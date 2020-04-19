/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Joystick.c.
 */

#ifndef _NESADAPTER_H_
#define _NESADAPTER_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <string.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Platform/Platform.h>

	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)

	/* Hardware definitions */

	/* Joystick port 1 */
	#define JOY1_DATA_DDR		DDRD
	#define JOY1_DATA_PORT		PORTD
	#define JOY1_DATA_PIN		PIND
	#define JOY1_DATA			(1 << 0)

	/* Joystick port 2 */
	#define JOY2_DATA_DDR		DDRD
	#define JOY2_DATA_PORT		PORTD
	#define JOY2_DATA_PIN		PIND
	#define JOY2_DATA			(1 << 1)

	/* Joystick port 3 */
	#define JOY3_DATA_DDR		DDRD
	#define JOY3_DATA_PORT		PORTD
	#define JOY3_DATA_PIN		PIND
	#define JOY3_DATA			(1 << 4)

	/* Joystick port 4 */
	#define JOY4_DATA_DDR		DDRD
	#define JOY4_DATA_PORT		PORTD
	#define JOY4_DATA_PIN		PIND
	#define JOY4_DATA			(1 << 5)

	/* Joystick latch line (shared by all 4 joystick ports) */
	#define JOY_LATCH_DDR		DDRD
	#define JOY_LATCH_PORT		PORTD
	#define JOY_LATCH_PIN		PIND
	#define JOY_LATCH			(1 << 2)

	/* Joystick clock line (shared by all 4 joystick ports) */
	#define JOY_CLOCK_DDR		DDRD
	#define JOY_CLOCK_PORT		PORTD
	#define JOY_CLOCK_PIN		PIND
	#define JOY_CLOCK			(1 << 3)

	/* Mapping of buttons to the state array */
	/* NES controller buttons */
	#define MAP_FIREA_BUTTON	0
	#define MAP_FIREB_BUTTON	1
	#define MAP_SELECT_BUTTON	2
	#define MAP_START_BUTTON	3
	#define MAP_DOWN_BUTTON		4
	#define MAP_UP_BUTTON		5
	#define MAP_LEFT_BUTTON		6
	#define MAP_RIGHT_BUTTON	7
	
	/* SNES controller buttons */
	// #define MAP_FIREB_BUTTON	0
	// #define MAP_FIREY_BUTTON	1
	// #define MAP_SELECT_BUTTON	2
	// #define MAP_START_BUTTON	3
	// #define MAP_DOWN_BUTTON		4
	// #define MAP_UP_BUTTON		5
	// #define MAP_LEFT_BUTTON		6
	// #define MAP_RIGHT_BUTTON	7
	// #define MAP_FIREA_BUTTON	8
	// #define MAP_FIREX_BUTTON	9
	// #define MAP_FIREL_BUTTON	10
	// #define MAP_FIRER_BUTTON	11
	
	/* The number of physical buttons */
	#define NUMBER_OF_BUTTONS		8  /* NES */
	// #define NUMBER_OF_BUTTONS		12 /* SNES */

	/* Define the de-bounce tolerance */
	#define DEBOUNCE_TOLERANCE		10

	/* Physical button states */
	#define BUTTON_OFF	0
	#define BUTTON_ON	1

	/* Type Defines: */
		/** Type define for the joystick HID report structure,
		 *  for creating and sending HID reports to the host PC.
		 *  This mirrors the layout described to the host in the HID report descriptor,
		 *  in Descriptors.c.
		 */
		typedef struct
		{
			int8_t  x;			// Current absolute joystick X position, as a signed 8-bit integer
			int8_t  y;			// Current absolute joystick Y position, as a signed 8-bit integer
			uint8_t buttonMask; // Bit mask of the currently pressed joystick buttons
		} USB_JoystickReport_Data_t;

	/* Function Prototypes: */
		void SetupHardware(void);
		void HID_Task(void);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);
		
		void readJoystickStates(void);
		void performDebounce(void);

		bool GetNextReport(USB_JoystickReport_Data_t* const reportData, USB_JoystickReport_Data_t* const previousReportData, uint8_t joystickNumber);

#endif

