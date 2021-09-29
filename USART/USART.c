/*
 * USART.c
 *
 *  Created on: 30-Aug-2021
 *      Author: Kunal
 */

#include "USART.h"

//********************************	Asynchronous Communication	********************************

void UART_Init(Serial UART)
{
	if(UART.port == USART1)
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
		GPIOA -> MODER   |= (2 << 18) | (2 << 20);	//9 -> tx	10 -> rx
		GPIOA -> OTYPER  |= (0 << 9)  | (0 << 10) ;
		GPIOA -> OSPEEDR |= (3 << 9)  | (3 << 10);
		GPIOA -> PUPDR   |= (0 << 18) | (0 << 20);
		GPIOA -> AFR[1]  |= (7 << 4)  | (5 << 8);
		if(UART.hardware_control == 1)
		{
			GPIOA -> MODER   |= (2 << 22)  | (2 << 24);	//11 -> CTS 12->RTS
			GPIOA -> OTYPER  |= (0 << 12)  | (0 << 11) ;
			GPIOA -> OSPEEDR |= (3 << 12)  | (3 << 11);
			GPIOA -> PUPDR   |= (0 << 22)  | (0 << 24);
			GPIOA -> AFR[1]  |= (7 << 12)  | (5 << 16);
		}

	}
	if(UART.port == USART2)
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
		GPIOA -> MODER   |= (2 << 4)  | (2 << 6);	//2 -> tx	3 -> rx
		GPIOA -> OTYPER  |= (0 << 2)  | (0 << 3) ;
		GPIOA -> OSPEEDR |= (3 << 4)  | (3 << 6);
		GPIOA -> PUPDR   |= (0 << 4)  | (0 << 6);
		GPIOA -> AFR[0]  |= (7 << 8)  | (5 << 12);
		if(UART.hardware_control == 1)
		{
			GPIOA -> MODER   |= (2 << 0)  | (2 << 2);	//0 -> CTS 1->RTS
			GPIOA -> OTYPER  |= (0 << 0)  | (0 << 1) ;
			GPIOA -> OSPEEDR |= (3 << 0)  | (3 << 2);
			GPIOA -> PUPDR   |= (0 << 0)  | (0 << 2);
			GPIOA -> AFR[1]  |= (7 << 0)  | (5 << 4);
		}
	}

	UART.port ->CR1 |= USART_CR1_UE;
	UART.port ->BRR = (int)(SystemCoreClock / (16 * UART.baudrate)) << 4;

	if (UART.TX_DMA == 1) UART.port -> CR3 |= USART_CR3_DMAT;
	else                  UART.port -> CR3 &= ~USART_CR3_DMAT;
	if (UART.RX_DMA == 1) UART.port -> CR3 |= USART_CR3_DMAR;
	else                  UART.port -> CR3 &= ~USART_CR3_DMAR;

	if(UART.mode == Half_Duplex) UART.port -> CR3 |= USART_CR3_HDSEL;
	if(UART.mode == Full_Duplex) UART.port -> CR3 &= ~USART_CR3_HDSEL;

	if(UART.hardware_control == 1)
	{
		UART.port -> CR3 |= USART_CR3_CTSE | USART_CR3_RTSE;
	}
	else
	{
		UART.port -> CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE);
	}

	UART.port ->CR1 |= USART_CR1_TE | USART_CR1_RE  ;
}


void UART_Transmit_Byte(Serial UART, char data)
{
	USART1 ->DR = data;
	USART1 -> CR1 |= USART_CR1_SBK;
	while((USART1->SR & USART_SR_TC) == 0);
}


void UART_Transmit_Buffer(Serial UART, char *data)
{
	int x = strlen(data);
	for(int n = 0; n < x; n++)
	{
		USART1 ->DR = (data[n]);
		USART1 -> CR1 |= USART_CR1_SBK;
		while((USART1->SR & USART_SR_TC) == 0);
	}
}


char UART_Receive_Byte(Serial UART)
{
	while((UART.port ->SR & USART_SR_RXNE) == 0);
	return UART.port-> DR;
}


char USART_Transceive(Serial UART, char byte)
{
	USART1 ->DR = (byte);
	USART1 -> CR1 |= USART_CR1_SBK;
	while((USART1->SR & USART_SR_TC) == 0);
	while((UART.port ->SR & USART_SR_RXNE) == 0);
	return UART.port-> DR;
}


//********************************	Synchronous Communication	********************************

void USART_Init(Serial UART);

void UASRT_Transmit_Byte(Serial UART, char data);

void USART_Transmit_Buffer(Serial UART, char *data);

char USART_Receive_Byte(Serial UART);

char USART_Transceive(Serial UART, char byte);
