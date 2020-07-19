#include "led.h"
  
//LED IO初始化
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOC_CLK_ENABLE();           	//开启GPIOC时钟
		__HAL_RCC_GPIOB_CLK_ENABLE();           	//开启GPIOB时钟
	
    GPIO_Initure.Pin=GPIO_PIN_6; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

		GPIO_Initure.Pin=GPIO_PIN_1; 				//PD2
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);	//PA8置1，默认初始化后灯灭
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PD2置1，默认初始化后灯灭
}
