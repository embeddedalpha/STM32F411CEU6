/*
 * DMA.h
 *
 *  Created on: 11-Sep-2021
 *      Author: Kunal
 */

#ifndef DMA_DMA_H_
#define DMA_DMA_H_

#include "main.h"
#include "SPI/SPI.h"
#include "I2S/I2S.h"
#include "I2C/I2C.h"
#include "USART/USART.h"



typedef struct DMA_Config
{

	DMA_Stream_TypeDef *DMA_Stream;
	uint8_t channel;
	uint8_t priority;
	uint8_t memory_size;
	uint8_t peripheral_size;
	uint8_t direction;
	int data_length;
	uint32_t source_address;
	uint32_t destination_address;

}DMA_Config;


void DMA_Init(DMA_Config DMA);

/******************************************* USART START ****************************************************/
void DMA_UART_TX_Init(USART_TypeDef *USART, char data[], int len);
void DMA_UART_TX_Start(USART_TypeDef *USART);
void DMA_UART_RX_Init(USART_TypeDef *USART, char data[], int len);
void DMA_UART_RX_Start(USART_TypeDef *USART);
/******************************************* USART END ****************************************************/



#endif /* DMA_DMA_H_ */

