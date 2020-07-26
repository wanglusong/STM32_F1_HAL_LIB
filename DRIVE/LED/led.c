#include "led.h"
 


void LED_Init(void)
{
#if F103_C8T6_TWO_USB_ADD_8PIN_LCD_INTERFACE
	
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	
		__HAL_RCC_GPIOD_CLK_ENABLE();          
	
    GPIO_Initure.Pin=GPIO_PIN_2; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	
    GPIO_Initure.Pull=GPIO_PULLUP;          	
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;  
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

		GPIO_Initure.Pin=GPIO_PIN_8; 				//PD2
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);	
#endif
	
}
