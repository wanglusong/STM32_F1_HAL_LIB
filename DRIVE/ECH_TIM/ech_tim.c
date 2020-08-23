#include "ech_tim.h"
#include "lvgl.h"

#if TIM_FUNC
#include "string.h"
#include "ech_uartall.h"

TIM_CONFIG tim_config_t;

TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
TIM_HandleTypeDef TIM4_Handler;      //��ʱ����� 
TIM_HandleTypeDef TIM5_Handler;      //��ʱ����� 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Stop_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE  

		memset(&tim_config_t, 0 ,sizeof(TIM_CONFIG));
}

void TIM4_Init(u16 arr,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                          //ͨ�ö�ʱ��4
    TIM4_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM4_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM4_Handler);
    
    HAL_TIM_Base_Stop_IT(&TIM4_Handler); //ʹ�ܶ�ʱ��4�Ͷ�ʱ��4�����жϣ�TIM_IT_UPDATE   
}

void TIM5_Init(u16 arr,u16 psc)
{  
    TIM5_Handler.Instance=TIM5;                          //ͨ�ö�ʱ��5
    TIM5_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM5_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM5_Handler);
    
    HAL_TIM_Base_Stop_IT(&TIM5_Handler); //ʹ�ܶ�ʱ��5�Ͷ�ʱ��5�����жϣ�TIM_IT_UPDATE   
}

/*���ض�ʱ��*/
void TIM_ON_OFF_IT(TIM_HandleTypeDef *htim, bool status)
{
		if(htim->Instance == TIM3)
		{
			if(status)
				HAL_TIM_Base_Start_IT(&TIM3_Handler);
			else
				HAL_TIM_Base_Stop_IT(&TIM3_Handler);
		}
		else if(htim->Instance == TIM4)
		{
			if(status)
				HAL_TIM_Base_Start_IT(&TIM4_Handler);
			else
				HAL_TIM_Base_Stop_IT(&TIM4_Handler);
		}		
		else if(htim->Instance == TIM5)
		{
			if(status)
				HAL_TIM_Base_Start_IT(&TIM5_Handler);
			else
				HAL_TIM_Base_Stop_IT(&TIM5_Handler);
		}				
}
/*���ض�ʱ��״̬*/
HAL_TIM_StateTypeDef Get_TIM_State(TIM_HandleTypeDef *htim)
{
	return HAL_TIM_Base_GetState(htim);
}

//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
	   else if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //ʹ��TIM4ʱ��
		HAL_NVIC_SetPriority(TIM4_IRQn,1,4);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�4
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //����ITM3�ж�   
	}
	   else if(htim->Instance==TIM5)
	{
		__HAL_RCC_TIM5_CLK_ENABLE();            //ʹ��TIM5ʱ��
		HAL_NVIC_SetPriority(TIM5_IRQn,1,5);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�5
		HAL_NVIC_EnableIRQ(TIM5_IRQn);          //����ITM3�ж�   
	}	
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

//��ʱ��4�жϷ�����
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM4_Handler);
}

//��ʱ��5�жϷ�����
void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM5_Handler);
}

//�ص���������ʱ���жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM3_Handler))
    {
       lv_tick_inc(1);//lvgl��1ms����
    }else if(htim==(&TIM4_Handler))
    {
       if(tim_config_t.status == true)
			 {
					tim_config_t.tim_count ++;
					if(tim_config_t.tim_count > 2)
					{
						tim_config_t.tim_count = 0;
						tim_config_t.status = false;
						TIM_ON_OFF_IT(&TIM4_Handler, false);
						uart_config_t.uart_state = true;/*�������*/
					}
			 }
    }else if(htim==(&TIM5_Handler))
    {
			if(tim_config_t.TIM5_Status == true)
			{
				tim_config_t.tim_count++;
				if(tim_config_t.tim_count >= 10)/*10s*/
				{
					tim_config_t.TIM5_Status = false;
					TIM_ON_OFF_IT(&TIM5_Handler, false);
					main_param_t.runstatus = false;/*����״̬*/
				}
			}
    }
}

#endif
