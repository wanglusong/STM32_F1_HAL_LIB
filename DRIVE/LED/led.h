#ifndef _LED_H
#define _LED_H

#include "appstart.h"

/*定义自己板子类型  ---  OPEN or CLOSE */
#define F103_C8T6_TWO_USB_ADD_8PIN_LCD_INTERFACE  CLOSE /*带8针OLED屏的有两个USB口的开发板*/
#define F103_ZET6_NETWORK_BOARD OPEN	/*物联网板子板载网口及ESP8266*/

#if F103_C8T6_TWO_USB_ADD_8PIN_LCD_INTERFACE

#define LED0 PDout(2)   	//LED0
#define LED1 PAout(8)   	//LED1

#elif F103_ZET6_NETWORK_BOARD

#define LED0 PCout(4)   	//LED0
#define LED1 PCout(5)   	//LED1
#define LED2 PBout(0)   	//LED2
#define LED3 PBout(1)   	//LED3

#endif

void LED_Init(void);

#endif
