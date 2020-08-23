#include "TEA5767.h"
#include "ech_delay.h"
#include "ech_uartall.h"
#include "string.h"
#include "ech_key.h"

#if 0

#define max_freq 108000
#define min_freq 87500

TEA5767_func TEA5767_func_t;

unsigned char radio_data[5]={0x29,0xc2,0x20,0x11,0x00};

unsigned char read_data[5];        //TEA5767读出的状态
unsigned long frequency;
unsigned int pll;

u8 key_down=0;
/**********************************************************
** 函数名: IIC_Init
** 功能描述: I2C的GPIO初始化
** 输入参数: 无
** 输出参数: 无
** 返    回：无
***********************************************************/
void IIC_Init(void)	
{					     
 	//CLK-PB10,SDA-PB11
	RCC->APB2ENR|=1<<3;//先使能外设PB时钟
	RCC->APB2ENR|=1<<6;//先使能外设PC时钟 							 
	GPIOB->CRH&=0XFFFF00FF;//PB10/11 推挽输出
	GPIOB->CRH|=0X00003300;	   
	GPIOB->ODR|=0X0C00;    //PB10、PB11置高

	memset(&TEA5767_func_t,0,sizeof(TEA5767_func));
	
	TEA5767_func_t.tea5767_freq = 92000;//100142 滨海电台	
	
	Set_Frequency(TEA5767_func_t.tea5767_freq); //设置电台频率为101.8MHz
}

/**********************************************************
** 函数名: Key_Scan
** 功能描述: 按键检测
** 输入参数: 无
** 输出参数: key_down--输出按键值
** 返    回：无
***********************************************************/
void Key_Scan(void)
{
	
	if(GPIOA->IDR&GPIO_PIN_0) //PA0键按下
	{
		delay_ms(6);
		if(GPIOA->IDR&GPIO_PIN_0)
		{
			key_down=3;
		}
		while(GPIOA->IDR&GPIO_PIN_0);//等待按键释放
	}
	if(!(GPIOE->IDR&GPIO_PIN_3)) //PE3键按下
	{
		delay_ms(6);
		if(!(GPIOE->IDR&GPIO_PIN_3))
		{
			key_down=1;
		}
		while(!(GPIOE->IDR&GPIO_PIN_3));//等待按键释放
	}
		if(!(GPIOE->IDR&GPIO_PIN_4)) //PE4键按下
	{
		delay_ms(6);
		if(!(GPIOE->IDR&GPIO_PIN_4))
		{
			key_down=2;
		}
		while(!(GPIOE->IDR&GPIO_PIN_4));//等待按键释放
	}
}
/**********************************************************
** 函数名: IIC_Start
** 功能描述: 产生IIC起始信号 
** 输入参数: 无
** 输出参数: 无
** 返    回：无
***********************************************************/
void IIC_Start(void)
{
	SDA_OUT();     //SDA线配置为输出
	IIC_SDA_SET(1);	//SDA置1  	  
	IIC_SCL_SET(1); //SCL置1  
	delay_us(4);
 	IIC_SDA_SET(0);//SDA置0  START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_SET(0);//SCL置0 钳住I2C总线，准备发送或接收数据 
}	  
/**********************************************************
** 函数名: IIC_Stop
** 功能描述: 产生IIC停止信号 
** 输入参数: 无
** 输出参数: 无
** 返    回：无
***********************************************************/
void IIC_Stop(void)
{
	SDA_OUT();//SDA线配置为输出
	IIC_SCL_SET(0);
	IIC_SDA_SET(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_SET(1); 
	IIC_SDA_SET(1);//发送I2C总线结束信号							   	
}
/**********************************************************
** 函数名: IIC_Wait_Ack
** 功能描述:等待应答信号到来
** 输入参数: 无
** 输出参数: 无
** 返    回：0，接收应答失败
             1，接收应答成功
***********************************************************/
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA_SET(1);
	delay_us(1);	   
	IIC_SCL_SET(1);	 
	while(READ_SDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 0;  //超时退出
		}
	}
	IIC_SCL_SET(0);//时钟置0 	   
	return 1;  
} 
/**********************************************************
** 函数名: IIC_Ack
** 功能描述:产生ACK应答
** 输入参数: 无
** 输出参数: 无
** 返    回：无
***********************************************************/
void IIC_Ack(void)
{
	IIC_SCL_SET(0);
	SDA_OUT();
	IIC_SDA_SET(0);
	delay_us(1);
	IIC_SCL_SET(1);
	delay_us(1);
	IIC_SCL_SET(0);
}

