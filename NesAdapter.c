/* 
	NES controller USB adapter By Andrea Ghensi
	Heavily based on Nintendo Four Score USB Joystick Adapter by Simon Inns

	Since I have a Minimus AVR and no Four Score,
	I removed Fire and Player buttons from the code.

	Copyright (C) 2013 Simon Inns

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Email: simon.inns@gmail.com
*/

/** \file
 *
 *  Main source file for the (S)NES cotroller Adapter.
 *  This file contains the main tasks
 *  and is responsible for the initial application hardware configuration.
 */

#include "NesAdapter.h"

/** Array for storing the physical button state, 
 *  de-bounce counter and current de-bounced button state
 */
struct buttonState
{
	uint8_t physicalState; // On or off
	uint8_t state; // On or off
	uint8_t debounceCount;
};

/** Array for storing the physical state of all four joysticks **/
struct joystickState
{
	struct buttonState button[NUMBER_OF_BUTTONS];
} joyStick[4];

/** Global for storing the previously sent reports for each joystick **/
USB_JoystickReport_Data_t previousJoystickReportData0;
USB_JoystickReport_Data_t previousJoystickReportData1;
USB_JoystickReport_Data_t previousJoystickReportData2;
USB_JoystickReport_Data_t previousJoystickReportData3;

/** Main program entry point. 
 *  This routine configures the hardware required by the application,
 *  then enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	/* Main program loop */
	while(1)
	{
		/* Read the joystick states */
		readJoystickStates();

		/* Perform button and joystick debouncing */
		performDebounce();
		
		/* Perform the local HID tasks */
		HID_Task();
		
		/* Perform the LUFA USB tasks */
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#elif (ARCH == ARCH_XMEGA)
	/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
	XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
	XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

	/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
	XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
	XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif


	/* Hardware Initialization */

	/* Joystick data input */
	JOY1_DATA_DDR &= ~(JOY1_DATA);			// Set direction to input
	JOY1_DATA_PORT |= JOY1_DATA;			// Turn on weak pull-ups
	JOY2_DATA_DDR &= ~(JOY2_DATA);			// Set direction to input
	JOY2_DATA_PORT |= JOY2_DATA;			// Turn on weak pull-ups
	JOY3_DATA_DDR &= ~(JOY3_DATA);			// Set direction to input
	JOY3_DATA_PORT |= JOY3_DATA;			// Turn on weak pull-ups
	JOY4_DATA_DDR &= ~(JOY4_DATA);			// Set direction to input
	JOY4_DATA_PORT |= JOY4_DATA;			// Turn on weak pull-ups
	
	/* Joystick clock output */
	JOY_CLOCK_DDR |= JOY_CLOCK;				// Set direction to output
	JOY_CLOCK_PORT &= ~(JOY_CLOCK);			// Set output to off
	
	/* Joystick latch output */
	JOY_LATCH_DDR |= JOY_LATCH;				// Set direction to output
	JOY_LATCH_PORT &= ~(JOY_LATCH);			// Set output to off
	
	/* Initialise the LUFA USB library */
	LEDs_Init();
	USB_Init();
}

/** Read the joystick button states for all 4 joysticks **/
void readJoystickStates(void)
{
	/* Set joystick latch low */
	JOY_LATCH_PORT &= ~(JOY_LATCH);
	
	for (uint8_t buttonNumber = 0; buttonNumber < NUMBER_OF_BUTTONS; buttonNumber++)
	{
		/* Set joystick clock low */
		_delay_us(6);
		JOY_CLOCK_PORT &= ~(JOY_CLOCK);
		
		/* Read the data pin state for all joysticks */
		if (JOY1_DATA_PIN & JOY1_DATA) joyStick[0].button[buttonNumber].physicalState = BUTTON_OFF;
			else joyStick[0].button[buttonNumber].physicalState = BUTTON_ON;
		if (JOY2_DATA_PIN & JOY2_DATA) joyStick[1].button[buttonNumber].physicalState = BUTTON_OFF;
			else joyStick[1].button[buttonNumber].physicalState = BUTTON_ON;
		if (JOY3_DATA_PIN & JOY3_DATA) joyStick[2].button[buttonNumber].physicalState = BUTTON_OFF;
			else joyStick[2].button[buttonNumber].physicalState = BUTTON_ON;
		if (JOY4_DATA_PIN & JOY4_DATA) joyStick[3].button[buttonNumber].physicalState = BUTTON_OFF;
			else joyStick[3].button[buttonNumber].physicalState = BUTTON_ON;
		
		/* Set joystick clock high */
		_delay_us(6);
		JOY_CLOCK_PORT |= (JOY_CLOCK);
	}
	
	/* Set joystick latch high */
	JOY_LATCH_PORT |= (JOY_LATCH);
}

