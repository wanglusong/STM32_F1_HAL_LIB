#include "st7735_spi.h"
#include "delay.h"
#include "usart.h"

#ifndef ST7735_SPI

/*static func*/

static void ST7735_LCD_SetParam(void);
static void ST7735_LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

/*variable start*/

static st7735_lcd_dev st7735_lcddev;

/*variable end*/

#if USE_HARDWARE_SPI/*硬件spi*/

SPI_HandleTypeDef SPI2_Handler;  //SPI1句柄

/****************************************************************************
* 名    称：u8 ST7735_SPI_WriteByte(u8 TxData)
* 功    能：STM32_硬件SPI读写一个字节数据底层函数
* 入口参数：Byte
* 出口参数：返回总线收到的数据
* 说    明：STM32_硬件SPI读写一个字节数据底层函数
****************************************************************************/
static
u8 ST7735_SPI_WriteByte(u8 TxData)
{
	u8 Rxdata;
	HAL_SPI_TransmitReceive(&SPI2_Handler,&TxData,&Rxdata,1, 1000);       
 	return Rxdata;  	
} 

/****************************************************************************
* 名    称：void ST7735_SPI_SetSpeed(u8 SPI_BaudRatePrescaler)
* 功    能：设置SPI的速度
* 入口参数：SPI_BaudRatePrescaler
* 出口参数：无
* 说    明：SPI_BaudRatePrescaler
****************************************************************************/
void ST7735_SPI_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
    __HAL_SPI_DISABLE(&SPI2_Handler);            //关闭SPI
    SPI2_Handler.Instance->CR1&=0XFFC7;          //位3-5清零，用来设置波特率
    SPI2_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//设置SPI速度
    __HAL_SPI_ENABLE(&SPI2_Handler);             //使能SPI
} 

/****************************************************************************
* 名    称：ST7735_SPI2_Init(void)
* 功    能：STM32_SPI2硬件配置初始化
* 入口参数：无
* 出口参数：无
* 说    明：STM32_SPI2硬件配置初始化
****************************************************************************/
static
void ST7735_SPI2_Init(void)	
{
		GPIO_InitTypeDef GPIO_Initure;
	
		__HAL_RCC_GPIOB_CLK_ENABLE();           	//开启GPIOB时钟
	
    GPIO_Initure.Pin=ST7735_LED|ST7735_RS|ST7735_CS|ST7735_RST; 				//PB7-9,12
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(ST7735_CTRL,&GPIO_Initure);
		HAL_GPIO_WritePin(ST7735_CTRL,ST7735_LED|ST7735_RS|ST7735_CS|ST7735_RST,GPIO_PIN_RESET);
	
    SPI2_Handler.Instance=SPI2;                         //SPI2
    SPI2_Handler.Init.Mode=SPI_MODE_MASTER;             //设置SPI工作模式，设置为主模式
    SPI2_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //设置SPI单向或者双向的数据模式:SPI设置为双线模式
    SPI2_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI2_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //串行同步时钟的空闲状态为高电平
    SPI2_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    SPI2_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI2_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//定义波特率预分频的值:波特率预分频值为256
    SPI2_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI2_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //关闭TI模式
    SPI2_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//关闭硬件CRC校验
    SPI2_Handler.Init.CRCPolynomial=7;                  //CRC值计算的多项式
    HAL_SPI_Init(&SPI2_Handler);//初始化

    __HAL_SPI_ENABLE(&SPI2_Handler);                    //使能SPI2
		
		ST7735_SPI_WriteByte(0xff);
}

#else

/****************************************************************************
* 名    称：void  SPIv_WriteData(u8 Data)
* 功    能：STM32_模拟SPI写一个字节数据底层函数
* 入口参数：Data
* 出口参数：无
* 说    明：STM32_模拟SPI读写一个字节数据底层函数
****************************************************************************/
static
void  SPIv_WriteData(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
	  ST7735_SDA_SET; //输出数据
      else ST7735_SDA_CLR;
	   
      ST7735_SCL_CLR;       
      ST7735_SCL_SET;
      Data<<=1; 
	}
}

//******************************************************************
//函数名：  ST7735_LCD_GPIOInit
//作者：    wangls
//日期：    2020-07-18
//功能：    液晶屏IO初始化，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
static
void ST7735_LCD_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	      
	__HAL_RCC_GPIOB_CLK_ENABLE(); 
	
	GPIO_InitStructure.Pin = ST7735_RS| ST7735_CS| ST7735_RST| ST7735_SCL | ST7735_SDA | ST7735_LED;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull=GPIO_PULLUP; 
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(ST7735_CTRL,&GPIO_InitStructure);      
}

#endif

