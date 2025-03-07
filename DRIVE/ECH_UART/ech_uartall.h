#ifndef	_ECH_UARTALL_H
#define	_ECH_UARTALL_H

#include "appstart.h"

#ifdef UART_FUNC

typedef struct uart_param_t
{
	u16 uart_count;/*计数*/
	u8 uart_buf[256];/*存储区*/
	u8 uart_deal_buf[256];/*处理区*/
	bool uart_state;/*接收状态*/
	
}UART_CONFIG;

#define USART_REC_LEN  			200  		//定义最大接收字节数 200


#define EN_USART1_RX 			1			//使能（1）/禁止（0）串口1接收
#define EN_USART2_RX 			1		
#define EN_USART3_RX 			1	
#define EN_UART4_RX 			1			
#define EN_UART5_RX 			1		

#define RXBUFFERSIZE   1 					//缓存大小

/*extern func*/
extern UART_CONFIG uart_config_t;

extern u8  USART_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         			//接收状态标记	
extern UART_HandleTypeDef UART1_Handler; 	//UART句柄

extern u8  USART2_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         			//接收状态标记	
extern UART_HandleTypeDef UART2_Handler; 	//UART句柄

extern u8  USART3_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         			//接收状态标记	
extern UART_HandleTypeDef UART3_Handler; 	//UART句柄

extern u8  UART4_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 UART4_RX_STA;         			//接收状态标记	
extern UART_HandleTypeDef UART4_Handler; 	//UART句柄

extern u8  UART5_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 UART5_RX_STA;         			//接收状态标记	
extern UART_HandleTypeDef UART5_Handler; 	//UART句柄


void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void uart4_init(u32 bound);
void uart5_init(u32 bound);
void UART_TransimtByte(UART_HandleTypeDef *huart,uint8_t c);
void UART1_apTrace(char* fmt,...);
void UART2_apTrace(char* fmt,...); 
void UART3_apTrace(char* fmt,...); 
void UART4_apTrace(char* fmt,...);
void UART5_apTrace(char* fmt,...); 
/*开关中断*/
void UART_IRQ_FUNC(UART_HandleTypeDef *huart,bool opa);

#endif

#endif
