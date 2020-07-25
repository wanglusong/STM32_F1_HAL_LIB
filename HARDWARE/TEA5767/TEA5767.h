#ifndef __TEA5767__H__INCLUDED__
#define __TEA5767__H__INCLUDED__

#include "sys.h"

typedef struct TEA5767_T
{
	u32 tea5767_freq;
	u8 tea5767_vloume;
	u8 mode;
}TEA5767_func;

extern TEA5767_func TEA5767_func_t;

#if 0

//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;} //PB11
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
//IO管脚定义
#define	IIC_CLK	 (1<<10)  //数据/命令选择端口	PB10
#define	IIC_SDA  (1<<11)  //数据端口		  	PB11 
//IO操作函数	 
#define IIC_SCL_SET(x)   GPIOB->ODR=(GPIOB->ODR&~IIC_CLK)|(x ? IIC_CLK:0)
#define IIC_SDA_SET(x)   GPIOB->ODR=(GPIOB->ODR&~IIC_SDA)|(x ? IIC_SDA:0)	 
#define READ_SDA() ((GPIOB->IDR&(IIC_SDA))?1:0)//输入的时候

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
//TEA5767操作函数

void Key_Scan(void);
void TEA5767_Write(void);
void Get_PLL(void);
void Get_Frequency(void);
void TEA5767_Read(void);
void Search(char mode);
void Auto_Search(char mode);
void Set_Frequency(u32 fre);
void Tea5767_main(void);

#endif

#endif
