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
#include "tim.h"
#include "lvgl.h"
#include "lv_gui_main.h"
#include "lcd_config.h"
#include "lv_demo_keypad_encoder.h"
#include "appstart.h"/*设备配置头*/

/*
打印问题：

该文件编码为ASN编码,注意否则打印字符串是乱码的,同时保证KEIL5为GB2312编码.
①记事本打开另存为ASN编码;
②KEIL5编码改为GB2312 --- 解决打印异常.

显示问题：

该文件不能调用st7789字库显示函数，由于编码为UTF8，数据偏移不一样，显示异常.
①在st7789用于回调显示或者套函数使用.
②若换GB2312编码格式还是显示异常，指针偏移需重算，比较复杂，所以尽量不要改文件编码。

2020-7-27
解决：

①用记事本保存为ANSI格式文件;
②MDK5保存为GB2312格式.
*/

/*
临时项目定义使用
*/

MAIN_PARAM main_param_t;

/*----end---*/


#if ESP8266_FUNC
#include "esp8266_uart.h"
#endif

#ifndef LV_DISPALY
#include "lv_port_disp.h"
#endif

int main(void)
{ 
	/*临时项目参数*/
	memset(&main_param_t, 0, sizeof(MAIN_PARAM));
	
	HAL_Init();                    	 	   
	Stm32_Clock_Init(RCC_PLL_MUL9);//72M
	delay_init(72);         //DELAY

#if TIM_FUNC	
	TIM4_Init(999,719);/*10ms*/
	TIM5_Init(9999,7199);/*1s*/
#endif
	
#if UART_FUNC	
	uart1_init(9600);				//UART
	uart2_init(9600);
	uart3_init(9600);
#endif
	
	LED_Init();							//LED
	KEY_Init();							//KEY
	
#if LVGL_FUNC
	/*lvgl的1ms心跳*/
	
#if TIM_FUNC	
	TIM3_Init(999,71);	
	TIM_ON_OFF_IT(TIM3_Handler, true);
#endif	
	
	/*little vGL init*/
	lv_init();
	/*LCD映射LVGL*/
	lv_port_disp_init();
	/*init end*/
	/*userinit*/
	lv_demo_keypad_encoder();
	lv_ex_get_started_3();
#endif

#ifndef ST7789_SPI
#if !LVGL_FUNC

#if UART_FUNC
	UART2_apTrace("设备启动，初始化无线模块中！");
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
	UART2_apTrace("欢迎使用孤独症儿童康复系统！");
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
	/*UTF8编码显示区域*/
	ST7789_Display_Launch();
#endif
#endif
	
	while(1)
	{
#if LVGL_FUNC
		lv_task_handler();
#endif
		
		main_run_task();
		
		if(main_param_t.runcounttime >=50)
		{
			main_param_t.runcounttime = 0;
			delay_ms(10);
			if(main_param_t.runstatus == true)/*有消息动画*/
			{
				main_param_t.anim_count_rec_msg+=1;
				if(main_param_t.anim_count_rec_msg > 4)main_param_t.anim_count_rec_msg = 1;
				st7789_rec_msg_to_notation(main_param_t.anim_count_rec_msg);
			}
			else if(main_param_t.runstatus == false)/*待机动画*/
			{
				main_param_t.anim_count_sleep_msg+=1;
				if(main_param_t.anim_count_sleep_msg > 2)main_param_t.anim_count_sleep_msg = 1;
				st7789_sleep_msg_to_notation(main_param_t.anim_count_sleep_msg);
			}
			delay_ms(10);
			LED1 = !LED1;
		}
		delay_ms(10);
		
		main_param_t.runcounttime++;
		
	}
}

