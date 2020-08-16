#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_hal.h"
#include "sys.h"

/* Func Config ---------------------------------------------------------------*/

#define OPEN  1
#define CLOSE 0

/*开关ESP8266功能*/
#define		ESP8266_FUNC	CLOSE

/*开关LCD功能*/
#define		LCD_FUNC			OPEN

/*开关LVGL功能*/
#define		LVGL_FUNC			OPEN

/*开关串口功能*/
#define		UART_FUNC			OPEN

/*开关定时器功能*/
#define		TIM_FUNC			OPEN

/*开关ADC功能*/
#define		ADC_FUNC			CLOSE

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

/*extern constants*/
typedef struct main_param
{
	u8 rec_num;/*接收到的数字*/
	u8 rec_Chinese[64];/*接收到的汉字*/
	bool runstatus;/*运行状态*/
	u8 anim_count_rec_msg;
	u8 anim_count_sleep_msg;	
	u16 runcounttime;
}MAIN_PARAM;

extern MAIN_PARAM main_param_t;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

/* project macro switch*/

#define item_37472 CLOSE /*open or close*/
#define item_32415 CLOSE /*open or close*/

#endif /* __MAIN_H */

