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
#include "appstart.h"/*�豸����ͷ*/

/*
��ӡ���⣺

���ļ�����ΪASN����,ע������ӡ�ַ����������,ͬʱ��֤KEIL5ΪGB2312����.
�ټ��±������ΪASN����;
��KEIL5�����ΪGB2312 --- �����ӡ�쳣.

��ʾ���⣺

���ļ����ܵ���st7789�ֿ���ʾ���������ڱ���ΪUTF8������ƫ�Ʋ�һ������ʾ�쳣.
����st7789���ڻص���ʾ�����׺���ʹ��.
������GB2312�����ʽ������ʾ�쳣��ָ��ƫ�������㣬�Ƚϸ��ӣ����Ծ�����Ҫ���ļ����롣

2020-7-27
�����

���ü��±�����ΪANSI��ʽ�ļ�;
��MDK5����ΪGB2312��ʽ.
*/

/*
��ʱ��Ŀ����ʹ��
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
	/*��ʱ��Ŀ����*/
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
	/*lvgl��1ms����*/
	
#if TIM_FUNC	
	TIM3_Init(999,71);	
	TIM_ON_OFF_IT(TIM3_Handler, true);
#endif	
	
	/*little vGL init*/
	lv_init();
	/*LCDӳ��LVGL*/
	lv_port_disp_init();
	/*init end*/
	/*userinit*/
	lv_demo_keypad_encoder();
	lv_ex_get_started_3();
#endif

#ifndef ST7789_SPI
#if !LVGL_FUNC

#if UART_FUNC
	UART2_apTrace("�豸��������ʼ������ģ���У�");
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
	UART2_apTrace("��ӭʹ�ù¶�֢��ͯ����ϵͳ��");
#endif

	#if 1
	/*�豸��*/
	#define displaybaseaddr 12
	#define displaycolor YELLOW/*"�¶�֢��ͯ�����豸"*/
	ST7789_LCD_ShowChinese(displaybaseaddr+0 +0,20,0,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*1,20,1,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*2,20,2,24,displaycolor);
	ST7789_LCD_ShowChinese(displaybaseaddr+24*3,20,3,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*4,20,4,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*5,20,5,24,displaycolor);
	ST7789_LCD_ShowChinese(displaybaseaddr+24*6,20,6,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*7,20,7,24,displaycolor);ST7789_LCD_ShowChinese(displaybaseaddr+24*8,20,8,24,displaycolor);
	#else
	ST7789_LCD_ShowChinese_Search(50,20,WHITE,(u8*)"�¶�֢��ͯ�����豸");
	#endif
	/*UTF8������ʾ����*/
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
			if(main_param_t.runstatus == true)/*����Ϣ����*/
			{
				main_param_t.anim_count_rec_msg+=1;
				if(main_param_t.anim_count_rec_msg > 4)main_param_t.anim_count_rec_msg = 1;
				st7789_rec_msg_to_notation(main_param_t.anim_count_rec_msg);
			}
			else if(main_param_t.runstatus == false)/*��������*/
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

