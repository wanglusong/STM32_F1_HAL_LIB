#include "st7789_spi.h"
#include "stdlib.h"
#include "delay.h"

/*
该文件为UTF8格式,不要乱改，否则显示字库异常.
*/

#ifndef ST7789_SPI
#include "st7789_font.h"
#include "string.h"
#include "st7789_img.h"

#if UART_FUNC
#include "uartall.h"
#endif

#if TIM_FUNC
#include "tim.h"
#endif

/*static func*/
static u32 mypow(u8 m,u8 n);
/*static param*/
static u16 BACK_COLOR,POINT_COLOR;   //画笔色

#if 0
const unsigned char *img_show_msg1 = &gImage_st7789_rec_msg1[7200]; 
const unsigned char *img_show_msg2 = &gImage_st7789_rec_msg2[7200]; 
const unsigned char *img_show_msg3 = &gImage_st7789_rec_msg3[7200]; 
const unsigned char *img_show_msg4 = &gImage_st7789_rec_msg4[7200]; 
#endif

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
#if LCD_DRAWRECTANGLE	 
	 st7789_Lcd_DrawRectangle(5, 5, 235, 235, POINT_COLOR);
#endif
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

#ifndef ST7789_LVGL

//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void st7789_Lcd_Fill(u16 x,u16 y,u16 color)
{          
	LCD_DrawPoint(x,y);
	LCD_WR_DATA(color);//设置光标位置 	    			  	    
}
#else

//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void st7789_Lcd_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//设置光标位置 	    
	} 					  	    
}  

//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"
//mode:叠加方式(1)还是非叠加方式(0)
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"

//mode:叠加方式(1)还是非叠加方式(0)
void ST7789_LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u8 size,u16 color)
{  
  u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=st7789_asc2_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=st7789_asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=st7789_asc2_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPoint(x,y,color);
			else if(mode==0)LCD_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=LCD_H)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=LCD_W)return;	//超区域了
				break;
			}
		}  	 
	}  
}  

//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void ST7789_LCD_ShowString(u16 x,u16 y,const u8 *p, u8 size, u16 color)
{         
    while(*p!='\0')
    {       
        if(x>LCD_W-size){x=0;y+=size;}
        if(y>LCD_H-size){y=x=0;st7789_Lcd_Clear(BACK_COLOR);}
        ST7789_LCD_ShowChar(x,y,*p,0,size,color);
        x+=8;
        p++;
    }  
}

//显示数字
//x,y :起点坐标	 
//len :数字的位数
//color:颜色
//num:数值(0~4294967295);	
void ST7789_LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 color)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				ST7789_LCD_ShowChar(x+(size/2)*t,y,' ',0, size, color);
				continue;
			}else enshow=1; 
		 	 
		}
	 	ST7789_LCD_ShowChar(x+(size/2)*t,y,temp+'0',0 ,size, color); 
	}
} 

//在指定位置显示一个汉字
//size:字体大小--16 --24 --32
void ST7789_LCD_ShowChinese(unsigned int x,unsigned int y,unsigned char index,u16 size, u16 color)	
{  
	unsigned char i,j;
	unsigned char *temp=ST7789_Hzk;  
	unsigned char sizepoint;
    Address_set(x,y,x+(size-1),y+(size-1)); //设置区域 

	if(size == 16)
	{
		temp+=index*(size*2);
		sizepoint = size*2;		
	}
	else if(size == 24)
	{
		temp+=index*(size*3);	
		sizepoint = size*3;	
	}		
	else if(size == 32)
	{
		temp+=index*(size*4);
		sizepoint = size*4;
	}
	
	for(j=0;j<sizepoint;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
		 	if((*temp&(1<<i))!=0)
			{
				LCD_WR_DATA(color);
			} 
			else
			{
				LCD_WR_DATA(BACK_COLOR);
			}   
		}
		temp++;
	 }
	
}
/*查询方式填充汉字*/
void ST7789_LCD_ShowChinese_Search(u16 x, u16 y, u16 color, u8 *s)
{
	unsigned char i,j;
	unsigned short k;
	u16 HZnum;
	HZnum=sizeof(FONT_16)/sizeof(st7789_typFNT_GBK16);
	while(*s) 
	{	
		if((*s) >= 128) 
		{		
			for (k=0;k<HZnum;k++) 
			{
//			  #if 1/*UTF8编码*/
//			  if ((FONT_16[k].Index[0]==*(s))&&(FONT_16[k].Index[1]==*(s+1))&&(FONT_16[k].Index[2]==*(s+2)))/*UIF8码时的偏移量，注意*/
//			  #endif
			  if ((FONT_16[k].Index[0]==*(s))&&(FONT_16[k].Index[1]==*(s+1)))
			  { 	
					Address_set(x,y,x+16-1,y+16-1);
				    for(i=0;i<16*2;i++)
				    {
						for(j=0;j<8;j++)
				    	{
							if(FONT_16[k].Msk[i]&(0x80>>j))	LCD_WR_DATA(color);
							else 
							{
							if (color!=BACK_COLOR) LCD_WR_DATA(BACK_COLOR);
							}
						}
					}
					x+=16;
					break;
				}
//			  delay_ms(50);/*调试使用*/
			}
//			#if 1
//			s+=3;/*UIF8码时的偏移量，注意*/
//			#endif
			
			s+=2;/*GB2312编码偏移量 文件格式ANSI*/
		}
		else
		s+=1; 
	}	
}

