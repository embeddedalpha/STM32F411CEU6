#include "main.h"
#include "Console/Console.h"
#include "US100_UART/US100_UART.h"

int main()
{

	MCU_Clock_Setup();
	Delay_Config();
	Console_Init(USART2, 9600);
	US100_UART_Init(USART1);

int b;

	while(1)
	{
		b = US100_UART_Get_Distance_cm(USART1) ;
		printConsole(USART2, "%d\r\n",b);

	}
}


