/*
 * DMA.c
 *
 *  Created on: 11-Sep-2021
 *      Author: Kunal
 */

#include "DMA.h"


void DMA_Init(DMA_Config DMA)
{
	DMA.DMA_Stream -> CR |= ( DMA.channel << 25 |
			                  DMA.priority << 16 |
							  DMA.memory_size << 13 |
							  DMA.peripheral_size << 11 |
							  1 << 10 | 1 << 8 | DMA.direction << 6 );
	DMA.DMA_Stream -> NDTR = DMA.data_length;
	DMA.DMA_Stream -> PAR = DMA.source_address;
	DMA.DMA_Stream -> M0AR = DMA.destination_address;
	DMA.DMA_Stream -> CR |= DMA_SxCR_EN;
}


void DMA_UART_TX_Init(USART_TypeDef *USART, char data[], int len)
{
	if(USART == USART1)
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		DMA2_Stream7 -> CR |= ( 4 << 25 ) | (1 << 10) | (1 << 8) | (1 << 6) | (1 << 4) | (1 << 3) |
				 (1 << 2) |  (1 << 1);
		DMA2_Stream7 -> NDTR = len;
		DMA2_Stream7 -> M0AR = (uint32_t)&data[0];
		DMA2_Stream7 -> PAR = (uint32_t)&(USART1->DR);
	}else if(USART == USART2)
		{
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA1EN;
		DMA1_Stream6 -> CR |= ( 6 << 25 ) | (1 << 10) | (1 << 8) | (1 << 6) | (1 << 4) | (1 << 3) |
				 (1 << 2) |  (1 << 1);
		DMA1_Stream6 -> NDTR = len;
		DMA1_Stream6 -> M0AR = (uint32_t)&data[0];
		DMA1_Stream6 -> PAR = (uint32_t)&(USART2->DR);
		}else if(USART == USART6)
			{
			RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
			DMA2_Stream7 -> CR |= ( 5 << 25 ) | (1 << 10) | (1 << 8) | (1 << 6) | (1 << 4) | (1 << 3) |
					 (1 << 2) |  (1 << 1);
			DMA2_Stream7 -> NDTR = len;
			DMA2_Stream7 -> M0AR = (uint32_t)&data[0];
			DMA2_Stream7 -> PAR = (uint32_t)&(USART6->DR);
			}
}


void DMA_UART_TX_Start(USART_TypeDef *USART)
{
	if(USART == USART1)
	{
		USART1 -> CR3 |= USART_CR3_DMAT;
		USART1 -> CR1 |= USART_CR1_UE;
		DMA2_Stream7 -> CR |= 1 << 0;
	}else if(USART == USART2)
		{
		USART2 -> CR3 |= USART_CR3_DMAT;
		USART2 -> CR1 |= USART_CR1_UE;
		DMA1_Stream6 -> CR |= 1 << 0;
		}else if(USART == USART6)
			{
			USART6 -> CR3 |= USART_CR3_DMAT;
			USART6 -> CR1 |= USART_CR1_UE;
			DMA2_Stream7 -> CR |= 1 << 0;
			}
}

void DMA_UART_RX_Init(USART_TypeDef *USART, char data[], int len)
{
	if(USART == USART1)
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		DMA2_Stream2 -> CR |= ( 4 << 25 ) | (1 << 10) | (1 << 8) | (0 << 6) | (1 << 4) | (1 << 3) |
				 (1 << 2) |  (1 << 1);
		DMA2_Stream2 -> NDTR = len;
		DMA2_Stream2 -> M0AR = (uint32_t)&data[0];
		DMA2_Stream2 -> PAR = (uint32_t)&(USART1->DR);
	}else if(USART == USART2)
		{
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA1EN;
		DMA1_Stream5 -> CR |= ( 5 << 25 ) | (1 << 10) | (1 << 8) | (0 << 6) | (1 << 4) | (1 << 3) |
				 (1 << 2) |  (1 << 1);
		DMA1_Stream5 -> NDTR = len;
		DMA1_Stream5 -> M0AR = (uint32_t)&data[0];
		DMA1_Stream5 -> PAR = (uint32_t)&(USART2->DR);
		}else if(USART == USART6)
			{
			RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
			DMA2_Stream1 -> CR |= ( 5 << 25 ) | (1 << 10) | (1 << 8) | (0 << 6) | (1 << 4) | (1 << 3) |
					 (1 << 2) |  (1 << 1);
			DMA2_Stream1 -> NDTR = len;
			DMA2_Stream1 -> M0AR = (uint32_t)&data[0];
			DMA2_Stream1 -> PAR = (uint32_t)&(USART6->DR);
			}
}


void DMA_UART_RX_Start(USART_TypeDef *USART)
{
	if(USART == USART1)
	{
		USART1 -> CR3 |= USART_CR3_DMAT;
		USART1 -> CR1 |= USART_CR1_UE;
		DMA2_Stream2 -> CR |= 1 << 0;
	}else if(USART == USART2)
		{
		USART2 -> CR3 |= USART_CR3_DMAT;
		USART2 -> CR1 |= USART_CR1_UE;
		DMA1_Stream6 -> CR |= 1 << 0;
		}else if(USART == USART6)
			{
			USART6 -> CR3 |= USART_CR3_DMAT;
			USART6 -> CR1 |= USART_CR1_UE;
			DMA2_Stream1 -> CR |= 1 << 0;
			}
}



