#ifndef _ST7735_SPI_H
#define _ST7735_SPI_H

#include "sys.h"
#include "lcd_config.h"

#ifndef ST7735_SPI

/*
PB7 连接至TFT -BLK
PB8连接至TFT --DC
PB9 连接至TFT --CS
PB12连接至TFT --RST
PB13连接至TFT -- SCL
PB15连接至TFT - SDA
*/

//LCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令	 
}st7735_lcd_dev; 	

//支持横竖屏快速定义切换，支持8/16位模式切换
#define USE_HORIZONTAL  	0	//定义是否使用横屏 		0,不使用.1,使用.

//使用硬件SPI 还是模拟SPI作为测试
#define USE_HARDWARE_SPI    1  //1:Enable Hardware SPI;0:USE Soft SPI

//定义LCD的尺寸
#if USE_HORIZONTAL==1	//使用横屏
#define LCD_W 320
#define LCD_H 240
#else
#define LCD_W 240
#define LCD_H 320
#endif

//-----------------LCD端口定义---------------- 
//QDtech全系列模块采用了三极管控制背光亮灭，用户也可以接PWM调节背光亮度
#define ST7735_LED        	GPIO_PIN_7  //PB7 连接至TFT -LED
//接口定义在Lcd_Driver.h内定义，请根据接线修改并修改相应IO初始化LCD_GPIO_Init()
#define ST7735_CTRL   	  	GPIOB		//定义TFT数据端口
#define ST7735_RS         	GPIO_PIN_8	//PB8连接至TFT --RS
#define ST7735_CS        		GPIO_PIN_9 	//PB9 连接至TFT --CS
#define ST7735_RST     			GPIO_PIN_12	//PB12连接至TFT --RST
#define ST7735_SCL        	GPIO_PIN_13	//PB13连接至TFT -- CLK
#define ST7735_SDA        	GPIO_PIN_15	//PB15连接至TFT - SDI

//液晶控制口置1操作语句宏定义
#define	ST7735_CS_SET  		ST7735_CTRL->BSRR=ST7735_CS    
#define	ST7735_RS_SET  		ST7735_CTRL->BSRR=ST7735_RS    
#define	ST7735_SDA_SET  	ST7735_CTRL->BSRR=ST7735_SDA    
#define	ST7735_SCL_SET  	ST7735_CTRL->BSRR=ST7735_SCL    
#define	ST7735_RST_SET  	ST7735_CTRL->BSRR=ST7735_RST    
#define	ST7735_LED_SET  	ST7735_CTRL->BSRR=ST7735_LED   

//液晶控制口置0操作语句宏定义
#define	ST7735_CS_CLR  	  ST7735_CTRL->BRR=ST7735_CS    
#define	ST7735_RS_CLR  	  ST7735_CTRL->BRR=ST7735_RS    
#define	ST7735_SDA_CLR  	ST7735_CTRL->BRR=ST7735_SDA    
#define	ST7735_SCL_CLR  	ST7735_CTRL->BRR=ST7735_SCL    
#define	ST7735_RST_CLR  	ST7735_CTRL->BRR=ST7735_RST    
#define	ST7735_LED_CLR  	ST7735_CTRL->BRR=ST7735_LED 

//画笔颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色

//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
#define LIGHTGREEN     	0X841F //浅绿色
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)

/*extern func*/
void ST7735_Init(void);	
void ST7735_LCD_Clear(u16 Color);
void ST7735_LCD_Fill(u16 sx,u16 sy,u16 color);

#endif

#endif

