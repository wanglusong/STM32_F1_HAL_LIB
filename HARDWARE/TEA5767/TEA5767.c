#include "TEA5767.h"
#include "delay.h"
#include "usart.h"

#define max_freq 108000
#define min_freq 87500

unsigned char radio_data[5]={0x29,0xc2,0x20,0x11,0x00};

unsigned char read_data[5];        //TEA5767������״̬
unsigned long frequency;
unsigned int pll;

u8 key_down=0;
/**********************************************************
** ������: IIC_Init
** ��������: I2C��GPIO��ʼ��
** �������: ��
** �������: ��
** ��    �أ���
***********************************************************/
void IIC_Init(void)	
{					     
 	//CLK-PB10,SDA-PB11
	RCC->APB2ENR|=1<<3;//��ʹ������PBʱ��
	RCC->APB2ENR|=1<<6;//��ʹ������PCʱ�� 							 
	GPIOB->CRH&=0XFFFF00FF;//PB10/11 �������
	GPIOB->CRH|=0X00003300;	   
	GPIOB->ODR|=0X0C00;    //PB10��PB11�ø�
	//��������PA0,��������
//	RCC->APB2ENR|=1<<2;//ʹ��PAʱ��							 
//	GPIOA->CRL&=0XFFFFFFF0;
//	GPIOA->CRL|=0X00000008;//PA0��������
//	GPIOA->ODR|=0X0001;//PA0��1	 
	//��������PE2~4,��������
//	GPIOE->CRL&=0XFFF000FF;	//PE2~4���ó�����	  
//	GPIOE->CRL|=0X00088800; 				   
//	GPIOE->ODR|=7<<2;	   	//PE2~4 ����
}

/**********************************************************
** ������: Key_Scan
** ��������: �������
** �������: ��
** �������: key_down--�������ֵ
** ��    �أ���
***********************************************************/
void Key_Scan(void)
{
	
	if(GPIOA->IDR&GPIO_PIN_0) //PA0������
	{
		delay_ms(6);
		if(GPIOA->IDR&GPIO_PIN_0)
		{
			key_down=3;
		}
		while(GPIOA->IDR&GPIO_PIN_0);//�ȴ������ͷ�
	}
	if(!(GPIOE->IDR&GPIO_PIN_3)) //PE3������
	{
		delay_ms(6);
		if(!(GPIOE->IDR&GPIO_PIN_3))
		{
			key_down=1;
		}
		while(!(GPIOE->IDR&GPIO_PIN_3));//�ȴ������ͷ�
	}
		if(!(GPIOE->IDR&GPIO_PIN_4)) //PE4������
	{
		delay_ms(6);
		if(!(GPIOE->IDR&GPIO_PIN_4))
		{
			key_down=2;
		}
		while(!(GPIOE->IDR&GPIO_PIN_4));//�ȴ������ͷ�
	}
}
/**********************************************************
** ������: IIC_Start
** ��������: ����IIC��ʼ�ź� 
** �������: ��
** �������: ��
** ��    �أ���
***********************************************************/
void IIC_Start(void)
{
	SDA_OUT();     //SDA������Ϊ���
	IIC_SDA_SET(1);	//SDA��1  	  
	IIC_SCL_SET(1); //SCL��1  
	delay_us(4);
 	IIC_SDA_SET(0);//SDA��0  START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_SET(0);//SCL��0 ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
/**********************************************************
** ������: IIC_Stop
** ��������: ����IICֹͣ�ź� 
** �������: ��
** �������: ��
** ��    �أ���
***********************************************************/
void IIC_Stop(void)
{
	SDA_OUT();//SDA������Ϊ���
	IIC_SCL_SET(0);
	IIC_SDA_SET(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_SET(1); 
	IIC_SDA_SET(1);//����I2C���߽����ź�							   	
}
/**********************************************************
** ������: IIC_Wait_Ack
** ��������:�ȴ�Ӧ���źŵ���
** �������: ��
** �������: ��
** ��    �أ�0������Ӧ��ʧ��
             1������Ӧ��ɹ�
***********************************************************/
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_SET(1);
	delay_us(1);	   
	IIC_SCL_SET(1);	 
	while(READ_SDA())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 0;  //��ʱ�˳�
		}
	}
	IIC_SCL_SET(0);//ʱ����0 	   
	return 1;  
} 
/**********************************************************
** ������: IIC_Ack
** ��������:����ACKӦ��
** �������: ��
** �������: ��
** ��    �أ���
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
** ������: IIC_NAck
** ��������:������ACKӦ��
** �������: ��
** �������: ��
** ��    �أ���
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
** ������:IIC_Send_Byte
** ��������:IIC����һ���ֽ�   
** �������: txd ���͵��ֽ�����
** �������: ��
** ��    �أ���
***********************************************************/
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_SET(0);//����ʱ�ӿ�ʼ���ݴ���
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
** ������:IIC_Read_Byte
** ��������:��1�ֽ�
** �������:ack��1--����ACK
				 0--����nACK
