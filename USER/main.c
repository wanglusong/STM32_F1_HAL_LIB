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

extern unsigned long frequency;

typedef struct TEA5767_T
{
	u32 tea5767_freq;
	u8 tea5767_vloume;
	u8 mode;
}TEA5767_func;

TEA5767_func TEA5767_func_t;


int main(void)
{ 
	u8 key;
	
	memset(&TEA5767_func_t,0,sizeof(TEA5767_func));
	
	HAL_Init();                    	 	//初始化HAL库    
	Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               		//初始化延时函数
	uart_init(115200);					//初始化串口
	usmart_dev.init(84); 		  	  	//初始化USMART	
	LED_Init();							//初始化LED	
	KEY_Init();							//初始化按键
 	LCD_Init();							//初始化LCD
 	mem_init();							//初始化内存池
	
	exfuns_init();						//为fatfs相关变量申请内存  
  f_mount(fs[0],"0:",1); 				//挂载SD卡 
 	f_mount(fs[1],"1:",1); 				//挂载FLASH.
	while(font_init()) 					//检查字库
	{  
		LCD_Clear(WHITE);		   		//清屏
 		POINT_COLOR=RED;				//设置字体为红色	   	   	  
		LCD_ShowString(30,50,200,16,16,"Mini  STM32");
		while(SD_Init())				//检测SD卡
		{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(30,70,200,16,16,"SD Card OK");
		LCD_ShowString(30,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//更新字库
		while(key)//更新失败		
		{			 		  
			LCD_ShowString(30,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//清屏	       
	}  
	POINT_COLOR=RED;       
	Show_Str(70,50,200,16,"扩音系统从机",16,0);			

	TEA5767_func_t.tea5767_freq = 92000;//100142 滨海电台
		    	 
	Show_Str(50,90,200,16,"当前频道：",16,0);		
	LCD_ShowxNum(50+5*16,90,TEA5767_func_t.tea5767_freq/1000,3,16,0);	
	Show_Str(50+5*16+16+8,90,200,16,".",16,0);
	LCD_ShowxNum(50+5*16+16+8+8,90,TEA5767_func_t.tea5767_freq%1000,3,16,0);

	Show_Str(50,130,200,16,"当前音量：",16,0);
			    	 
	Show_Str(50,170,200,16,"信号强度：",16,0);		
	
	Show_Str(50,210,200,16,"当前模式：",16,0);		
	
	Show_Str(50+5*16,210,200,16,"手动",16,0);	

	IIC_Init();	//IIC接口初始化	
	
	Set_Frequency(TEA5767_func_t.tea5767_freq); //设置电台频率为101.8MHz
	
	printf("system is starting\r\n");
	
	while(1)
	{

		 key=KEY_Scan(0);
		 if(key)
		{
			printf("key is = %d\r\n",key);
			
			switch(key)
			{
				case 2:
				{
					if(TEA5767_func_t.mode == 1)
					{
						Auto_Search(1);//自动向上搜索
					}else
					{
						Search(1);  //手动向上搜索
					}
					
					TEA5767_func_t.tea5767_freq = frequency;
					
					LCD_ShowxNum(50+5*16,90,TEA5767_func_t.tea5767_freq/1000,3,16,0);	
					Show_Str(50+5*16+16+8,90,200,16,".",16,0);
					LCD_ShowxNum(50+5*16+16+8+8,90,TEA5767_func_t.tea5767_freq%1000,3,16,0);
					
					key = 0;
					break;
				}
				case 3:
				{
					if(TEA5767_func_t.mode == 1)
					{
						Auto_Search(0);//自动向下搜索
					}else
					{
						Search(0);  //手动向下搜索
					}
					
					TEA5767_func_t.tea5767_freq = frequency;
					
					LCD_ShowxNum(50+5*16,90,TEA5767_func_t.tea5767_freq/1000,3,16,0);	
					Show_Str(50+5*16+16+8,90,200,16,".",16,0);
					LCD_ShowxNum(50+5*16+16+8+8,90,TEA5767_func_t.tea5767_freq%1000,3,16,0);							
					key = 0;
					break;
				}
				case 1:
				{
					TEA5767_func_t.mode = ! TEA5767_func_t.mode;
					
					if(TEA5767_func_t.mode == 0)
					{
						Show_Str(50+5*16,210,200,16,"手动",16,0);	
					}else
					{
						Show_Str(50+5*16,210,200,16,"自动",16,0);	
					}
					key = 0;
					break;
				}
			}
		}

		LED0=!LED0;
		delay_ms(50);

	}
}