//******************************************************************
//函数名：  ST7735_LCD_WR_REG
//作者：    wangls
//日期：    2020-07-18
//功能：    向液晶屏总线写入写16位指令
//输入参数：Reg:待写入的指令值
//返回值：  无
//修改记录：无
//******************************************************************
static
void ST7735_LCD_WR_REG(u8 data)
{ 
   ST7735_CS_CLR;
   ST7735_RS_CLR;
#if USE_HARDWARE_SPI   
   ST7735_SPI_WriteByte(data);
#else
   SPIv_WriteData(data);
#endif 
   ST7735_CS_SET;
}

//******************************************************************
//函数名：  ST7735_LCD_WR_DATA
//作者：    wangls
//日期：    2020-07-18
//功能：    向液晶屏总线写入写8位数据
//输入参数：Data:待写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
static
void ST7735_LCD_WR_DATA(u8 data)
{
	
   ST7735_CS_CLR;
   ST7735_RS_SET;
#if USE_HARDWARE_SPI   
   ST7735_SPI_WriteByte(data);
#else
   SPIv_WriteData(data);
#endif 
   ST7735_CS_SET;

}
//******************************************************************
//函数名：  ST7735_LCD_WR_DATA_16Bit
//作者：    wangls
//日期：    2020-07-18
//功能：    8位总线下如何写入一个16位数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
static
void ST7735_LCD_WR_DATA_16Bit(u16 data)
{	
   ST7735_CS_CLR;
   ST7735_RS_SET;
#if USE_HARDWARE_SPI   
   ST7735_SPI_WriteByte(data>>8);
   ST7735_SPI_WriteByte(data);
#else
   SPIv_WriteData(data>>8);
   SPIv_WriteData(data);
#endif 
   ST7735_CS_SET;
}

//******************************************************************
//函数名：  ST7735_LCD_WriteReg
//作者：    wangls
//日期：    2020-07-18
//功能：    写寄存器数据
//输入参数：LCD_Reg:寄存器地址
//			LCD_RegValue:要写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
static
void ST7735_LCD_WriteReg(u8 LCD_Reg, u8 LCD_RegValue)
{	
	ST7735_LCD_WR_REG(LCD_Reg);  
	ST7735_LCD_WR_DATA(LCD_RegValue);	    		 
}	   


//******************************************************************
//函数名：  ST7735_LCD_WriteRAM_Prepare
//作者：    wangls
//日期：    2020-07-18
//功能：    开始写GRAM
//			在给液晶屏传送RGB数据前，应该发送写GRAM指令
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
static
void ST7735_LCD_WriteRAM_Prepare(void)
{
	ST7735_LCD_WR_REG(st7735_lcddev.wramcmd);
}	 

//******************************************************************
//函数名：  ST7735_LCD_RESET
//作者：    wangls
//日期：    2020-07-18
//功能：    LCD复位函数，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
static
void ST7735_LCD_RESET(void)
{
	ST7735_RST_CLR;
	delay_ms(100);	
	ST7735_RST_SET;
	delay_ms(50);
}