/**********************************************************
** 函数名: IIC_NAck
** 功能描述:不产生ACK应答
** 输入参数: 无
** 输出参数: 无
** 返    回：无
***********************************************************/
void IIC_NAck(void)
{
	IIC_SCL_SET(0);
	SDA_OUT();
	IIC_SDA_SET(1);
	delay_us(1);
	IIC_SCL_SET(1);
	delay_us(1);
	IIC_SCL_SET(0);
}
/**********************************************************
** 函数名:IIC_Send_Byte
** 功能描述:IIC发送一个字节   
** 输入参数: txd 发送的字节数据
** 输出参数: 无
** 返    回：无
***********************************************************/
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_SET(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA_SET((txd&0x80)>>7);
        txd<<=1; 	  
		delay_us(1);   
		IIC_SCL_SET(1);
		delay_us(1); 
		IIC_SCL_SET(0);	
		delay_us(1);
    }	 
} 	    
/**********************************************************
** 函数名:IIC_Read_Byte
** 功能描述:读1字节
** 输入参数:ack，1--发送ACK
				 0--发送nACK
** 输出参数: 无
** 返    回：返回读取的一字节数据
***********************************************************/
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_SET(0); //CLK=0
        delay_us(1);
		IIC_SCL_SET(1);	 //CLK=1
        receive<<=1;
        if(READ_SDA())//读取SDA线数据
			receive++;    
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}
/**********************************************************
** 函数名:TEA5767_Write
** 功能描述:向TEA5767写入5个字节数据
** 输入参数:无
** 输出参数:无
** 返    回:无
***********************************************************/
void TEA5767_Write(void)
{
    unsigned char i;
    IIC_Start(); //发送起始信号
    IIC_Send_Byte(0xc0);        //TEA5767写地址
    IIC_Wait_Ack();	  //等待应答
    for(i=0;i<5;i++)
    {
        IIC_Send_Byte(radio_data[i]);//连续写入5个字节数据
        IIC_Ack(); //发送应答
    }
    IIC_Stop(); //发送停止信号   
}

/**********************************************************
** 函数名:Get_PLL
** 功能描述:由频率值计算PLL
** 输入参数:无
** 输出参数:pll--得到PLL值
** 返    回:无
***********************************************************/
void Get_PLL(void)
{
    unsigned char hlsi;
    hlsi=radio_data[2]&0x10;  //HLSI位
    if (hlsi)
        pll=(unsigned int)((float)((frequency+225)*4)/(float)32.768);    //频率单位:k
    else
        pll=(unsigned int)((float)((frequency-225)*4)/(float)32.768);    //频率单位:k
}


/**********************************************************
** 函数名:Get_Frequency
** 功能描述:由PLL计算频率
** 输入参数:无
** 输出参数:frequency--得到频率值
** 返    回:无
***********************************************************/
void Get_Frequency(void)
{
    unsigned char hlsi;
    unsigned int npll=0;
    npll=pll;
    hlsi=radio_data[2]&0x10;
    if(hlsi)
        frequency=(unsigned long)((float)(npll)*(float)8.192-225);    //频率单位:KHz
    else
        frequency=(unsigned long)((float)(npll)*(float)8.192+225);    //频率单位:KHz
}