/*显示一张图片*/
void st7789_Lcd_Showpicture(u16 x, u16 y, u16 img_w, u16 img_h, bool opaclear,const unsigned char *p) //显示图片
{
  int i; 
	unsigned char picH,picL; 
	
	if(!opaclear)
	{
		Address_set(x,y,x+img_w-1,y+img_h-1);//窗口设置
		for(i=0;i<img_w*img_h;i++)
		{	
			picL=*(p+i*2);	//数据低位在前
			picH=*(p+i*2+1);				
			LCD_WR_DATA(picH<<8|picL);  						
		}	
	}
	else
	{
		st7789_Lcd_Fill(x , y, x+img_w, y+img_h, BACK_COLOR);/*清除IMG*/
	}
}

/*收到消息动画*/
void st7789_rec_msg_to_notation(char show_img)
{
	switch(show_img)
	{
		case 1:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, false, gImage_st7789_rec_msg1);
			break;
		}
		case 2:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, false, gImage_st7789_rec_msg2);
			break;
		}
		case 3:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, false, gImage_st7789_rec_msg3);
			break;
		}
		case 4:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, false, gImage_st7789_rec_msg4);
			break;
		}
		default:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, true, NULL);
			break;
		}
	}
}

/*待机动画*/
void st7789_sleep_msg_to_notation(char show_img)
{
	switch(show_img)
	{
		case 1:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, false, gImage_st7789_sleep_msg1);
			break;
		}
		case 2:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, false, gImage_st7789_sleep_msg2);
			break;
		}
		default:
		{
			st7789_Lcd_Showpicture(150, 160, 60, 60, true, NULL);
			break;
		}
	}
}

/*
启动UI配置
*/
void ST7789_Display_Launch(void)
{
	ST7789_LCD_ShowChinese_Search(120,60,GREEN,(u8*)"开心每一天");
	
	ST7789_LCD_ShowChinese_Search(20,100,BROWN,(u8*)"您输入的文字为");
	ST7789_LCD_ShowChar(132,100,':',0,16,BROWN);
	
	ST7789_LCD_ShowChinese_Search(36,140,LIGHTGREEN,(u8*)"当前好感度为");
	ST7789_LCD_ShowChar(132,140,':',0,16,LIGHTGREEN);/*:*/
	ST7789_LCD_ShowNum(148,140,0,3,16,LIGHTGREEN);/*输入接口*/
	ST7789_LCD_ShowChar(196,140,'%',0,16,LIGHTGREEN);/*%*/
	
	ST7789_LCD_ShowChinese_Search(36,190,MAGENTA,(u8*)"当前动态");
	ST7789_LCD_ShowChar(116,190,':',0,16,MAGENTA);/*:*/
}
#endif

//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void st7789_Lcd_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol, color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//画矩形
void st7789_Lcd_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
	st7789_Lcd_DrawLine(x1,y1,x2,y1, color);
	st7789_Lcd_DrawLine(x1,y1,x1,y2, color);
	st7789_Lcd_DrawLine(x1,y2,x2,y2, color);
	st7789_Lcd_DrawLine(x2,y1,x2,y2, color);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void st7789_Draw_Circle(u16 x0,u16 y0,u8 r, u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a, color);             //3           
		LCD_DrawPoint(x0+b,y0-a, color);             //0           
		LCD_DrawPoint(x0-a,y0+b, color);             //1       
		LCD_DrawPoint(x0-b,y0-a, color);             //7           
		LCD_DrawPoint(x0-a,y0-b, color);             //2             
		LCD_DrawPoint(x0+b,y0+a, color);             //4               
		LCD_DrawPoint(x0+a,y0-b, color);             //5
		LCD_DrawPoint(x0+a,y0+b, color);             //6 
		LCD_DrawPoint(x0-b,y0+a, color);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b, color);
	}
}