/** Debounce buttons and joysticks on and off to improve joystick feedback **/
void performDebounce(void)
{
	for (uint8_t joystickNumber = 0; joystickNumber < 4; joystickNumber++)
	{
		/* De-bounce all buttons on and off */
		for (uint8_t buttonNumber = 0; buttonNumber < NUMBER_OF_BUTTONS; buttonNumber++)
		{
			/* De-bounce on */
			if (joyStick[joystickNumber].button[buttonNumber].physicalState ==
				BUTTON_ON && joyStick[joystickNumber].button[buttonNumber].state == BUTTON_OFF)
			{
				/* If the de-bounce tolerance is met change state
				 * otherwise increment the de-bounce counter
				 */
				if (joyStick[joystickNumber].button[buttonNumber].debounceCount > DEBOUNCE_TOLERANCE)
				joyStick[joystickNumber].button[buttonNumber].state = BUTTON_ON;
				else joyStick[joystickNumber].button[buttonNumber].debounceCount++;
			}
			/* De-bounce off */
			if (joyStick[joystickNumber].button[buttonNumber].physicalState
				== BUTTON_OFF && joyStick[joystickNumber].button[buttonNumber].state == BUTTON_ON)
			{			
				/* If the de-bounce tolerance is met change state 
				 * otherwise increment the de-bounce counter
				 */
				if (joyStick[joystickNumber].button[buttonNumber].debounceCount > DEBOUNCE_TOLERANCE)
				joyStick[joystickNumber].button[buttonNumber].state = BUTTON_OFF;
				else joyStick[joystickNumber].button[buttonNumber].debounceCount++;
			}
			/* Reset de-bounce counter */
			if (joyStick[joystickNumber].button[buttonNumber].physicalState ==
				joyStick[joystickNumber].button[buttonNumber].state)
				joyStick[joystickNumber].button[buttonNumber].debounceCount = 0;
		}
	}		
}

/** Event handler for the USB_Connect event. 
 *  This indicates that the device is enumerating via the status LEDs 
 *  and starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Device_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and joystick reporting tasks.
 */
void EVENT_USB_Device_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the joystick reporting task started.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup HID Report Endpoint, one for each joystick */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK0_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK1_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK2_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK3_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	/* Handle HID Class specific requests */
	switch (USB_ControlRequest.bRequest)
	{
		case HID_REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				USB_JoystickReport_Data_t JoystickReportData;

				/* Check which joystick the control request refers to: */
				switch (USB_ControlRequest.wIndex)
				{
					case 0x00:
						/* Create the next joystick0 HID report to send to the host */
						GetNextReport(&JoystickReportData, &previousJoystickReportData0, 0);

						Endpoint_ClearSETUP();

						/* Write the joystick0 report data to the control endpoint */
						Endpoint_Write_Control_Stream_LE(&JoystickReportData, sizeof(JoystickReportData));
						Endpoint_ClearOUT();
						break;

					case 0x01:
						/* Create the next joystick1 HID report to send to the host */
						GetNextReport(&JoystickReportData, &previousJoystickReportData1, 1);

						Endpoint_ClearSETUP();

						/* Write the joystick1 report data to the control endpoint */
						Endpoint_Write_Control_Stream_LE(&JoystickReportData, sizeof(JoystickReportData));
						Endpoint_ClearOUT();
						break;
						
					case 0x02:
						/* Create the next joystick2 HID report to send to the host */
						GetNextReport(&JoystickReportData, &previousJoystickReportData2, 2);

						Endpoint_ClearSETUP();

						/* Write the joystick2 report data to the control endpoint */
						Endpoint_Write_Control_Stream_LE(&JoystickReportData, sizeof(JoystickReportData));
						Endpoint_ClearOUT();
						break;

					case 0x03:
						/* Create the next joystick3 HID report to send to the host */
						GetNextReport(&JoystickReportData, &previousJoystickReportData3, 3);

						Endpoint_ClearSETUP();

						/* Write the joystick3 report data to the control endpoint */
						Endpoint_Write_Control_Stream_LE(&JoystickReportData, sizeof(JoystickReportData));
						Endpoint_ClearOUT();
						break;						
				}		
			}

			break;
	}
}

/** Fills the given HID report data structure with the next HID report to send to the host.
 *
 *  \param[out] ReportData  Pointer to a HID report data structure to be filled
 *  \param[out] previousReportData Pointer to the previous HID report
 *  \param joystickNumber joystick number
 *
 *  \return Boolean \c true if the new report differs from the last report, \c false otherwise
 */
