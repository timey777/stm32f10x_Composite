/**
 ******************************************************************************
 * @file    usb_desc.c
 * @author  MCD Application Team
 * @version V4.1.0
 * @date    26-May-2017
 * @brief   Descriptors for Joystick Mouse Demo
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usb_desc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t Composite_DeviceDescriptor[COMPOSITE_SIZ_DEVICE_DESC] =
    {
        0x12,                       /* 设备描述符的长度bLength */
        USB_DEVICE_DESCRIPTOR_TYPE, /* 此描述符类型，这里是USB设备描述符类型bDescriptorType */
        0x10, 0x01,                 /* bcdUSB = 2.00 */
        0xEF,                       /* bDeviceClass 设备类 复合设备 */
        0x02,                       /* bDeviceSubClass 设备子类*/
        0x01,                       /* bDeviceProtocol 设备协议*/
        0x40,                       /* bMaxPacketSize0 端点0对应包的的最大包的大小*/
        0x73, 0x23,                 /* idVendor = 0x0483 */
        0x40, 0x57,                 /* idProduct = 0x5740 */
        0x00, 0x02,                 /* bcdDevice = 2.00 */
        1,                          /* Index of string descriptor describing manufacturer */
        2,                          /* Index of string descriptor describing product */
        3,                          /* Index of string descriptor describing the device's serial number */
        0x01                        /* bNumConfigurations 配置描述符个数*/
}; /* Joystick_DeviceDescriptor */

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Composite_ConfigDescriptor[COMPOSITE_SIZ_CONFIG_DESC] =
    {
        0x09,                              /* bLength: Configuration Descriptor size */
        USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
        COMPOSITE_SIZ_CONFIG_DESC,
        /* wTotalLength: Bytes returned */
        0x00,
        0x03, /* bNumInterfaces: 3 interface 共3个接口 CDC 2个 HID一个*/
        0x01, /* bConfigurationValue: Configuration value */
        0x00, /* iConfiguration: Index of string descriptor describing
                             the configuration*/
        0xC0, /* bmAttributes: Self powered */
        0x32, /* MaxPower 100 mA: this current is used for detecting Vbus */

        /*************************************功能1 HID键盘**************************************/
        /*IAD描述符*/
        0x08, // bLength：IAD描述符大小
        0x0B, // bDescriptorType：IAD描述符类型
        0x00, // bFirstInterface：功能1 HID键盘的第一个接口描述符是在总的配置描述符中的第几个从0开始数
        0x01, // bInferfaceCount：功能1 HID键盘有1个接口描述符
        0x03, // bFunctionClass：同单HID功能时，设备符中的bDeviceClass
        0x00, // bFunctionSubClass：同单HID功能时，设备符中的bDeviceSubClass
        0x01, // bFunctionProtocol：同单HID功能时，设备符中的bDeviceProtocol
        0x00, // iFunction：字符串描述中关于此设备的索引(个人理解是一个字符串描述符中有比如0~5是功能1的字符串，
              // 6~10是功能2的字符串,如果是功能2的话，此值为6)

        /************** Descriptor of Custom HID interface ****************/
        /* 09 */
        0x09,                                             /* bLength: Interface Descriptor size */
        USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType: Interface descriptor type */
        0x00, /* bInterfaceNumber: Number of Interface */ //<接口 0>
        0x00,                                             /* bAlternateSetting: Alternate setting */
        0x02,                                             /* bNumEndpoints */
        0x03,                                             /* bInterfaceClass: HID */
        0x01,                                             /* bInterfaceSubClass : 1=BOOT, 0=no boot */
        0x01,                                             /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
        0,                                                /* iInterface: Index of string descriptor */
        /******************** Descriptor of Custom HID HID ********************/
        /* 18 */
        0x09,                /* bLength: HID Descriptor size */
        HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
        0x10,                /* bcdHID: HID Class Spec release number */
        0x01,
        0x00, /* bCountryCode: Hardware target country */
        0x01, /* bNumDescriptors: Number of HID class descriptors to follow */
        0x22, /* bDescriptorType */
        CUSTOMHID_SIZ_REPORT_DESC,
        // KEYBOARD_SIZ_REPORT_DESC,/* wItemLength: Total length of Report descriptor */
        0x00,
        /******************** Descriptor of Custom HID endpoints ******************/
        /* 27 */
        0x07,                         /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */
        0x84,                         /* bEndpointAddress: Endpoint Address (IN) */
        0x03,                         /* bmAttributes: Interrupt endpoint */
        0x09,                         /* wMaxPacketSize: 8 Bytes max */
        0x00,
        0x20, /* bInterval: Polling Interval (32 ms) */
        /* 34 */
        0x07,                         /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */
        0x04,                         /* bEndpointAddress:Endpoint Address (OUT) */
        0x03,                         /* bmAttributes: Interrupt endpoint */
        0x01,                         /* wMaxPacketSize: 1 Bytes max  */
        0x00,
        0x20, /* bInterval: Polling Interval (20 ms) */
        /* 41 */
        /********************************功能2 VCP虚拟串口*****************************/
        /*IAD描述符*/
        /* Interface Association Descriptor(IAD Descriptor)  */
        0x08, /*  bLength  */
        0x0B, /*  bDescriptorType*/
        0x01, /*  bFirstInterface*/
        0x02, /*  bInterfaceCount*/
        0x02, /*  bFunctionClass --CDC*/
        0x02, /*  bFunctionSubClass*/
        0x01, /*  bFunctionProtocoll*/
        0x00, /*  iFunction */

        /**VCP虚拟串口**/
        /*Interface Descriptor接口描述符*/
        0x09,                          /* bLength: Interface Descriptor size */
        USB_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType: Interface */
        /* Interface descriptor type */
        0x01, /* bInterfaceNumber: Number of Interface */ //<接口 1>
        0x00,                                             /* bAlternateSetting: Alternate setting */
        0x01,                                             /* bNumEndpoints: One endpoints used 该接口非0端点数*/
        0x02,                                             /* bInterfaceClass: Communication Interface Class */
        0x02,                                             /* bInterfaceSubClass: Abstract Control Model */
        0x01,                                             /* bInterfaceProtocol: Common AT commands */
        0x00,                                             /* iInterface: */
        /*Header Functional Descriptor类描述符*/
        0x05, /* bLength: Endpoint Descriptor size */
        0x24, /* bDescriptorType: CS_INTERFACE */
        0x00, /* bDescriptorSubtype: Header Func Desc */
        0x10, /* bcdCDC: spec release number */
        0x01,
        /*Call Management Functional Descriptor*/
        0x05, /* bFunctionLength */
        0x24, /* bDescriptorType: CS_INTERFACE */
        0x01, /* bDescriptorSubtype: Call Management Func Desc */
        0x00, /* bmCapabilities: D0+D1 */
        0x01, /* bDataInterface: 1 */
        /*ACM Functional Descriptor*/
        0x04, /* bFunctionLength */
        0x24, /* bDescriptorType: CS_INTERFACE */
        0x02, /* bDescriptorSubtype: Abstract Control Management desc */
        0x02, /* bmCapabilities */
        /*Union Functional Descriptor*/
        0x05, /* bFunctionLength */
        0x24, /* bDescriptorType: CS_INTERFACE */
        0x06, /* bDescriptorSubtype: Union func desc */
        0x00, /* bMasterInterface: Communication class interface */
        0x01, /* bSlaveInterface0: Data Class Interface */
        /*Endpoint 2 Descriptor端点描述符*/
        0x07,                         /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: Endpoint */
        0x82,                         /* bEndpointAddress: (IN2) */
        0x03,                         /* bmAttributes: Interrupt */
        VIRTUAL_COM_PORT_INT_SIZE,    /* wMaxPacketSize: */
        0x00,
        0xFF, /* bInterval: */

        /*Data class interface descriptor类描述符*/
        0x09,                                             /* bLength: Endpoint Descriptor size */
        USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType: */
        0x02, /* bInterfaceNumber: Number of Interface */ //<接口 2>
        0x00,                                             /* bAlternateSetting: Alternate setting */
        0x02,                                             /* bNumEndpoints: Two endpoints used */
        0x0A,                                             /* bInterfaceClass: CDC */
        0x00,                                             /* bInterfaceSubClass: */
        0x00,                                             /* bInterfaceProtocol: */
        0x00,                                             /* iInterface: */
        /*Endpoint 3 Descriptor端点描述符*/
        0x07,                         /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: Endpoint */
        0x03,                         /* bEndpointAddress: (OUT3) */
        0x02,                         /* bmAttributes: Bulk */
        VIRTUAL_COM_PORT_DATA_SIZE,   /* wMaxPacketSize: */
        0x00,
        0x00, /* bInterval: ignore for Bulk transfer */
        /*Endpoint 1 Descriptor 端点描述符*/
        0x07,                         /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: Endpoint */
        0x81,                         /* bEndpointAddress: (IN1) */
        0x02,                         /* bmAttributes: Bulk */
        VIRTUAL_COM_PORT_DATA_SIZE,   /* wMaxPacketSize: */
        0x00,
        0x00 /* bInterval */
};
/* MOUSE_ConfigDescriptor */
const uint8_t CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] =
    {
        0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,                    // USAGE (Keyboard)
        0xa1, 0x01,                    // COLLECTION (Application)
        0x85, 0x01,                    //   REPORT_ID (1)
        0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
        0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
        0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,                    //   REPORT_SIZE (1)
        0x95, 0x08,                    //   REPORT_COUNT (8)
        0x81, 0x02,                    //   INPUT (Data,Var,Abs)
        0x95, 0x01,                    //   REPORT_COUNT (1)
        0x75, 0x08,                    //   REPORT_SIZE (8)
        0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
        0x95, 0x05,                    //   REPORT_COUNT (5)
        0x75, 0x01,                    //   REPORT_SIZE (1)
        0x05, 0x08,                    //   USAGE_PAGE (LEDs)
        0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
        0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
        0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
        0x95, 0x01,                    //   REPORT_COUNT (1)
        0x75, 0x03,                    //   REPORT_SIZE (3)
        0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
        0x95, 0x06,                    //   REPORT_COUNT (6)
        0x75, 0x08,                    //   REPORT_SIZE (8)
        0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
        0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
        0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
        0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
        0xc0,                          // END_COLLECTION
        0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
        0x09, 0x02,                    // USAGE (Mouse)
        0xa1, 0x01,                    // COLLECTION (Application)
        0x85, 0x02,                    //   REPORT_ID (2)
        0x09, 0x01,                    //   USAGE (Pointer)
        0xa1, 0x00,                    //   COLLECTION (Physical)
        0x05, 0x09,                    //     USAGE_PAGE (Button)
        0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
        0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
        0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
        0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
        0x95, 0x03,                    //     REPORT_COUNT (3)
        0x75, 0x01,                    //     REPORT_SIZE (1)
        0x81, 0x02,                    //     INPUT (Data,Var,Abs)
        0x95, 0x01,                    //     REPORT_COUNT (1)
        0x75, 0x05,                    //     REPORT_SIZE (5)
        0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
        0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
        0x09, 0x30,                    //     USAGE (X)
        0x09, 0x31,                    //     USAGE (Y)
        0x09, 0x38,                    //     USAGE (Wheel)
        0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
        0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
        0x75, 0x08,                    //     REPORT_SIZE (8)
        0x95, 0x03,                    //     REPORT_COUNT (3)
        0x81, 0x06,                    //     INPUT (Data,Var,Rel)
        0xc0,                          //   END_COLLECTION
        0xc0                           // END_COLLECTION

}; /* CustomHID_ReportDescriptor */

/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
    {
        JOYSTICK_SIZ_STRING_LANGID,
        USB_STRING_DESCRIPTOR_TYPE,
        0x09,
        0x04}; /* LangID = 0x0409: U.S. English */

const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
    {
        JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
        USB_STRING_DESCRIPTOR_TYPE, /* bDescriptorType*/
        /* Manufacturer: "STMicroelectronics" */
        'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
        'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
        'c', 0, 's', 0};

const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
    {
        JOYSTICK_SIZ_STRING_PRODUCT, /* bLength */
        USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType */
        'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'J', 0,
        'o', 0, 'y', 0, 's', 0, 't', 0, 'i', 0, 'c', 0, 'k', 0};
uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
    {
        JOYSTICK_SIZ_STRING_SERIAL, /* bLength */
        USB_STRING_DESCRIPTOR_TYPE, /* bDescriptorType */
        'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
