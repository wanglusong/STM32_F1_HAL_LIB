#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "usmart.h"
#include "malloc.h" 
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
#include "string.h"
#include "usmart.h"
#include "fontupd.h"
#include "text.h"	
#include "TEA5767.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_gui_main.h"
#include "lcd_config.h"
#include "lv_demo_keypad_encoder.h"

#ifndef LV_DISPALY
#include "lv_port_disp.h"
#endif

extern unsigned long frequency;


int main(void)
{ 
	
	HAL_Init();                    	 	   
	Stm32_Clock_Init(RCC_PLL_MUL9);//72M
	delay_init(72);         //DELAY
	uart_init(9600);				//UART
	LED_Init();							//LED
	KEY_Init();							//KEY
	
	/*lvgl的1ms心跳*/
	TIM3_Init(999,71);	
	/*little vGL init*/
	lv_init();
	/*LCD映射到LVGL*/
	lv_port_disp_init();
	/*init end*/
	
	/*userinit*/
	lv_demo_keypad_encoder();
	//lv_ex_get_started_3();
	
	printf("system is starting\r\n");
	
	while(1)
	{

		lv_task_handler();
		LED1=!LED1;
		delay_ms(50);

	}
}

