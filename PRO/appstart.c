#include "ech_delay.h"
#include "ech_led.h"
#include "ech_key.h"
#include "string.h"
#include "lv_gui_main.h"
#include "lv_ech_base_souce.h"
#include "appstart.h"/*设备配置头*/

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"					//FreeRTOS使用		  
#include "task.h" 
#endif

/*	constants */
MAIN_PARAM main_param_t;

#if TIM_FUNC
#include "ech_tim.h"
#endif

#if LVGL_FUNC
#include "lvgl.h"
#endif

#if LCD_FUNC
#include "ech_lcd_config.h"
#endif

#if UART_FUNC
#include "ech_uartall.h"
#endif

#if ADC_FUNC
#include "ech_adc.h"
#endif

#if ESP8266_FUNC
#include "ech_esp8266_uart.h"
#endif

#ifndef LV_DISPALY
#include "lv_port_disp.h"
#endif

static TaskHandle_t StartTask_Handler; /*TASK handle*/
static TaskHandle_t LVGLTask_Handler; 
static TaskHandle_t LEDTask_Handler; 
static TaskHandle_t Lv_Ech_Start_Task_Handler; 

static void start_task(void *pvParameters); /*START TASK*/
static void lvgl_task(void *pvParameters);	/*LVGL TASK*/

//******************************************************************
//函数名：  app_config
//作者：    wangls
//日期：    2020-08-23
//功能：    系统驱动配置
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
static
void app_config(void)
{
	/*init param*/
	memset(&main_param_t, 0, sizeof(MAIN_PARAM));
		
#if ADC_FUNC
	MY_ADC_Init();
#endif
	
#if TIM_FUNC	
	TIM4_Init(999,719);/*10ms*/
	TIM5_Init(9999,7199);/*1s*/
#endif
		
#if UART_FUNC	
	uart1_init(9600);				//UART
	uart2_init(9600);
	uart3_init(9600);
#endif

	KEY_Init(); 						//KEY
		
#if LVGL_FUNC

	/*lvgl的1ms心跳time*/
	#if TIM_FUNC	
	TIM3_Init(999,71);	
	TIM_ON_OFF_IT(&TIM3_Handler, true);
	/*little vGL init*/
	lv_init();
	/*LCD映射LVGL*/
	lv_port_disp_init();
	#else
	return ;
	#endif	
	
#endif
	
#if ESP8266_FUNC
	UART_IRQ_FUNC(&UART1_Handler,false);
	esp8266_init();
	UART_IRQ_FUNC(&UART1_Handler,true);
#endif

}

//******************************************************************
//函数名：  main
//作者：    wangls
//日期：    2020-08-23
//功能：    系统入口
//输入参数：无
//返回值：  错误信息
//修改记录：无
//******************************************************************
int main(void)
{
	HAL_Init(); 						   
	Stm32_Clock_Init(RCC_PLL_MUL9);//72M
	delay_init();		  //DELAY
	/*app init*/
	app_config();
	
	//创建开始任务
	xTaskCreate((TaskFunction_t )start_task, //任务函数
	(const char* )"start_task", //任务名称
	(uint16_t )START_STK_SIZE, //任务堆栈大小
	(void* )NULL, //传递给任务函数的参数
	(UBaseType_t )START_TASK_PRIO, //任务优先级
	(TaskHandle_t* )&StartTask_Handler); //任务句柄
	vTaskStartScheduler(); //开启任务调度

}

//******************************************************************
//函数名：  start_task
//作者：    wangls
//日期：    2020-08-23
//功能： 创建任务
//输入参数：任务参数
//返回值：  无
//修改记录：无
//******************************************************************
static
void start_task(void *pvParameters)
{ 

	taskENTER_CRITICAL(); //进入临界区
	//创建 lvgl 任务
	xTaskCreate((TaskFunction_t )lvgl_task,
	(const char* )"lvgl_task",
	(uint16_t )LV_ECH_LVGL_STK_SIZE,
	(void* )NULL,
	(UBaseType_t )LV_ECH_LVGL_TASK_PRIO, 
	(TaskHandle_t* )&LVGLTask_Handler);

	vTaskDelete(StartTask_Handler); //删除开始任务
	taskEXIT_CRITICAL(); //退出临界区

}

//******************************************************************
//函数名：  lvgl_task
//作者：    wangls
//日期：    2020-08-23
//功能： lv运行节拍
//输入参数：任务参数
//返回值：  无
//修改记录：无
//******************************************************************
static
void lvgl_task(void *pvParameters)
{
	//创建 LED 任务
	xTaskCreate((TaskFunction_t )led_task,
	(const char* )"led_task",
	(uint16_t )LV_ECH_LED_STK_SIZE,
	(void* )NULL,
	(UBaseType_t )LV_ECH_LED_TASK_PRIO,
	(TaskHandle_t* )&LEDTask_Handler);
	
	//创建 Ech 任务
	xTaskCreate((TaskFunction_t )lv_ech_start_task,
	(const char* )"lv_ech_start_task",
	(uint16_t )LV_ECH_START_STK_SIZE,
	(void* )NULL,
	(UBaseType_t )LV_ECH_START_TASK_PRIO,
	(TaskHandle_t* )&Lv_Ech_Start_Task_Handler);	
	
	while(1)
	{

#if LVGL_FUNC
		lv_task_handler();
#endif
		vTaskDelay(5);

	}
}

