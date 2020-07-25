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

//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;} //PB11
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
//IO�ܽŶ���
#define	IIC_CLK	 (1<<10)  //����/����ѡ��˿�	PB10
#define	IIC_SDA  (1<<11)  //���ݶ˿�		  	PB11 
//IO��������	 
#define IIC_SCL_SET(x)   GPIOB->ODR=(GPIOB->ODR&~IIC_CLK)|(x ? IIC_CLK:0)
#define IIC_SDA_SET(x)   GPIOB->ODR=(GPIOB->ODR&~IIC_SDA)|(x ? IIC_SDA:0)	 
#define READ_SDA() ((GPIOB->IDR&(IIC_SDA))?1:0)//�����ʱ��

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
//TEA5767��������

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
