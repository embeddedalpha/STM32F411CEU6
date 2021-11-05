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

#define DMA_Peripheral_To_Memory 0
#define DMA_Memory_To_Peripheral 1
#define DMA_Memory_To_Memory     2

#define Enable 1
#define Disable 0

#define DMA_Priority_Low           0
#define DMA_Priority_Medium        1
#define DMA_Priority_High          2
#define DMA_Priority_Very_High     3

typedef struct DMA_Config
{
	DMA_Stream_TypeDef *DMA_Stream;
	uint8_t channel;
	uint32_t *source_address;
	uint32_t *destination_address;
	uint8_t priority_level;
	uint8_t memory_size;
	uint8_t peripheral_size;
	uint8_t circular_mode;
	uint8_t direction;
	uint8_t packet_length;
	uint8_t interrupt_priority;
	uint8_t transfer_complete_interrupt;
	uint8_t half_transfer_interrupt;
	uint8_t transfer_error_interrupt;
	uint8_t direct_mode_error_interrupt;

}DMA_Config;


void DMA_Init(DMA_Config DMA);
void DMA_Interrupt(DMA_Config DMA);
void DMA_Enable(DMA_Config DMA);

//void DMA2_Stream2_IRQHandler(void)
//{
//	if((DMA2 ->LISR & DMA_LISR_TCIF2) == DMA_LISR_TCIF2)
//	{
//		DMA2 -> LIFCR |= DMA_LIFCR_CTCIF2;
//      //Your code goes here
//
//	}
//}

#endif /* DMA_DMA_H_ */
