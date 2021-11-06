/*
 * DMA.c
 *
 *  Created on: 11-Sep-2021
 *      Author: Kunal
 */

#include "DMA.h"


void DMA_Init(DMA_Config DMA)
{
	if(DMA.DMA_Stream == DMA1_Stream0 ||
	   DMA.DMA_Stream == DMA1_Stream1 ||
	   DMA.DMA_Stream == DMA1_Stream2 ||
	   DMA.DMA_Stream == DMA1_Stream3 ||
	   DMA.DMA_Stream == DMA1_Stream4 ||
	   DMA.DMA_Stream == DMA1_Stream5 ||
	   DMA.DMA_Stream == DMA1_Stream6 )
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	}
	if(DMA.DMA_Stream == DMA2_Stream0 ||
	   DMA.DMA_Stream == DMA2_Stream1 ||
	   DMA.DMA_Stream == DMA2_Stream2 ||
	   DMA.DMA_Stream == DMA2_Stream3 ||
	   DMA.DMA_Stream == DMA2_Stream4 ||
	   DMA.DMA_Stream == DMA2_Stream5 ||
	   DMA.DMA_Stream == DMA2_Stream6 )
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	}

	DMA.DMA_Stream -> CR |= ( DMA.channel << 25 |
			                  DMA.priority_level << 16 |
							  DMA.memory_size << 13 |
							  DMA.peripheral_size << 11 |
							  DMA.circular_mode << 8 |
							  DMA.direction << 6 |
							  1 << 8 |
							  1 << 10
							  );

	DMA.DMA_Stream -> NDTR = DMA.packet_length;
	DMA.DMA_Stream -> PAR = DMA.source_address;
	DMA.DMA_Stream -> M0AR = DMA.destination_address;

}

void DMA_Interrupt(DMA_Config DMA)
{
	if(DMA.DMA_Stream == DMA1_Stream0)
	{
		NVIC_SetPriority(DMA1_Stream0_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream0_IRQn);
	}
	else if(DMA.DMA_Stream == DMA1_Stream1)
	{
		NVIC_SetPriority(DMA1_Stream1_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	}
	else if(DMA.DMA_Stream == DMA1_Stream2)
	{
		NVIC_SetPriority(DMA1_Stream2_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	}
	else if(DMA.DMA_Stream == DMA1_Stream3)
	{
		NVIC_SetPriority(DMA1_Stream3_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream3_IRQn);
	}
	else if(DMA.DMA_Stream == DMA1_Stream4)
	{
		NVIC_SetPriority(DMA1_Stream4_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream4_IRQn);
	}
	else if(DMA.DMA_Stream == DMA1_Stream5)
	{
		NVIC_SetPriority(DMA1_Stream5_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	}
	else if(DMA.DMA_Stream == DMA1_Stream6)
	{
		NVIC_SetPriority(DMA1_Stream6_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream6_IRQn);
	}
/**************************************************************************************/
	else 	if(DMA.DMA_Stream == DMA2_Stream0)
	{
		NVIC_SetPriority(DMA2_Stream0_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA1_Stream0_IRQn);
	}
	else if(DMA.DMA_Stream == DMA2_Stream1)
	{
		NVIC_SetPriority(DMA2_Stream1_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	}
	else if(DMA.DMA_Stream == DMA2_Stream2)
	{
		NVIC_SetPriority(DMA2_Stream2_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	}
	else if(DMA.DMA_Stream == DMA2_Stream3)
	{
		NVIC_SetPriority(DMA2_Stream3_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	}
	else if(DMA.DMA_Stream == DMA2_Stream4)
	{
		NVIC_SetPriority(DMA2_Stream4_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA2_Stream4_IRQn);
	}
	else if(DMA.DMA_Stream == DMA2_Stream5)
	{
		NVIC_SetPriority(DMA2_Stream5_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA2_Stream5_IRQn);
	}
	else if(DMA.DMA_Stream == DMA2_Stream6)
	{
		NVIC_SetPriority(DMA2_Stream6_IRQn,DMA.interrupt_priority);
		NVIC_EnableIRQ(DMA2_Stream6_IRQn);
	}
/**************************************************************************************/
	DMA.DMA_Stream -> CR |= DMA.transfer_complete_interrupt << 4 |
			        DMA.half_transfer_interrupt << 3 |
				DMA.transfer_error_interrupt << 2 |
				DMA.direct_mode_error_interrupt << 1;
}

void DMA_Enable(DMA_Config DMA)
{
	DMA.DMA_Stream -> CR |= DMA_SxCR_EN;
}



