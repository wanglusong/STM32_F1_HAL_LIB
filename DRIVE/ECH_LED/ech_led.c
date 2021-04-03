#include "ech_led.h"

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"					//FreeRTOS使用		  
#include "task.h" 
#endif

static
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

void led_task(void *pvParameters)
{
	LED_Init();
	
	while (1)
	{
		LED1 = !LED1;
		//UART1_apTrace("[%s %s] FILE: %s FUNC: %s LINE: %d [song]:led running \r\n", __DATE__, \
			//__TIME__, __FILE__,  __func__, __LINE__);
		vTaskDelay(500);
	}
}


