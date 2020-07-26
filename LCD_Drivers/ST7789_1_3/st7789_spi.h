#ifndef __ST7789_SPI_H_
#define __ST7789_SPI_H_

#include "main.h"

#ifndef ST7789_SPI

/*
���ļ�ΪUTF8��ʽ,��Ҫ�Ҹģ�������ʾ�ֿ��쳣.
*/

#define LCD_W 240
#define LCD_H 240

//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

//-----------------OLED�˿ڶ���----------------  					   
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

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define LCD_DRAWRECTANGLE 1 /*������Χ��ʾ��---��ʾ����ʾһ�������*/

void st7789_Lcd_Init(void); 
void st7789_Lcd_Clear(u16 Color);

#define ST7789_LVGL
#ifndef ST7789_LVGL

void st7789_Lcd_Fill(u16 x,u16 y,u16 color);

#else
//����
void st7789_Lcd_Clear(u16 Color);
//���
void st7789_Lcd_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
//����
void st7789_Lcd_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
//������
void st7789_Lcd_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
//��ָ��λ�û�һ��ָ����С��Բ
void st7789_Draw_Circle(u16 x0,u16 y0,u8 r, u16 color);
//�̶���ʽд����
void ST7789_LCD_ShowChinese(unsigned int x,unsigned int y,unsigned char index,u16 size, u16 color);
//ָ���ѯ��ʽд����
void ST7789_LCD_ShowChinese_Search(u16 x, u16 y, u16 color, u8 *s);
//д�ַ�
void ST7789_LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u8 size,u16 color);
//д�ַ���
void ST7789_LCD_ShowString(u16 x,u16 y,const u8 *p, u8 size, u16 color);
//д����
void ST7789_LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color);
//��ʾһ��ͼƬ
void st7789_Lcd_Showpicture(u16 x, u16 y, u16 img_w, u16 img_h, bool opaclear,const unsigned char *p);
//��	
u32 mypow(u8 m,u8 n);
/*�յ���Ϣ����*/
void st7789_rec_msg_to_notation(char show_img);
/*��������*/
void st7789_sleep_msg_to_notation(char show_img);

/*����������*/
void ST7789_Display_Launch(void);

/*��ʱ��Ŀfunc*/
typedef void *show_recnum(u8 recnum);
typedef void *show_recfont(u8 *pfont);
/*���ִ�����*/
void display_recnum_cb(u8 recnum);
void module_rec_msg(u8 recnum, show_recnum func);/*������Ϣ*/
/*���ִ�����*/
void display_recfont_cb(u8 *pfont);
void module_rec_font_msg(u8 *pfont, show_recfont func);/*������Ϣ*/

void main_run_task(void);
#endif

#endif

#endif
