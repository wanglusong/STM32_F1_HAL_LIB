#ifndef _LED_H
#define _LED_H

#include "sys.h"

#define F103_C8T6_TWO_USB_ADD_8PIN_LCD_INTERFACE 1

#if F103_C8T6_TWO_USB_ADD_8PIN_LCD_INTERFACE

#define LED0 PDout(2)   	//LED0
#define LED1 PAout(8)   	//LED1

#endif

void LED_Init(void);

#endif
