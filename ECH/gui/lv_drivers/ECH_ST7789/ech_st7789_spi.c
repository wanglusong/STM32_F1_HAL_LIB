#include "ech_st7789_spi.h"
#include "stdlib.h"
#include "ech_delay.h"

/*
该文件为UTF8格式,不要乱改，否则显示字库异常.
*/

#ifndef ST7789_SPI
#include "string.h"

#ifdef UART_FUNC
#include "ech_uartall.h"
#endif

#ifdef TIM_FUNC
#include "ech_tim.h"
#endif

/*static param*/
static u16 BACK_COLOR;   //画笔色
//static u16 POINT_COLOR;

static
void LCD_Writ_Bus(char dat)   //串行数据写入
{	
	u8 i;			  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}			
}

static
void LCD_WR_DATA8(char da) //发送数据-8位参数
{	
	//OLED_CS_Clr();
    OLED_DC_Set();
		LCD_Writ_Bus(da);  
	//OLED_CS_Set();
}  

static
void LCD_WR_DATA(int da)
{
	//OLED_CS_Clr();
		OLED_DC_Set();
		LCD_Writ_Bus(da>>8);
    LCD_Writ_Bus(da);
	//OLED_CS_Set();
}	  

static
void LCD_WR_REG(char da)	 
{	//	OLED_CS_Clr();
    OLED_DC_Clr();
	LCD_Writ_Bus(da);
	//OLED_CS_Set();
}

#if 0
static
void LCD_WR_REG_DATA(int reg,int da)
{	
	//OLED_CS_Clr();
    LCD_WR_REG(reg);
		LCD_WR_DATA(da);
	//OLED_CS_Set();
}
#endif

static
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	 LCD_WR_REG(0x2a);
	 LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);					 						 
}

//清屏函数
//Color:要清屏的填充色
void st7789_Lcd_Clear(u16 Color)
{
	 u16 i,j;  	
	 Address_set(0,0,LCD_W-1,LCD_H-1);
   for(i=0;i<LCD_W;i++)
	 {
			for (j=0;j<LCD_H;j++)
			{
				LCD_WR_DATA(Color);	 			 
			}

	 }
}

//画点
//POINT_COLOR:此点的颜色
static
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	Address_set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(color); 	    
} 

#if 0
//画一个大点
//POINT_COLOR:此点的颜色
static
void LCD_DrawPoint_big(u16 x,u16 y,u16 color)
{
	st7789_Lcd_Fill(x-1,y-1,x+1,y+1,color);
}
#endif

//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void st7789_Lcd_Fill(u16 x,u16 y,u16 color)
{          
	LCD_DrawPoint(x,y,color);   			  	    
}		 

void st7789_Lcd_Init(void)
{
		GPIO_InitTypeDef GPIO_Initure;
	
		__HAL_RCC_GPIOB_CLK_ENABLE();           	//开启GPIOB时钟
		__HAL_RCC_GPIOC_CLK_ENABLE();           	//开启GPIOC时钟
	
    GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10; 			
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_SET);

	  GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8; 	
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速	
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8|GPIO_PIN_7,GPIO_PIN_SET);

	//OLED_CS_Clr();  //打开片选使能
	  OLED_RST_Clr();
		delay_ms(20);
		OLED_RST_Set();
		delay_ms(20);
		OLED_BLK_Set();
	
		//************* Start Initial Sequence **********// 
		LCD_WR_REG(0x36); 
		LCD_WR_DATA8(0x00);

		LCD_WR_REG(0x3A); 
		LCD_WR_DATA8(0x05);

		LCD_WR_REG(0xB2);
		LCD_WR_DATA8(0x0C);
		LCD_WR_DATA8(0x0C);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x33);
		LCD_WR_DATA8(0x33);

		LCD_WR_REG(0xB7); 
		LCD_WR_DATA8(0x35);  

		LCD_WR_REG(0xBB);
		LCD_WR_DATA8(0x19);

		LCD_WR_REG(0xC0);
		LCD_WR_DATA8(0x2C);

		LCD_WR_REG(0xC2);
		LCD_WR_DATA8(0x01);

		LCD_WR_REG(0xC3);
		LCD_WR_DATA8(0x12);   

		LCD_WR_REG(0xC4);
		LCD_WR_DATA8(0x20);  

		LCD_WR_REG(0xC6); 
		LCD_WR_DATA8(0x0F);    

		LCD_WR_REG(0xD0); 
		LCD_WR_DATA8(0xA4);
		LCD_WR_DATA8(0xA1);

		LCD_WR_REG(0xE0);
		LCD_WR_DATA8(0xD0);
		LCD_WR_DATA8(0x04);
		LCD_WR_DATA8(0x0D);
		LCD_WR_DATA8(0x11);
		LCD_WR_DATA8(0x13);
		LCD_WR_DATA8(0x2B);
		LCD_WR_DATA8(0x3F);
		LCD_WR_DATA8(0x54);
		LCD_WR_DATA8(0x4C);
		LCD_WR_DATA8(0x18);
		LCD_WR_DATA8(0x0D);
		LCD_WR_DATA8(0x0B);
		LCD_WR_DATA8(0x1F);
		LCD_WR_DATA8(0x23);

		LCD_WR_REG(0xE1);
		LCD_WR_DATA8(0xD0);
		LCD_WR_DATA8(0x04);
		LCD_WR_DATA8(0x0C);
		LCD_WR_DATA8(0x11);
		LCD_WR_DATA8(0x13);
		LCD_WR_DATA8(0x2C);
		LCD_WR_DATA8(0x3F);
		LCD_WR_DATA8(0x44);
		LCD_WR_DATA8(0x51);
		LCD_WR_DATA8(0x2F);
		LCD_WR_DATA8(0x1F);
		LCD_WR_DATA8(0x1F);
		LCD_WR_DATA8(0x20);
		LCD_WR_DATA8(0x23);

		LCD_WR_REG(0x21); 

		LCD_WR_REG(0x11); 
		//Delay (120); 
		
		BACK_COLOR=BLACK;/*赋予背景*/
	  //POINT_COLOR=WHITE;/*赋予画笔颜色*/ 		
		st7789_Lcd_Clear(BACK_COLOR); //清屏
		
		LCD_WR_REG(0x29); //开启屏幕
} 

#endif

