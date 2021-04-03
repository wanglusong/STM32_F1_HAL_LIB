#ifndef _ECH_TIMER_H
#define _ECH_TIMER_H

#include "appstart.h"

#ifdef TIM_FUNC

typedef struct tim_config
{
	bool status;
	u16 tim_count;
	
	bool TIM5_Status;
	u16 TIM5_Tim_Count;	
	
}TIM_CONFIG;

/*extern func*/
extern TIM_CONFIG tim_config_t;/*参数结构体*/

extern TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
extern TIM_HandleTypeDef TIM4_Handler;  
extern TIM_HandleTypeDef TIM5_Handler; 

/*初始化*/
void TIM3_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM5_Init(u16 arr,u16 psc);

/*开关定时器*/
void TIM_ON_OFF_IT(TIM_HandleTypeDef *htim, bool status);
/*获取定时器状态*/
HAL_TIM_StateTypeDef Get_TIM_State(TIM_HandleTypeDef *htim);
#endif

#endif

