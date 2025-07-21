#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "usb_type.h"

void Set_USBClock(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);
uint32_t CDC_Send_DATA (uint8_t *ptrBuffer, uint8_t Send_length);
uint32_t CDC_Receive_DATA(void);
#endif  /*__HW_CONFIG_H*/