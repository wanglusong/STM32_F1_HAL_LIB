#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "sys.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#define ENABLE 1
#define DISABLE 0


#define		ESP8266_FUNC		ENABLE/*开关ESP8266功能*/
#define		LVGL_FUNC		DISABLE/*开关LVGL功能*/
#define		UART_FUNC		ENABLE/*开关串口功能*/
#define		TIM_FUNC		ENABLE/*开关定时器功能*/

/*临时项目 extern func*/
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
/*---end---*/

#endif /* __MAIN_H */

