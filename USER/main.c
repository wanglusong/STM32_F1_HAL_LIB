#include "sys.h"
#include "delay.h"
#include "uartall.h"
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
	/*param*/
	u8 anim_count_rec_msg = 0;
	u8 anim_count_sleep_msg = 0;
	
	HAL_Init();                    	 	   
	Stm32_Clock_Init(RCC_PLL_MUL9);//72M
	delay_init(72);         //DELAY
	
	uart1_init(115200);				//UART
	uart2_init(9600);
	
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

#if UART_FUNC
	UART2_apTrace("欢迎使用孤独症儿童康复系统");
#endif

	st7789_Lcd_Init();
	ST7789_LCD_ShowString(60,100,(u8 *)"ESP8266 Init...",16,WHITE);
#if ESP8266_FUNC
	UART_IRQ_FUNC(&UART1_Handler,false);
	esp8266_init();
	st7789_Lcd_Clear(BLACK);
	UART_IRQ_FUNC(&UART1_Handler,true);
#endif

#if UART_FUNC
	UART2_apTrace("设备启动中");
#endif

	#if 1
	/*设备名*/
	#define displaybaseaddr 12
	#define displaycolor YELLOW/*"孤独症儿童康复设备"*/
	ST7789_LCD_ShowChinese(displaybaseaddr+0 +0,20,0,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*1,20,1,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*2,20,2,24,displaycolor);
	ST7789_LCD_ShowChinese(displaybaseaddr+24*3,20,3,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*4,20,4,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*5,20,5,24,displaycolor);
	ST7789_LCD_ShowChinese(displaybaseaddr+24*6,20,6,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*7,20,7,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*8,20,8,24,displaycolor);
	#else
	ST7789_LCD_ShowChinese_Search(50,20,WHITE,(u8*)"孤独症儿童康复设备");
	#endif
	ST7789_LCD_ShowChinese_Search(120,60,GREEN,(u8*)"开心每一天");
	
	ST7789_LCD_ShowChinese_Search(20,100,BROWN,(u8*)"您输入的文字为");
	ST7789_LCD_ShowChar(132,100,':',0,16,BROWN);
	
	ST7789_LCD_ShowChinese_Search(36,140,LIGHTGREEN,(u8*)"当前好感度为");
	ST7789_LCD_ShowChar(132,140,':',0,16,LIGHTGREEN);/*:*/
	ST7789_LCD_ShowNum(148,140,100,3,16,LIGHTGREEN);/*输入接口*/
	ST7789_LCD_ShowChar(196,140,'%',0,16,LIGHTGREEN);/*%*/
	
	ST7789_LCD_ShowChinese_Search(36,190,MAGENTA,(u8*)"当前动态");
	ST7789_LCD_ShowChar(116,190,':',0,16,MAGENTA);/*:*/
	
#endif
#endif
	
	while(1)
	{
#if LVGL_FUNC
		lv_task_handler();
#endif
		
//		anim_count_rec_msg++;
//		if(anim_count_rec_msg > 4)anim_count_rec_msg = 1;
//		st7789_rec_msg_to_notation(anim_count_rec_msg);
		
		delay_ms(500);
		
		anim_count_sleep_msg++;
		if(anim_count_sleep_msg > 2)anim_count_sleep_msg = 1;
		st7789_sleep_msg_to_notation(anim_count_sleep_msg);
		
		LED1 = !LED1;

	}
}