//******************************************************************
//函数名：  LCD_Init
//作者：    wangls
//日期：    2020-07-18
//功能：    LCD初始化
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void ST7735_Init(void)
{  
#if USE_HARDWARE_SPI //使用硬件SPI
	ST7735_SPI2_Init();
	//ST7735_SPI_SetSpeed(SPI_BAUDRATEPRESCALER_2);
#else	
	ST7735_LCD_GPIOInit();//使用模拟SPI
#endif  										 

 	ST7735_LCD_RESET(); //液晶屏复位

	//************* Start Initial Sequence **********//		
	//开始初始化液晶屏
	ST7735_LCD_WR_REG(0x11);//Sleep exit 
	delay_ms (120);		
	//ST7735R Frame Rate
	ST7735_LCD_WR_REG(0xB1); 
	ST7735_LCD_WR_DATA(0x01); 
	ST7735_LCD_WR_DATA(0x2C); 
	ST7735_LCD_WR_DATA(0x2D); 

	ST7735_LCD_WR_REG(0xB2); 
	ST7735_LCD_WR_DATA(0x01); 
	ST7735_LCD_WR_DATA(0x2C); 
	ST7735_LCD_WR_DATA(0x2D); 

	ST7735_LCD_WR_REG(0xB3); 
	ST7735_LCD_WR_DATA(0x01); 
	ST7735_LCD_WR_DATA(0x2C); 
	ST7735_LCD_WR_DATA(0x2D); 
	ST7735_LCD_WR_DATA(0x01); 
	ST7735_LCD_WR_DATA(0x2C); 
	ST7735_LCD_WR_DATA(0x2D); 
	
	ST7735_LCD_WR_REG(0xB4); //Column inversion 
	ST7735_LCD_WR_DATA(0x07); 
	
	//ST7735R Power Sequence
	ST7735_LCD_WR_REG(0xC0); 
	ST7735_LCD_WR_DATA(0xA2); 
	ST7735_LCD_WR_DATA(0x02); 
	ST7735_LCD_WR_DATA(0x84); 
	ST7735_LCD_WR_REG(0xC1); 
	ST7735_LCD_WR_DATA(0xC5); 

	ST7735_LCD_WR_REG(0xC2); 
	ST7735_LCD_WR_DATA(0x0A); 
	ST7735_LCD_WR_DATA(0x00); 

	ST7735_LCD_WR_REG(0xC3); 
	ST7735_LCD_WR_DATA(0x8A); 
	ST7735_LCD_WR_DATA(0x2A); 
	ST7735_LCD_WR_REG(0xC4); 
	ST7735_LCD_WR_DATA(0x8A); 
	ST7735_LCD_WR_DATA(0xEE); 
	
	ST7735_LCD_WR_REG(0xC5); //VCOM 
	ST7735_LCD_WR_DATA(0x0E); 
	
	ST7735_LCD_WR_REG(0x36); //MX, MY, RGB mode 				 
	ST7735_LCD_WR_DATA(0xC8); 
	
	//ST7735R Gamma Sequence
	ST7735_LCD_WR_REG(0xe0); 
	ST7735_LCD_WR_DATA(0x0f); 
	ST7735_LCD_WR_DATA(0x1a); 
	ST7735_LCD_WR_DATA(0x0f); 
	ST7735_LCD_WR_DATA(0x18); 
	ST7735_LCD_WR_DATA(0x2f); 
	ST7735_LCD_WR_DATA(0x28); 
	ST7735_LCD_WR_DATA(0x20); 
	ST7735_LCD_WR_DATA(0x22); 
	ST7735_LCD_WR_DATA(0x1f); 
	ST7735_LCD_WR_DATA(0x1b); 
	ST7735_LCD_WR_DATA(0x23); 
	ST7735_LCD_WR_DATA(0x37); 
	ST7735_LCD_WR_DATA(0x00); 	
	ST7735_LCD_WR_DATA(0x07); 
	ST7735_LCD_WR_DATA(0x02); 
	ST7735_LCD_WR_DATA(0x10); 

	ST7735_LCD_WR_REG(0xe1); 
	ST7735_LCD_WR_DATA(0x0f); 
	ST7735_LCD_WR_DATA(0x1b); 
	ST7735_LCD_WR_DATA(0x0f); 
	ST7735_LCD_WR_DATA(0x17); 
	ST7735_LCD_WR_DATA(0x33); 
	ST7735_LCD_WR_DATA(0x2c); 
	ST7735_LCD_WR_DATA(0x29); 
	ST7735_LCD_WR_DATA(0x2e); 
	ST7735_LCD_WR_DATA(0x30); 
	ST7735_LCD_WR_DATA(0x30); 
	ST7735_LCD_WR_DATA(0x39); 
	ST7735_LCD_WR_DATA(0x3f); 
	ST7735_LCD_WR_DATA(0x00); 
	ST7735_LCD_WR_DATA(0x07); 
	ST7735_LCD_WR_DATA(0x03); 
	ST7735_LCD_WR_DATA(0x10);  
	
	ST7735_LCD_WR_REG(0x2a);
	ST7735_LCD_WR_DATA(0x00);
	ST7735_LCD_WR_DATA(0x00);
	ST7735_LCD_WR_DATA(0x00);
	ST7735_LCD_WR_DATA(0x7f);

	ST7735_LCD_WR_REG(0x2b);
	ST7735_LCD_WR_DATA(0x00);
	ST7735_LCD_WR_DATA(0x00);
	ST7735_LCD_WR_DATA(0x00);
	ST7735_LCD_WR_DATA(0x9f);
	
	ST7735_LCD_WR_REG(0xF0); //Enable test command  
	ST7735_LCD_WR_DATA(0x01); 
	ST7735_LCD_WR_REG(0xF6); //Disable ram power save mode 
	ST7735_LCD_WR_DATA(0x00); 
	
	ST7735_LCD_WR_REG(0x3A); //65k mode 
	ST7735_LCD_WR_DATA(0x05); 	
	ST7735_LCD_WR_REG(0x29);//Display on	

	ST7735_LCD_SetParam();//设置LCD参数	 
	ST7735_LCD_Clear(WHITE);		
	ST7735_LED_SET;//点亮背光	

}