** �������: ��
** ��    �أ����ض�ȡ��һ�ֽ�����
***********************************************************/
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_SET(0); //CLK=0
        delay_us(1);
		IIC_SCL_SET(1);	 //CLK=1
        receive<<=1;
        if(READ_SDA())//��ȡSDA������
			receive++;    
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
/**********************************************************
** ������:TEA5767_Write
** ��������:��TEA5767д��5���ֽ�����
** �������:��
** �������:��
** ��    ��:��
***********************************************************/
void TEA5767_Write(void)
{
    unsigned char i;
    IIC_Start(); //������ʼ�ź�
    IIC_Send_Byte(0xc0);        //TEA5767д��ַ
    IIC_Wait_Ack();	  //�ȴ�Ӧ��
    for(i=0;i<5;i++)
    {
        IIC_Send_Byte(radio_data[i]);//����д��5���ֽ�����
        IIC_Ack(); //����Ӧ��
    }
    IIC_Stop(); //����ֹͣ�ź�   
}

/**********************************************************
** ������:Get_PLL
** ��������:��Ƶ��ֵ����PLL
** �������:��
** �������:pll--�õ�PLLֵ
** ��    ��:��
***********************************************************/
void Get_PLL(void)
{
    unsigned char hlsi;
    hlsi=radio_data[2]&0x10;  //HLSIλ
    if (hlsi)
        pll=(unsigned int)((float)((frequency+225)*4)/(float)32.768);    //Ƶ�ʵ�λ:k
    else
        pll=(unsigned int)((float)((frequency-225)*4)/(float)32.768);    //Ƶ�ʵ�λ:k
}


/**********************************************************
** ������:Get_Frequency
** ��������:��PLL����Ƶ��
** �������:��
** �������:frequency--�õ�Ƶ��ֵ
** ��    ��:��
***********************************************************/
void Get_Frequency(void)
{
    unsigned char hlsi;
    unsigned int npll=0;
    npll=pll;
    hlsi=radio_data[2]&0x10;
    if(hlsi)
        frequency=(unsigned long)((float)(npll)*(float)8.192-225);    //Ƶ�ʵ�λ:KHz
    else
        frequency=(unsigned long)((float)(npll)*(float)8.192+225);    //Ƶ�ʵ�λ:KHz
}

/**********************************************************
** ������:Get_Frequency
** ��������:��PLL����Ƶ��
** �������:��
** �������:frequency--�õ�Ƶ��ֵ
** ��    ��:��
***********************************************************/
void TEA5767_Read(void)
{
    unsigned char i;
    unsigned char temp_l,temp_h;
    pll=0;
    IIC_Start();
    IIC_Send_Byte(0xc1);        //TEA5767����ַ
    IIC_Wait_Ack();
    for(i=0;i<5;i++)   //��ȡ5���ֽ�����
    {
        read_data[i]=IIC_Read_Byte(1);//��ȡ���ݺ󣬷���Ӧ��
    }
    IIC_Stop();
    temp_l=read_data[1];//�õ�PLL��8λ 
    temp_h=read_data[0];//�õ�PLL��6λ
    temp_h&=0x3f;
    pll=temp_h*256+temp_l; //PLLֵ
    Get_Frequency();//ת��ΪƵ��ֵ
}
/**********************************************************
** ������:Set_Frequency
** ��������:���õ�̨Ƶ��
** �������:fre--д��ĵ�̨Ƶ��ֵ��kHz��
** �������:��
** ��    ��:��
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
** ������:Search
** ��������:�ֶ�������̨�����ÿ���TEA5767������̨�����λ:SM,SUD
** �������:mode=1������������Ƶ��ֵ+0.1MHz
			mode=0������������Ƶ��ֵ-0.1MHz
** �������:��
** ��    ��:��
***********************************************************/
void Search(char mode)
{
    TEA5767_Read(); //��ȡ��ǰƵ��ֵ       
    if(mode) //��������
    {
        frequency+=10;
        if(frequency>max_freq)//Ƶ�ʴﵽ���ֵ
            frequency=min_freq;
    }
    else   //��������
    {
        frequency-=10;
        if(frequency<min_freq)//Ƶ�ʴﵽ��Сֵ
            frequency=max_freq;
    }          
    Get_PLL();//����PLLֵ
    radio_data[0]=pll/256; //����д��5���ֽ�����
    radio_data[1]=pll%256;
    radio_data[2]=0x20;
    radio_data[3]=0x11;
    radio_data[4]=0x00;
    TEA5767_Write();
	TEA5767_Read();//��ȡƵ��ֵ
	//while(GPIOA->IDR&GPIO_Pin_0); //�ȴ�PA0�����ͷ�
}

/**********************************************************
** ������:Auto_Search
** ��������:�Զ�������̨
** �������:mode=1��Ƶ����������
			mode=0��Ƶ�ʼ�С����
** �������:��
** ��    ��:��
***********************************************************/
void Auto_Search(char mode)
{
	TEA5767_Read();//��ȡƵ��
    Get_PLL();	   //ת��ΪPLLֵ
    if(mode)//Ƶ��������̨
        radio_data[2]=0xa0;
    else	//Ƶ�ʼ�С��̨
        radio_data[2]=0x20;  
	  
    radio_data[0]=pll/256+0x40;
    radio_data[1]=pll%256;    
    radio_data[3]=0x11;
    radio_data[4]=0x00;
    TEA5767_Write();  //д��5���ֽ�����
    TEA5767_Read();//��ȡƵ��ֵ
//	  printf(" |%d\n",frequency);	//�������Ƶ��ֵ 
    if((read_data[0]&0x80))     //��̨�ɹ����ɱ�����Ƶ��ֵ����
    {
        TEA5767_Read();
//		printf(" frequency=%d\n",frequency);
		// while(GPIOA->IDR&GPIO_Pin_0); //�ȴ�PA0�����ͷ�
    }    
}



