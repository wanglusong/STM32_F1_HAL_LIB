#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "malloc.h" 
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
#include "string.h"
#include "TEA5767.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_gui_main.h"
#include "lcd_config.h"
#include "lv_demo_keypad_encoder.h"
#include "main.h"/*设备配置头*/

#if ESP8266_FUNC
#include "esp8266_uart.h"
#endif

#ifndef LV_DISPALY
#include "lv_port_disp.h"
#endif

int main(void)
{ 
	
	HAL_Init();                    	 	   
	Stm32_Clock_Init(RCC_PLL_MUL9);//72M
	delay_init(72);         //DELAY
	uart_init(115200);				//UART
	LED_Init();							//LED
	KEY_Init();							//KEY
	
#if LVGL_FUNC
	/*lvgl的1ms心跳*/
	TIM3_Init(999,71);	
	/*little vGL init*/
	lv_init();
	/*LCD映射到LVGL*/
	lv_port_disp_init();
	/*init end*/
	/*userinit*/
	lv_demo_keypad_encoder();
	lv_ex_get_started_3();
#endif
	
#ifndef ST7789_SPI
#if !LVGL_FUNC
	st7789_Lcd_Init();

	ST7789_LCD_ShowChinese_Search(12,76,WHITE,(u8*)"二");
	ST7789_LCD_ShowNum(20,1,23,2,24,WHITE);
	//ST7789_LCD_ShowChinese(12,76,0,16,WHITE);
#endif
#endif

#if ESP8266_FUNC
	esp8266_init();
#endif
	
	while(1)
	{
#if LVGL_FUNC
		lv_task_handler();
#endif
		LED1=!LED1;
		delay_ms(50);

	}
}