//m^n函数
static
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
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
	  POINT_COLOR=WHITE;/*赋予画笔颜色*/ 		
		st7789_Lcd_Clear(BACK_COLOR); //清屏
		
		LCD_WR_REG(0x29); //开启屏幕
} 

/*临时项目函数*/
void display_recnum_cb(u8 recnum)
{
	ST7789_LCD_ShowNum(148,140,recnum,3,16,LIGHTGREEN);/*输入接口*/
}

void module_rec_msg(u8 recnum, show_recnum func)
{
	if(recnum != 0)
	{
		func(recnum);
	}
}

void display_recfont_cb(u8 *pfont)
{
	ST7789_LCD_ShowChinese_Search(148,100,BROWN,(u8*)pfont);/*显示汉字*/
}

void module_rec_font_msg(u8 *pfont, show_recfont func)/*汉字消息*/
{
	if(pfont != NULL)
	{
		func(pfont);
	}
}

void main_run_task(void)
{
		if(uart_config_t.uart_state == true)
		{
			memcpy(uart_config_t.uart_deal_buf,uart_config_t.uart_buf,uart_config_t.uart_count);
			memset(uart_config_t.uart_buf,0,uart_config_t.uart_count);
			
			uart_config_t.uart_state = false;
			/*数字处理区*/
			if(uart_config_t.uart_deal_buf[11] < 128 && uart_config_t.uart_deal_buf[12] < 128)/*表示是数字*/
			{
				if(uart_config_t.uart_deal_buf[13] == 0)
				{
					main_param_t.rec_num = (uart_config_t.uart_deal_buf[11] - 0x30)*10 + uart_config_t.uart_deal_buf[12] - 0x30;
				}
				else
				{
					main_param_t.rec_num = (uart_config_t.uart_deal_buf[11] - 0x30)*100 + (uart_config_t.uart_deal_buf[12] - 0x30)*10 
						+ uart_config_t.uart_deal_buf[13] - 0x30;
				}
				if(main_param_t.rec_num <= 100)
				module_rec_msg(main_param_t.rec_num,(show_recnum*)display_recnum_cb);
				UART3_apTrace("%d",main_param_t.rec_num );
				main_param_t.rec_num = 0;
				main_param_t.runstatus = true;
				uart_config_t.uart_count = 0;
				
				/*启动计时*/
				u8 time_status = Get_TIM_State(&TIM5_Handler);
				if(time_status == HAL_TIM_STATE_READY)
				{
					TIM_ON_OFF_IT(&TIM5_Handler,true);
					tim_config_t.TIM5_Status = true;
				}
			}
			else if(uart_config_t.uart_deal_buf[11] >= 128)/*汉字区域*/
			{
				strncpy((char*)main_param_t.rec_Chinese, (char*)uart_config_t.uart_deal_buf + 11,  (uart_config_t.uart_count - 11));/*检索出现汉字的地方*/
				module_rec_font_msg((u8 *)main_param_t.rec_Chinese, (show_recfont*)display_recfont_cb);/*显示汉字 main_param_t.rec_Chinese*/
				UART3_apTrace("%s",main_param_t.rec_Chinese);
				
				main_param_t.runstatus = true;
				uart_config_t.uart_count = 0;
				
				/*启动计时*/
				u8 time_status = Get_TIM_State(&TIM5_Handler);
				if(time_status == HAL_TIM_STATE_READY)
				{
					TIM_ON_OFF_IT(&TIM5_Handler,true);
					tim_config_t.TIM5_Status = true;
				}
				/*播报语音*/
				UART2_apTrace("%s",main_param_t.rec_Chinese);
				/*复位数据*/
				memset(main_param_t.rec_Chinese, 0, sizeof(main_param_t.rec_Chinese));
				
			}
			
		}
		
		if(main_param_t.runstatus == true)/*有消息动画*/
		{
			main_param_t.anim_count_rec_msg++;
			if(main_param_t.anim_count_rec_msg > 4)main_param_t.anim_count_rec_msg = 1;
			st7789_rec_msg_to_notation(main_param_t.anim_count_rec_msg);
		}
		
		if(main_param_t.runstatus == false)/*待机动画*/
		{
			main_param_t.anim_count_sleep_msg++;
			if(main_param_t.anim_count_sleep_msg > 2)main_param_t.anim_count_sleep_msg = 1;
			st7789_sleep_msg_to_notation(main_param_t.anim_count_sleep_msg);
		}

}
#endif

