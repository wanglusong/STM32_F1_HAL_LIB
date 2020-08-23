#include "lv_ech_base_souce.h"
#include "lv_gui_main.h"

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"					//FreeRTOS使用		  
#include "task.h" 
#endif

//******************************************************************
//函数名：  lv_ech_start_task
//作者：    wangls
//日期：    2020-08-23
//功能： 系统正式运行任务
//输入参数：任务参数
//返回值：  无
//修改记录：无
//******************************************************************
void lv_ech_start_task(void *pvParameters)
{ 
	/*userinit*/
	lv_start();
	
	while(1)
	{
		UART1_apTrace("[%s %s] FILE: %s FUNC: %s LINE: %d [song]:system running \r\n", __DATE__, \
			__TIME__, __FILE__,  __func__, __LINE__);
		vTaskDelay(500);
	}

}

