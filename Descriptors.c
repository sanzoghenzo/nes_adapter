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
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

/** Joystick 0 report descriptor. **/
const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport0[] =
{
	HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
	HID_RI_USAGE(8, 0x04), /* Joystick */
	HID_RI_COLLECTION(8, 0x01), /* Application */
		HID_RI_COLLECTION(8, 0x00), /* Physical */
			HID_RI_USAGE(8, 0x30), /* Usage X */
			HID_RI_USAGE(8, 0x31), /* Usage Y */
			HID_RI_LOGICAL_MINIMUM(8, -127),
			HID_RI_LOGICAL_MAXIMUM(8, 127),
			HID_RI_PHYSICAL_MINIMUM(8, -1),
			HID_RI_PHYSICAL_MAXIMUM(8, 1),
			HID_RI_REPORT_COUNT(8, 0x02),
			HID_RI_REPORT_SIZE(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

			HID_RI_USAGE_PAGE(8, 0x09), /* Button */
			HID_RI_USAGE_MINIMUM(8, 0x01),
			HID_RI_USAGE_MAXIMUM(8, 0x04), /* NES controller has 4 buttons */
			// HID_RI_USAGE_MAXIMUM(8, 0x08), /* SNES controller has 8 buttons */
			HID_RI_LOGICAL_MINIMUM(8, 0x00),
			HID_RI_LOGICAL_MAXIMUM(8, 0x01),
			HID_RI_REPORT_SIZE(8, 0x01),
			HID_RI_REPORT_COUNT(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
		HID_RI_END_COLLECTION(0),
	HID_RI_END_COLLECTION(0),
};

/** Joystick 1 report descriptor. **/
const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport1[] =
{
	HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
	HID_RI_USAGE(8, 0x04), /* Joystick */
	HID_RI_COLLECTION(8, 0x01), /* Application */
		HID_RI_COLLECTION(8, 0x00), /* Physical */
			HID_RI_USAGE(8, 0x30), /* Usage X */
			HID_RI_USAGE(8, 0x31), /* Usage Y */
			HID_RI_LOGICAL_MINIMUM(8, -127),
			HID_RI_LOGICAL_MAXIMUM(8, 127),
			HID_RI_PHYSICAL_MINIMUM(8, -1),
			HID_RI_PHYSICAL_MAXIMUM(8, 1),
			HID_RI_REPORT_COUNT(8, 0x02),
			HID_RI_REPORT_SIZE(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

			HID_RI_USAGE_PAGE(8, 0x09), /* Button */
			HID_RI_USAGE_MINIMUM(8, 0x01),
			HID_RI_USAGE_MAXIMUM(8, 0x04), /* NES controller has 4 buttons */
			// HID_RI_USAGE_MAXIMUM(8, 0x08), /* SNES controller has 8 buttons */
			HID_RI_LOGICAL_MINIMUM(8, 0x00),
			HID_RI_LOGICAL_MAXIMUM(8, 0x01),
			HID_RI_REPORT_SIZE(8, 0x01),
			HID_RI_REPORT_COUNT(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
		HID_RI_END_COLLECTION(0),
	HID_RI_END_COLLECTION(0),
};

/** Joystick 0 report descriptor. **/
const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport2[] =
{
	HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
	HID_RI_USAGE(8, 0x04), /* Joystick */
	HID_RI_COLLECTION(8, 0x01), /* Application */
		HID_RI_COLLECTION(8, 0x00), /* Physical */
			HID_RI_USAGE(8, 0x30), /* Usage X */
			HID_RI_USAGE(8, 0x31), /* Usage Y */
			HID_RI_LOGICAL_MINIMUM(8, -127),
			HID_RI_LOGICAL_MAXIMUM(8, 127),
			HID_RI_PHYSICAL_MINIMUM(8, -1),
			HID_RI_PHYSICAL_MAXIMUM(8, 1),
			HID_RI_REPORT_COUNT(8, 0x02),
			HID_RI_REPORT_SIZE(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

			HID_RI_USAGE_PAGE(8, 0x09), /* Button */
			HID_RI_USAGE_MINIMUM(8, 0x01),
			HID_RI_USAGE_MAXIMUM(8, 0x04), /* NES controller has 4 buttons */
			// HID_RI_USAGE_MAXIMUM(8, 0x08), /* SNES controller has 8 buttons */
			HID_RI_LOGICAL_MINIMUM(8, 0x00),
			HID_RI_LOGICAL_MAXIMUM(8, 0x01),
			HID_RI_REPORT_SIZE(8, 0x01),
			HID_RI_REPORT_COUNT(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
		HID_RI_END_COLLECTION(0),
	HID_RI_END_COLLECTION(0),
};

/** Joystick 0 report descriptor. **/
const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport3[] =
{
	HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
	HID_RI_USAGE(8, 0x04), /* Joystick */
	HID_RI_COLLECTION(8, 0x01), /* Application */
		HID_RI_COLLECTION(8, 0x00), /* Physical */
			HID_RI_USAGE(8, 0x30), /* Usage X */
			HID_RI_USAGE(8, 0x31), /* Usage Y */
			HID_RI_LOGICAL_MINIMUM(8, -127),
			HID_RI_LOGICAL_MAXIMUM(8, 127),
			HID_RI_PHYSICAL_MINIMUM(8, -1),
			HID_RI_PHYSICAL_MAXIMUM(8, 1),
			HID_RI_REPORT_COUNT(8, 0x02),
			HID_RI_REPORT_SIZE(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

			HID_RI_USAGE_PAGE(8, 0x09), /* Button */
			HID_RI_USAGE_MINIMUM(8, 0x01),
			HID_RI_USAGE_MAXIMUM(8, 0x04), /* NES controller has 4 buttons */
			// HID_RI_USAGE_MAXIMUM(8, 0x08), /* SNES controller has 8 buttons */
			HID_RI_LOGICAL_MINIMUM(8, 0x00),
			HID_RI_LOGICAL_MAXIMUM(8, 0x01),
			HID_RI_REPORT_SIZE(8, 0x01),
			HID_RI_REPORT_COUNT(8, 0x08),
			HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
		HID_RI_END_COLLECTION(0),
	HID_RI_END_COLLECTION(0),
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(1,1,0),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 0x03ED,
	.ProductID              = 0xA049,
	.ReleaseNumber          = VERSION_BCD(0,0,1),

	.ManufacturerStrIndex   = STRING_ID_Manufacturer,
	.ProductStrIndex        = STRING_ID_Product,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 4,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	// Joystick HID interface (HID0)
	.HID0_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x00, // Interface 0 is joystick 0
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 1,

			.Class                  = HID_CSCP_HIDClass,
			.SubClass               = HID_CSCP_NonBootSubclass,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID0_JoystickHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(1,1,1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(JoystickReport0)
		},

	.HID0_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = JOYSTICK0_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = JOYSTICK_EPSIZE,
			.PollingIntervalMS      = 0x05
		},

	// Joystick HID interface (HID1)
	.HID1_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x01, // Interface 1 is joystick 1
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 1,

			.Class                  = HID_CSCP_HIDClass,
			.SubClass               = HID_CSCP_NonBootSubclass,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID1_JoystickHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(1,1,1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(JoystickReport1)
		},

	.HID1_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = JOYSTICK1_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = JOYSTICK_EPSIZE,
			.PollingIntervalMS      = 0x05
		},

	// Joystick HID interface (HID2)
	.HID2_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x02, // Interface 2 is joystick 2
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 1,

			.Class                  = HID_CSCP_HIDClass,
			.SubClass               = HID_CSCP_NonBootSubclass,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID2_JoystickHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(1,1,1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(JoystickReport2)
		},

	.HID2_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = JOYSTICK2_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = JOYSTICK_EPSIZE,
			.PollingIntervalMS      = 0x05
		},

	// Joystick HID interface (HID3)
	.HID3_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x03, // Interface 3 is joystick 3
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 1,

			.Class                  = HID_CSCP_HIDClass,
			.SubClass               = HID_CSCP_NonBootSubclass,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID3_JoystickHID =
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

			.HIDSpec                = VERSION_BCD(1,1,1),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = HID_DTYPE_Report,
			.HIDReportLength        = sizeof(JoystickReport3)
		},

	.HID3_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = JOYSTICK3_EPADDR,
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = JOYSTICK_EPSIZE,
			.PollingIntervalMS      = 0x05
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString = USB_STRING_DESCRIPTOR(L"Andrea Ghensi");

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString = USB_STRING_DESCRIPTOR(L"NES Controller Adapter");

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case STRING_ID_Language:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case STRING_ID_Manufacturer:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case STRING_ID_Product:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}

			break;
		case DTYPE_HID:
			switch (wIndex)
			{
				case 0x00:
					Address = &ConfigurationDescriptor.HID0_JoystickHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;

				case 0x01:
					Address = &ConfigurationDescriptor.HID1_JoystickHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;
				
				case 0x02:
					Address = &ConfigurationDescriptor.HID2_JoystickHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;

				case 0x03:
					Address = &ConfigurationDescriptor.HID3_JoystickHID;
					Size    = sizeof(USB_HID_Descriptor_HID_t);
					break;
			}
			break;
		case DTYPE_Report:
			switch (wIndex)
			{
				case 0x00:
					Address = &JoystickReport0;
					Size    = sizeof(JoystickReport0);
					break;

				case 0x01:
					Address = &JoystickReport1;
					Size    = sizeof(JoystickReport1);
					break;

				case 0x02:
					Address = &JoystickReport2;
					Size    = sizeof(JoystickReport2);
					break;

				case 0x03:
					Address = &JoystickReport3;
					Size    = sizeof(JoystickReport3);
					break;
				
			}
			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