//******************************************************************
//函数名：  LCD_Clear
//作者：    wangls
//日期：    2020-07-18
//功能：    LCD全屏填充清屏函数
//输入参数：Color:要清屏的填充色
//返回值：  无
//修改记录：无
//******************************************************************
void ST7735_LCD_Clear(u16 Color)
{
	u16 i,j;      
	ST7735_LCD_SetWindows(0,0,st7735_lcddev.width-1,st7735_lcddev.height-1);	  
	for(i=0;i<st7735_lcddev.width;i++)
	{
		for(j=0;j<st7735_lcddev.height;j++)
		ST7735_LCD_WR_DATA_16Bit(Color);	//写入数据 	 
	}
}   		  
/*************************************************
函数名：ST7735_LCD_SetWindows
功能：设置lcd显示窗口，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
static
void ST7735_LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
#if USE_HORIZONTAL==1	//使用横屏
	ST7735_LCD_WR_REG(st7735_lcddev.setxcmd);	
	ST7735_LCD_WR_DATA(xStar>>8);
	ST7735_LCD_WR_DATA(0x00FF&xStar+3);		
	ST7735_LCD_WR_DATA(xEnd>>8);
	ST7735_LCD_WR_DATA(0x00FF&xEnd+3);

	ST7735_LCD_WR_REG(st7735_lcddev.setycmd);	
	ST7735_LCD_WR_DATA(yStar>>8);
	ST7735_LCD_WR_DATA(0x00FF&yStar+2);		
	ST7735_LCD_WR_DATA(yEnd>>8);
	ST7735_LCD_WR_DATA(0x00FF&yEnd+2);	

#else
	
	ST7735_LCD_WR_REG(st7735_lcddev.setxcmd);	
	ST7735_LCD_WR_DATA(xStar>>8);
	ST7735_LCD_WR_DATA(0x00FF&xStar+2);		
	ST7735_LCD_WR_DATA(xEnd>>8);
	ST7735_LCD_WR_DATA(0x00FF&xEnd+2);

	ST7735_LCD_WR_REG(st7735_lcddev.setycmd);	
	ST7735_LCD_WR_DATA(yStar>>8);
	ST7735_LCD_WR_DATA(0x00FF&yStar+3);		
	ST7735_LCD_WR_DATA(yEnd>>8);
	ST7735_LCD_WR_DATA(0x00FF&yEnd+3);	
#endif

	ST7735_LCD_WriteRAM_Prepare();	//开始写入GRAM				
}   

/*************************************************
ST7735_LCD_SetCursor
功能：设置光标位置
入口参数：xy坐标
返回值：无
*************************************************/
void ST7735_LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			 
#if USE_HORIZONTAL==1	//使用横屏
	ST7735_LCD_WR_REG(st7735_lcddev.setxcmd);	
	ST7735_LCD_WR_DATA(Xpos>>8);
	ST7735_LCD_WR_DATA(0xFF&Xpos);	//3	

	ST7735_LCD_WR_REG(st7735_lcddev.setycmd);		
	ST7735_LCD_WR_DATA(Ypos>>8);
	ST7735_LCD_WR_DATA(0xFF&Ypos);//2	

#else
	
	ST7735_LCD_WR_REG(st7735_lcddev.setxcmd);	
	ST7735_LCD_WR_DATA(Xpos>>8);
	ST7735_LCD_WR_DATA(0xFF&Xpos+2);//2		

	ST7735_LCD_WR_REG(st7735_lcddev.setycmd);		
	ST7735_LCD_WR_DATA(Ypos>>8);
	ST7735_LCD_WR_DATA(0xFF&Ypos+3);//3	
#endif	
} 

//设置LCD参数
//方便进行横竖屏模式切换
static
void ST7735_LCD_SetParam(void)
{ 	
	st7735_lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//使用横屏	  
	st7735_lcddev.dir=1;//横屏
	st7735_lcddev.width=128;
	st7735_lcddev.height=128;
	st7735_lcddev.setxcmd=0x2A;
	st7735_lcddev.setycmd=0x2B;			
	ST7735_LCD_WriteReg(0x36,0xA8);

#else//竖屏
	st7735_lcddev.dir=0;//竖屏				 	 		
	st7735_lcddev.width=128;
	st7735_lcddev.height=128;
	st7735_lcddev.setxcmd=0x2A;
	st7735_lcddev.setycmd=0x2B;	
	ST7735_LCD_WriteReg(0x36,0xC8);
#endif
}	

//******************************************************************
//函数名：  ST7735_LCD_Fill
//作者：    wanglus
//日期：    2020-07-18
//功能：    在指定区域内填充颜色
//输入参数： sx:指定区域开始点x坐标
//        	sy:指定区域开始点y坐标
//        	color:要填充的颜色
//返回值：  无
//修改记录：无
//******************************************************************
void ST7735_LCD_Fill(u16 sx,u16 sy,u16 color)
{  		
		ST7735_LCD_SetCursor(sx,sy);   	//设置光标位置 
		ST7735_LCD_WriteRAM_Prepare();     //开始写入GRAM
		ST7735_LCD_WR_DATA_16Bit(color);//写入数据 	
}

#endif
