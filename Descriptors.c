/*
*
* USB360: Interfaz USB que emula control de Xbox 360 para Pro Micro originales o piratas 
*
* Copyright (c) 2020
* Bruno Freitas - bruno@brunofreitas.com
* Jon Wilson    - degenatrons@gmail.com
* Kevin Mackett - kevin@sharpfork.com
* Bastian Aguirre - crtgamers.cl
*
* Este programa es software gratuito: puedes redistribuirlo y / o modificar
* bajo los términos de la Licencia Pública General GNU publicada por
* Free Software Foundation, ya sea la versión 3 de la Licencia, o
* (a su elección) cualquier versión posterior.
*
* Este programa se distribuye con la esperanza de que sea útil,
* pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
* COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver el
* Licencia pública general GNU para más detalles.
*
* Debería haber recibido una copia de la Licencia Pública General GNU
* junto con este programa. Si no, vea <http://www.gnu.org/licenses/>.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const uint8_t PROGMEM DeviceDescriptor[] =
{
	0x12,        // bLength
	0x01,        // bDescriptorType (Device)
	0x00, 0x02,  // bcdUSB 2.00
	0xFF,        // bDeviceClass 
	0xFF,        // bDeviceSubClass 
	0xFF,        // bDeviceProtocol 
	0x40,        // bMaxPacketSize0 64
	0x5E, 0x04,  // idVendor 0x045E
	0x8E, 0x02,  // idProduct 0x028E
	0x14, 0x01,  // bcdDevice 2.14
	0x01,        // iManufacturer (String Index)
	0x02,        // iProduct (String Index)
	0x03,        // iSerialNumber (String Index)
	0x01        // bNumConfigurations 1
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const uint8_t PROGMEM ConfigurationDescriptor[] =
{
	0x09,        // bLength
	0x02,        // bDescriptorType (Configuration)
	0x99, 0x00,  // wTotalLength 153
	0x04,        // bNumInterfaces 4
	0x01,        // bConfigurationValue
	0x00,        // iConfiguration (String Index)
	0xA0,        // bmAttributes Remote Wakeup
	0xFA,        // bMaxPower 500mA
	
	0x09,        // bLength
	0x04,        // bDescriptorType (Interface)
	0x00,        // bInterfaceNumber 0
	0x00,        // bAlternateSetting
	0x02,        // bNumEndpoints 2
	0xFF,        // bInterfaceClass
	0x5D,        // bInterfaceSubClass
	0x01,        // bInterfaceProtocol
	0x00,        // iInterface (String Index)
	
	0x11,        // bLength
	0x21,        // bDescriptorType (HID)
	0x00, 0x01,  // bcdHID 1.00
	0x01,        // bCountryCode
	0x25,        // bNumDescriptors
	0x81,        // bDescriptorType[0] (Unknown 0x81)
	0x14, 0x00,  // wDescriptorLength[0] 20
	0x00,        // bDescriptorType[1] (Unknown 0x00)
	0x00, 0x00,  // wDescriptorLength[1] 0
	0x13,        // bDescriptorType[2] (Unknown 0x13)
	0x01, 0x08,  // wDescriptorLength[2] 2049
	0x00,        // bDescriptorType[3] (Unknown 0x00)
	0x00, 
	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x81,        // bEndpointAddress (IN/D2H)
	0x03,        // bmAttributes (Interrupt)
	0x20, 0x00,  // wMaxPacketSize 32
	0x01,        // bInterval 4 (unit depends on device speed)
	
	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x01,        // bEndpointAddress (OUT/H2D)
	0x03,        // bmAttributes (Interrupt)
	0x20, 0x00,  // wMaxPacketSize 32
	0x08,        // bInterval 8 (unit depends on device speed)
	
	0x09,        // bLength
	0x04,        // bDescriptorType (Interface)
	0x01,        // bInterfaceNumber 1
	0x00,        // bAlternateSetting
	0x04,        // bNumEndpoints 4
	0xFF,        // bInterfaceClass
	0x5D,        // bInterfaceSubClass
	0x03,        // bInterfaceProtocol
	0x00,        // iInterface (String Index)
	
	0x1B,        // bLength
	0x21,        // bDescriptorType (HID)
	0x00, 0x01,  // bcdHID 1.00
	0x01,        // bCountryCode
	0x01,        // bNumDescriptors
	0x82,        // bDescriptorType[0] (Unknown 0x82)
	0x40, 0x01,  // wDescriptorLength[0] 320
	0x02, 0x20, 0x16, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x82,        // bEndpointAddress (IN/D2H)
	0x03,        // bmAttributes (Interrupt)
	0x20, 0x00,  // wMaxPacketSize 32
	0x02,        // bInterval 2 (unit depends on device speed)
	
	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x02,        // bEndpointAddress (OUT/H2D)
	0x03,        // bmAttributes (Interrupt)
	0x20, 0x00,  // wMaxPacketSize 32
	0x04,        // bInterval 4 (unit depends on device speed)
	
	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x83,        // bEndpointAddress (IN/D2H)
	0x03,        // bmAttributes (Interrupt)
	0x20, 0x00,  // wMaxPacketSize 32
	0x40,        // bInterval 64 (unit depends on device speed)
	
	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x03,        // bEndpointAddress (OUT/H2D)
	0x03,        // bmAttributes (Interrupt)
	0x20, 0x00,  // wMaxPacketSize 32
	0x10,        // bInterval 16 (unit depends on device speed)
	
	0x09,        // bLength
	0x04,        // bDescriptorType (Interface)
	0x02,        // bInterfaceNumber 2
	0x00,        // bAlternateSetting
	0x01,        // bNumEndpoints 1
	0xFF,        // bInterfaceClass
	0x5D,        // bInterfaceSubClass
	0x02,        // bInterfaceProtocol
	0x00,        // iInterface (String Index)
	
	0x09,        // bLength
	0x21,        // bDescriptorType (HID)
	0x00, 0x01,  // bcdHID 1.00
	0x01,        // bCountryCode
	0x22,        // bNumDescriptors
	0x84,        // bDescriptorType[0] (Unknown 0x84)
	0x07, 0x00,  // wDescriptorLength[0] 7
	
	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x84,        // bEndpointAddress (IN/D2H)
	0x03,        // bmAttributes (Interrupt)
	0x20, 0x00,  // wMaxPacketSize 32
	0x10,        // bInterval 16 (unit depends on device speed)
	
	0x09,        // bLength
	0x04,        // bDescriptorType (Interface)
	0x03,        // bInterfaceNumber 3
	0x00,        // bAlternateSetting
	0x00,        // bNumEndpoints 0
	0xFF,        // bInterfaceClass
	0xFD,        // bInterfaceSubClass
	0x13,        // bInterfaceProtocol
	0x04,        // iInterface (String Index)
	
	0x06,        // bLength
	0x41,        // bDescriptorType (Unknown)
	0x00, 0x01, 0x01, 0x03
};

/** Estructura del descriptor de idioma. Este descriptor, ubicado en la memoria FLASH, se devuelve cuando el host solicita
 * el descriptor de cadena con índice 0 (el primer índice). En realidad, es una matriz de enteros de 16 bits, que indican
 * a través de la tabla de ID de idiomas disponible en USB.org, qué idiomas admite el dispositivo para sus descriptores de cadena.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Cadena de descriptor del fabricante. Esta es una cadena Unicode que contiene los detalles del fabricante en legible por humanos
 * formulario, y se lee en voz alta a petición del host cuando se solicita la ID de cadena adecuada, que se enumera en el dispositivo
 * Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(12), .Type = DTYPE_String},

	.UnicodeString          = L"crtgamers.cl"
};

/** Cadena de descriptor de producto. Esta es una cadena Unicode que contiene los detalles del producto en forma legible por humanos,
 * y se lee a pedido del host cuando se solicita el ID de cadena apropiado, que se enumera en el Dispositivo
 * Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(81), .Type = DTYPE_String},

	.UnicodeString          = L"CRT GAMERS - 0 Delay USB Joystick Professional Plus Plus 2002 UM Champion Edition"
};

const USB_Descriptor_String_t PROGMEM VersionString =
{
	.Header                 = {.Size = USB_STRING_LEN(3), .Type = DTYPE_String},

	.UnicodeString          = L"6.9"
};

/** La biblioteca llama a esta función cuando está en modo dispositivo y debe anularse (consulte la biblioteca "Descriptores USB"
 * documentación) por el código de la aplicación para que se pueda dar la dirección y el tamaño de un descriptor solicitado
 * a la biblioteca USB. Cuando el dispositivo recibe una solicitud Get Descriptor en el punto final de control, esta función
 * se llama para que los detalles del descriptor se puedan devolver y el descriptor apropiado se envíe de vuelta al
 *  Puerto USB.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint16_t  DescriptorType   = (wValue >> 8);
	const uint16_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(DeviceDescriptor);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(ConfigurationDescriptor);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
				case 0x03:
					Address = &VersionString;
					Size    = pgm_read_byte(&VersionString.Header.Size);
					break;
		}

			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

