/*
 * USART.c
 *
 *  Created on: 05-Apr-2021
 *      Author: Kunal
 */



#include "USART.h"


void USART_Init(USART_Config USART)
{
	if(USART.USART == USART1)
	{
		USART1_Pin_Setup();
	}
	if(USART.USART == USART2)
	{
		USART2_Pin_Setup();
	}

}

void USART_TX(USART_Config USART, uint8_t data)
{

}

uint8_t USART_RX(USART_Config USART)
{

}

void USART_TX_HFC(USART_Config USART, uint8_t data)
{

}

uint8_t USART_RX_HFC(USART_Config USART)
{

}


