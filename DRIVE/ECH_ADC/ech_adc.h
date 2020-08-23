#ifndef __ECH_ADC_H
#define __ECH_ADC_H

#include "appstart.h"

#if ADC_FUNC

//*****************************************//
/*struct variable*/

typedef struct adc_config{
	
	bool status;
	u16 original_adc_vlaue;
	float m_voltage;
}ADC_CONFIG;


//*****************************************//


//*****************************************//
/*enum variable*/

typedef enum 
{
	ADC_CHANNEL_CONF_0 = ADC_CHANNEL_0,
	ADC_CHANNEL_CONF_1 = ADC_CHANNEL_1,
	ADC_CHANNEL_CONF_2 = ADC_CHANNEL_2,
	ADC_CHANNEL_CONF_3 = ADC_CHANNEL_3,
	ADC_CHANNEL_CONF_4 = ADC_CHANNEL_4,
	ADC_CHANNEL_CONF_5 = ADC_CHANNEL_5,
	ADC_CHANNEL_CONF_6 = ADC_CHANNEL_6,
	ADC_CHANNEL_CONF_7 = ADC_CHANNEL_7,
	ADC_CHANNEL_CONF_8 = ADC_CHANNEL_8,
	ADC_CHANNEL_CONF_9 = ADC_CHANNEL_9,
	ADC_CHANNEL_CONF_10 = ADC_CHANNEL_10,
	ADC_CHANNEL_CONF_11 = ADC_CHANNEL_11,
	ADC_CHANNEL_CONF_12 = ADC_CHANNEL_12,
	ADC_CHANNEL_CONF_13 = ADC_CHANNEL_13,
	ADC_CHANNEL_CONF_14 = ADC_CHANNEL_14,
	ADC_CHANNEL_CONF_15 = ADC_CHANNEL_15,
	ADC_CHANNEL_CONF_16 = ADC_CHANNEL_16,
	ADC_CHANNEL_CONF_17 = ADC_CHANNEL_17,
}ADC_ChannelConf;

typedef enum 
{
	ADC_CHANNEL_Sampling_1 = 1,
	ADC_CHANNEL_Sampling_3 = 3,
	ADC_CHANNEL_Sampling_5 = 5,
	ADC_CHANNEL_Sampling_10 = 10,
	ADC_CHANNEL_Sampling_15 = 15,
	ADC_CHANNEL_Sampling_20 = 20,
}ADC_Channel_Sampling_Count;

//*****************************************//

//*****************************************//
/*extern variable*/

extern ADC_CONFIG adc_config_t;

//*****************************************//

void MY_ADC_Init(void); 				//ADC通道初始化
u16  Get_Adc(ADC_ChannelConf ch); 		        //获得某个通道值 
u16 Get_Adc_Average(ADC_ChannelConf ch,ADC_Channel_Sampling_Count times);//得到某个通道给定次数采样的平均值

#endif

#endif 
