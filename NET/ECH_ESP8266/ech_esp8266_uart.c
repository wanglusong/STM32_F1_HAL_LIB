#include "ech_esp8266_uart.h"
#include "ech_uartall.h"	
#include "ech_delay.h"	

#ifdef ESP8266_FUNC

static
void uart_to_onebyte(u8 byte)
{
	HAL_UART_Transmit(&UART1_Handler,&byte,1,1000);
}

static
void esp8266_to_at_cmd(char *puf)
{
   while(*puf)    
	{
		uart_to_onebyte(*puf); 
		puf++;		
	}
	uart_to_onebyte('\r');
	uart_to_onebyte('\n');
}

void esp8266_init(void)
{	
	  esp8266_to_at_cmd("AT+RST");
	 	delay_ms(2000);		
	  esp8266_to_at_cmd("AT+CWMODE=2");
	 	delay_ms(1000);	
	  esp8266_to_at_cmd("AT+CIPAP=\"192.168.10.5\"");
	 	delay_ms(2000);	
	  esp8266_to_at_cmd("AT+CWSAP=\"small-fly-mouse\",\"xfs12345678\",11,3");
	 	delay_ms(1000);
		esp8266_to_at_cmd("AT+CIPMUX=1");
	 	delay_ms(1000);
		esp8266_to_at_cmd("AT+CIPSERVER=1,5865");
		delay_ms(1000);
}

#endif

