#ifndef __ST7789_SPI_H_
#define __ST7789_SPI_H_

#include "sys.h"

#ifndef ST7789_SPI

#define LCD_W 240
#define LCD_H 240

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

//-----------------OLED端口定义----------------  					   
#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET)//CLK
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET)//DIN
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET)

#define OLED_RST_Clr() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET)//RES
#define OLED_RST_Set() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)
 		     
#define OLED_BLK_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET)//BLK
#define OLED_BLK_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define LCD_DRAWRECTANGLE 1 /*开启外围显示框---显示屏显示一个矩阵框*/

void st7789_Lcd_Init(void); 
void st7789_Lcd_Clear(u16 Color);

#define ST7789_LVGL
#ifndef ST7789_LVGL

void st7789_Lcd_Fill(u16 x,u16 y,u16 color);

#else
//清屏
void st7789_Lcd_Clear(u16 Color);
//填充
void st7789_Lcd_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
//画线
void st7789_Lcd_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
//画矩形
void st7789_Lcd_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
//在指定位置画一个指定大小的圆
void st7789_Draw_Circle(u16 x0,u16 y0,u8 r, u16 color);
//固定方式写汉字
void ST7789_LCD_ShowChinese(unsigned int x,unsigned int y,unsigned char index,u16 size, u16 color);
//指针查询方式写汉字
void ST7789_LCD_ShowChinese_Search(u16 x, u16 y, u16 color, u8 *s);
//写字符
void ST7789_LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u8 size,u16 color);
//写字符串
void ST7789_LCD_ShowString(u16 x,u16 y,const u8 *p, u8 size, u16 color);
//写数字
void ST7789_LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color);
//显示一张图片
void st7789_Lcd_Showpicture(u16 x, u16 y, u16 img_w, u16 img_h, bool opaclear,const unsigned char *p);
//点	
u32 mypow(u8 m,u8 n);
/*收到消息动画*/
void st7789_rec_msg_to_notation(char show_img);
/*待机动画*/
void st7789_sleep_msg_to_notation(char show_img);

#endif

#endif

#endif
