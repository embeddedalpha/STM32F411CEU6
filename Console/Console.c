/*
 * Console.c
 *
 *  Created on: 25-Oct-2021
 *      Author: Kunal
 */

#include "Console.h"


  void Console_Init(USART_TypeDef *port,int baudrate)
{

	if(port == USART1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
		GPIO_Pin_Setup('A', 9, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART1_TX);
		GPIO_Pin_Setup('A', 10, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, USART1_RX);
		port ->CR1 |= USART_CR1_UE;
		port->BRR = (int)(SystemCoreClock / (16 * baudrate)) << 4;
		port ->CR1 |= USART_CR1_TE ;
		port ->CR1 |=  USART_CR1_RE  ;
	}
	else if(port == USART2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
		GPIO_Pin_Setup('A', 2, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART2_TX);
		GPIO_Pin_Setup('A', 3, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, USART2_RX);
		port ->CR1 |= USART_CR1_UE;
		port->BRR = (int)(SystemCoreClock / ((16 * baudrate)*2)) << 4;
		port ->CR1 |= USART_CR1_TE ;
		port ->CR1 |=  USART_CR1_RE  ;
	}
	else if(port == USART6)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART6EN;
		GPIO_Pin_Setup('A', 11, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART6_TX);
		GPIO_Pin_Setup('A', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART6_RX);
		port ->CR1 |= USART_CR1_UE;
		port->BRR = (int)(SystemCoreClock / (16 * baudrate)) << 4;
		port ->CR1 |= USART_CR1_TE ;
		port ->CR1 |=  USART_CR1_RE  ;
	}




}

  void printConsole(USART_TypeDef *port,char *msg, ...)
{

char buff[10000];
//	#ifdef DEBUG_UART

	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i<= strlen(buff); i++)
	{
		port -> DR = buff[i];
//		port -> CR1 |= USART_CR1_SBK;
		while (!(port->SR & USART_SR_TXE));
	}

//	#endif
}

  int scanConsole(char *msg,...)
{
	int c;
	char buff[10000];

	va_list args;
	va_start(args, msg);
	vscanf(buff,args);
	for(int i = 0; i<= strlen(buff); i++)
	{
		c = UXR();
	}
	va_end(args);
	return c;
}

  char * Console_Return(char *s)
{
	int ch;
	char *p = s;

	while( (ch = USART1 -> DR) != '\n' && ch != EOF)
	{
		*s = (char)ch;
		s++;
	}
	*s = '\0';
	return p;
}

