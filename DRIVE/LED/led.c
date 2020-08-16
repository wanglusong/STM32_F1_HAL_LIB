#include "led.h"
 


void LED_Init(void)
{
	
#if F103_C8T6_TWO_USB_ADD_8PIN_LCD_INTERFACE
	
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	
		__HAL_RCC_GPIOD_CLK_ENABLE();          
	
    GPIO_Initure.Pin=GPIO_PIN_2; 				//PD2
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	
    GPIO_Initure.Pull=GPIO_PULLUP;          	
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;  
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);

		GPIO_Initure.Pin=GPIO_PIN_8; 				//PA8
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);	
#elif F103_ZET6_NETWORK_BOARD
	
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	
		__HAL_RCC_GPIOC_CLK_ENABLE();          
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; 				//PB0,1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	
    GPIO_Initure.Pull=GPIO_PULLUP;          	
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;  
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

		GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6; 				//PC5,6
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_SET);	
	
#endif
	
}
