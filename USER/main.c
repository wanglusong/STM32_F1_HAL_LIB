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
 	LCD_Init();							//LCD     
	
	/*little vGL init*/
	lv_init();
	/*lvgl的1ms心跳*/
	TIM3_Init(999,71);
	/*LCD映射到LVGL*/
	lv_port_disp_init();
	/*init end*/
	
	/*userinit*/
	lv_st_theme_Init();
	lv_ex_get_started_3();

	printf("system is starting\r\n");
	
	while(1)
	{

		LED0=!LED0;
		delay_ms(50);

	}
}