bool GetNextReport(USB_JoystickReport_Data_t* const reportData, USB_JoystickReport_Data_t* const previousReportData, uint8_t joystickNumber)
{
	bool inputChanged = false;

	/* Clear the report contents */
	memset(reportData, 0, sizeof(USB_JoystickReport_Data_t));

	/* Set the joystick button status */
	/* NES buttons */
	if (joyStick[joystickNumber].button[MAP_FIREA_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 0);
	if (joyStick[joystickNumber].button[MAP_FIREB_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 1);
	if (joyStick[joystickNumber].button[MAP_SELECT_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 2);
	if (joyStick[joystickNumber].button[MAP_START_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 3);

	/* SNES buttons */
	// if (joyStick[joystickNumber].button[MAP_FIREB_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 0);
	// if (joyStick[joystickNumber].button[MAP_FIREY_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 1);
	// if (joyStick[joystickNumber].button[MAP_SELECT_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 2);
	// if (joyStick[joystickNumber].button[MAP_START_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 3);
	// if (joyStick[joystickNumber].button[MAP_FIREA_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 8);
	// if (joyStick[joystickNumber].button[MAP_FIREX_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 9);
	// if (joyStick[joystickNumber].button[MAP_FIREL_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 10);
	// if (joyStick[joystickNumber].button[MAP_FIRER_BUTTON].state == BUTTON_ON)	reportData->buttonMask |= (1 << 11);
	
	/* Set the joystick direction states */
	if (joyStick[joystickNumber].button[MAP_UP_BUTTON].state == BUTTON_ON)			reportData->y = 127;
	else if (joyStick[joystickNumber].button[MAP_DOWN_BUTTON].state == BUTTON_ON)	reportData->y = -127;
	else reportData->y = 0;
	
	if (joyStick[joystickNumber].button[MAP_LEFT_BUTTON].state == BUTTON_ON)		reportData->x = -127;
	else if (joyStick[joystickNumber].button[MAP_RIGHT_BUTTON].state == BUTTON_ON)	reportData->x = 127;
	else reportData->x = 0;

	/* Check to see if the joystick state has changed since the last report was sent */
	if (reportData->buttonMask != previousReportData->buttonMask) inputChanged = true;
	if (reportData->x != previousReportData->x) inputChanged = true;
	if (reportData->y != previousReportData->y) inputChanged = true;
	
	/* Save the current joystick status for later comparison */
	memcpy(previousReportData, reportData, sizeof(USB_JoystickReport_Data_t));

	/* Return whether the new report is different to the previous report or not */
	return inputChanged;
}

/** Function to manage HID report generation and transmission to the host. */
void HID_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	/* Select the Joystick 0 Report Endpoint */
	Endpoint_SelectEndpoint(JOYSTICK0_EPADDR);

	/* Check to see if the host is ready for another packet */
	if (Endpoint_IsINReady())
	{
		USB_JoystickReport_Data_t JoystickReportData0;

		/* Create the next HID report to send to the host */
		GetNextReport(&JoystickReportData0, &previousJoystickReportData0, 0);

		/* Write Joystick Report Data */
		Endpoint_Write_Stream_LE(&JoystickReportData0, sizeof(JoystickReportData0), NULL);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* Clear the report data afterwards */
		memset(&JoystickReportData0, 0, sizeof(JoystickReportData0));
	}
	
	/* Select the Joystick 1 Report Endpoint */
	Endpoint_SelectEndpoint(JOYSTICK1_EPADDR);
	
	/* Check to see if the host is ready for another packet */
	if (Endpoint_IsINReady())
	{
		USB_JoystickReport_Data_t JoystickReportData1;

		/* Create the next HID report to send to the host */
		GetNextReport(&JoystickReportData1, &previousJoystickReportData1, 1);

		/* Write Joystick Report Data */
		Endpoint_Write_Stream_LE(&JoystickReportData1, sizeof(JoystickReportData1), NULL);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* Clear the report data afterwards */
		memset(&JoystickReportData1, 0, sizeof(JoystickReportData1));
	}
	
	/* Select the Joystick 2 Report Endpoint */
	Endpoint_SelectEndpoint(JOYSTICK2_EPADDR);
		
	/* Check to see if the host is ready for another packet */
	if (Endpoint_IsINReady())
	{
		USB_JoystickReport_Data_t JoystickReportData2;

		/* Create the next HID report to send to the host */
		GetNextReport(&JoystickReportData2, &previousJoystickReportData2, 2);

		/* Write Joystick Report Data */
		Endpoint_Write_Stream_LE(&JoystickReportData2, sizeof(JoystickReportData2), NULL);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* Clear the report data afterwards */
		memset(&JoystickReportData2, 0, sizeof(JoystickReportData2));
	}
		
	/* Select the Joystick 1 Report Endpoint */
	Endpoint_SelectEndpoint(JOYSTICK3_EPADDR);
			
	/* Check to see if the host is ready for another packet */
	if (Endpoint_IsINReady())
	{
		USB_JoystickReport_Data_t JoystickReportData3;

		/* Create the next HID report to send to the host */
		GetNextReport(&JoystickReportData3, &previousJoystickReportData3, 3);

		/* Write Joystick Report Data */
		Endpoint_Write_Stream_LE(&JoystickReportData3, sizeof(JoystickReportData3), NULL);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* Clear the report data afterwards */
		memset(&JoystickReportData3, 0, sizeof(JoystickReportData3));
	}
}

