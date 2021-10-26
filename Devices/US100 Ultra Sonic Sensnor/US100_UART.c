/*
 * US100_UART.c
 *
 *  Created on: 27-Oct-2021
 *      Author: Kunal
 */


#include "US100_UART.h"


/*_______________________________________________________________________________________________________________
 * Function: US100_UART_Init
 * ______________________________________________________________________________________________________________
 *
 * Operation: Initializes the UART block with baud rate of 9600.
 * ______________________________________________________________________________________________________________
 *
 * Imports:
 *
 * USART = USART1 / USART2 / USART3
 * ______________________________________________________________________________________________________________
 *
 * Returns: None
 * ______________________________________________________________________________________________________________
 */

void US100_UART_Init(USART_TypeDef *USART)
{
	int baudrate = 9600;
	if(USART == USART1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
		GPIO_Pin_Setup('A', 9, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART1_TX);
		GPIO_Pin_Setup('A', 10, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, USART1_RX);
		USART ->CR1 |= USART_CR1_UE;
		USART->BRR = (int)(SystemCoreClock / (16 * baudrate)) << 4;
		USART ->CR1 |= USART_CR1_TE ;
		USART ->CR1 |=  USART_CR1_RE  ;
	}
	else if(USART == USART2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
		GPIO_Pin_Setup('A', 2, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART2_TX);
		GPIO_Pin_Setup('A', 3, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, USART2_RX);
		USART ->CR1 |= USART_CR1_UE;
		USART->BRR = (int)(SystemCoreClock / ((16 * baudrate)*2)) << 4;
		USART ->CR1 |= USART_CR1_TE ;
		USART ->CR1 |=  USART_CR1_RE  ;
	}
	else if(USART == USART6)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART6EN;
		GPIO_Pin_Setup('A', 11, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART6_TX);
		GPIO_Pin_Setup('A', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART6_RX);
		USART ->CR1 |= USART_CR1_UE;
		USART->BRR = (int)(SystemCoreClock / (16 * baudrate)) << 4;
		USART ->CR1 |= USART_CR1_TE ;
		USART ->CR1 |=  USART_CR1_RE  ;
	}

}


/*_______________________________________________________________________________________________________________
 * Function: US100_UART_Read_Temp
 * ______________________________________________________________________________________________________________
 *
 * Operation: Reads the temperature back from US100.
 * ______________________________________________________________________________________________________________
 *
 * Imports:
 *
 * USART = USART1 / USART2 / USART3
 * ______________________________________________________________________________________________________________
 *
 * Returns: temperature of the US100
 * ______________________________________________________________________________________________________________
 */

uint8_t US100_UART_Read_Temp(USART_TypeDef *USART)
{
	uint8_t x;
	USART -> DR = 0x50;
	while (!(USART ->SR & USART_SR_TXE));
	USART1 ->CR1 |= USART_CR1_RE;
	while (!(USART ->SR & USART_SR_RXNE));
	x = USART -> DR;
	return x;
}


/*_______________________________________________________________________________________________________________
 * Function: US100_UART_Get_Distance_mm
 * ______________________________________________________________________________________________________________
 *
 * Operation: Reads the temperature back from US100.
 * ______________________________________________________________________________________________________________
 *
 * Imports:
 *
 * USART = USART1 / USART2 / USART3
 * ______________________________________________________________________________________________________________
 *
 * Returns: distance in mm from US100
 * ______________________________________________________________________________________________________________
 */

float US100_UART_Get_Distance_mm(USART_TypeDef *USART)
{
	uint8_t x1,x2;
	float y;
	USART -> DR = 0x55;
	while (!(USART ->SR & USART_SR_TXE));
	USART1 ->CR1 |= USART_CR1_RE;
	while (!(USART ->SR & USART_SR_RXNE));
	x1 = USART -> DR;
	USART1 ->CR1 |= USART_CR1_RE;
	while (!(USART ->SR & USART_SR_RXNE));
	x2 = USART -> DR;
	y = x2 * 256 + x1;
	return y;
}


/*_______________________________________________________________________________________________________________
 * Function: US100_UART_Get_Distance_cm
 * ______________________________________________________________________________________________________________
 *
 * Operation: Reads the temperature back from US100.
 * ______________________________________________________________________________________________________________
 *
 * Imports:
 *
 * USART = USART1 / USART2 / USART3
 * ______________________________________________________________________________________________________________
 *
 * Returns: distance in cm from US100
 * ______________________________________________________________________________________________________________
 */

float US100_UART_Get_Distance_cm(USART_TypeDef *USART)
{
	uint8_t x1,x2;
	float y;
	USART -> DR = 0x55;
	while (!(USART ->SR & USART_SR_TXE));
	USART1 ->CR1 |= USART_CR1_RE;
	while (!(USART ->SR & USART_SR_RXNE));
	x1 = USART -> DR;
	USART1 ->CR1 |= USART_CR1_RE;
	while (!(USART ->SR & USART_SR_RXNE));
	x2 = USART -> DR;
	y = x2 * 256 + x1;
	return y;
}