/**********************************************************
** 函数名:Get_Frequency
** 功能描述:由PLL计算频率
** 输入参数:无
** 输出参数:frequency--得到频率值
** 返    回:无
***********************************************************/
void TEA5767_Read(void)
{
    unsigned char i;
    unsigned char temp_l,temp_h;
    pll=0;
    IIC_Start();
    IIC_Send_Byte(0xc1);        //TEA5767读地址
    IIC_Wait_Ack();
    for(i=0;i<5;i++)   //读取5个字节数据
    {
        read_data[i]=IIC_Read_Byte(1);//读取数据后，发送应答
    }
    IIC_Stop();
    temp_l=read_data[1];//得到PLL低8位 
    temp_h=read_data[0];//得到PLL高6位
    temp_h&=0x3f;
    pll=temp_h*256+temp_l; //PLL值
    Get_Frequency();//转换为频率值
}
/**********************************************************
** 函数名:Set_Frequency
** 功能描述:设置电台频率
** 输入参数:fre--写入的电台频率值（kHz）
** 输出参数:无
** 返    回:无
***********************************************************/
void Set_Frequency(u32 fre)
{
	frequency=fre;
	Get_PLL();
    radio_data[0]=pll/256;
    radio_data[1]=pll%256;
    radio_data[2]=0x20;
    radio_data[3]=0x11;
    radio_data[4]=0x00;
    TEA5767_Write();
}
/**********************************************************
** 函数名:Search
** 功能描述:手动搜索电台，不用考虑TEA5767用于搜台的相关位:SM,SUD
** 输入参数:mode=1，向上搜索，频率值+0.1MHz
			mode=0，向下搜索，频率值-0.1MHz
** 输出参数:无
** 返    回:无
***********************************************************/
void Search(char mode)
{
    TEA5767_Read(); //读取当前频率值       
    if(mode) //向上搜索
    {
        frequency+=10;
        if(frequency>max_freq)//频率达到最大值
            frequency=min_freq;
    }
    else   //向下搜索
    {
        frequency-=10;
        if(frequency<min_freq)//频率达到最小值
            frequency=max_freq;
    }          
    Get_PLL();//计算PLL值
    radio_data[0]=pll/256; //重新写入5个字节数据
    radio_data[1]=pll%256;
    radio_data[2]=0x20;
    radio_data[3]=0x11;
    radio_data[4]=0x00;
    TEA5767_Write();
	TEA5767_Read();//读取频率值
	//while(GPIOA->IDR&GPIO_Pin_0); //等待PA0按键释放
}

/**********************************************************
** 函数名:Auto_Search
** 功能描述:自动搜索电台
** 输入参数:mode=1，频率增加搜索
			mode=0，频率减小搜索
** 输出参数:无
** 返    回:无
***********************************************************/
void Auto_Search(char mode)
{
	TEA5767_Read();//读取频率
    Get_PLL();	   //转换为PLL值
    if(mode)//频率增加搜台
        radio_data[2]=0xa0;
    else	//频率减小搜台
        radio_data[2]=0x20;  
	  
    radio_data[0]=pll/256+0x40;
    radio_data[1]=pll%256;    
    radio_data[3]=0x11;
    radio_data[4]=0x00;
    TEA5767_Write();  //写入5个字节数据
    TEA5767_Read();//读取频率值
//	  printf(" |%d\n",frequency);	//串口输出频率值 
    if((read_data[0]&0x80))     //搜台成功，可保存其频率值待用
    {
        TEA5767_Read();
//		printf(" frequency=%d\n",frequency);
		// while(GPIOA->IDR&GPIO_Pin_0); //等待PA0按键释放
    }    
}

void Tea5767_main(void)
{
		 u8 key;
	
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
					
//					LCD_ShowxNum(50+5*16,90,TEA5767_func_t.tea5767_freq/1000,3,16,0);	
//					Show_Str(50+5*16+16+8,90,200,16,".",16,0);
//					LCD_ShowxNum(50+5*16+16+8+8,90,TEA5767_func_t.tea5767_freq%1000,3,16,0);
					
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
					
//					LCD_ShowxNum(50+5*16,90,TEA5767_func_t.tea5767_freq/1000,3,16,0);	
//					Show_Str(50+5*16+16+8,90,200,16,".",16,0);
//					LCD_ShowxNum(50+5*16+16+8+8,90,TEA5767_func_t.tea5767_freq%1000,3,16,0);							
					key = 0;
					break;
				}
				case 1:
				{
					TEA5767_func_t.mode = ! TEA5767_func_t.mode;
					
					if(TEA5767_func_t.mode == 0)
					{
//						Show_Str(50+5*16,210,200,16,"手动",16,0);	
					}else
					{
//						Show_Str(50+5*16,210,200,16,"自动",16,0);	
					}
					key = 0;
					break;
				}
			}
		}
}

#endif
