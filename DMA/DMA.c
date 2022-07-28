/*
 * DMA.c
 *
 *  Created on: Jul 28, 2022
 *      Author: Kunal
 */


#include "DMA.h"

int counter = 0;
int counter_limit = 1000;


int DMA_Init(DMA_Config_TypeDef DMA_Instance)
{
	if(DMA_Instance.DMA_Port == DMA1)
	{
		RCC->AHB2ENR |= RCC_AHB1ENR_DMA1EN;
	}
	else if(DMA_Instance.DMA_Port == DMA2)
	{
		RCC->AHB2ENR |= RCC_AHB1ENR_DMA2EN;
	}
	else {
		return -1;
	}

	//Disable DMA wait till it's disabled
	DMA_Instance.DMA_Stream -> CR &= ~DMA_SxCR_EN;
	while(((DMA_Instance.DMA_Stream->CR & DMA_SxCR_EN) ==  DMA_SxCR_EN) && (counter <= counter_limit)){
		counter++;
	}

	//Set DMA Direction
	DMA_Instance.DMA_Stream -> CR |= DMA_Instance.direction;

	//Depending on the direction, set up the memory and peripheral increment mode
	if(DMA_Instance.direction == DMA_Direction_Peripheral_To_Memory)
	{
		DMA_Instance.DMA_Stream -> CR |= DMA_SxCR_MINC;
	}
	else if(DMA_Instance.direction == DMA_Direction_Memory_To_Peripheral)
	{
		DMA_Instance.DMA_Stream -> CR &= ~(DMA_SxCR_MINC | DMA_SxCR_PINC);
	}
	else if(DMA_Instance.direction == DMA_Direction_Memory_To_Memory)
	{
		DMA_Instance.DMA_Stream -> CR |= DMA_SxCR_MINC;
	}
	else
	{
		return -1;
	}

	//Set DMA Priority
	DMA_Instance.DMA_Stream -> CR |= DMA_Instance.priority;


	//Enable Circular Mode
	DMA_Instance.DMA_Stream -> CR |= DMA_Instance.circular_mode;


	//Set Channel
	DMA_Instance.DMA_Stream -> CR |= DMA_Instance.channel_number;


	//Set up memory and peripheral size
	DMA_Instance.DMA_Stream -> CR |= DMA_Instance.memory_size | DMA_Instance.peripheral_size;

	DMA_Instance.DMA_Stream -> FCR |= DMA_SxFCR_DMDIS;

	DMA_Instance.DMA_Stream -> FCR |= DMA_SxFCR_FTH;

	return 0;
}


int DMA_Interrupt_Setup(DMA_Config_TypeDef DMA_Instance)
{
	//Set Interrupt for DMA
	DMA_Instance.DMA_Stream -> CR |= DMA_Instance.direct_mode_error_interrupt |
			                         DMA_Instance.transfer_error_interrupt    |
									 DMA_Instance.half_transfer_interrupt     |
									 DMA_Instance.transfer_complete_interrupt ;

	if(DMA_Instance.DMA_Port == DMA1)
	{
		if(DMA_Instance.DMA_Stream == DMA1_Stream0)
		{
			NVIC_EnableIRQ(DMA1_Stream0_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream1)
		{
			NVIC_EnableIRQ(DMA1_Stream1_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream2)
		{
			NVIC_EnableIRQ(DMA1_Stream2_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream3)
		{
			NVIC_EnableIRQ(DMA1_Stream3_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream4)
		{
			NVIC_EnableIRQ(DMA1_Stream4_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream5)
		{
			NVIC_EnableIRQ(DMA1_Stream5_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream6)
		{
			NVIC_EnableIRQ(DMA1_Stream6_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream7)
		{
			NVIC_EnableIRQ(DMA1_Stream7_IRQn);
		}
		else
		{
			return -1;
		}
	}
	else if(DMA_Instance.DMA_Port == DMA2)
	{
		if(DMA_Instance.DMA_Stream == DMA2_Stream0)
		{
			NVIC_EnableIRQ(DMA2_Stream0_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream1)
		{
			NVIC_EnableIRQ(DMA2_Stream1_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream2)
		{
			NVIC_EnableIRQ(DMA2_Stream2_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream3)
		{
			NVIC_EnableIRQ(DMA2_Stream3_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream4)
		{
			NVIC_EnableIRQ(DMA2_Stream4_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream5)
		{
			NVIC_EnableIRQ(DMA2_Stream5_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream6)
		{
			NVIC_EnableIRQ(DMA2_Stream6_IRQn);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream7)
		{
			NVIC_EnableIRQ(DMA2_Stream7_IRQn);
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

int DMA_Start(DMA_Config_TypeDef DMA_Instance)
{
	if(DMA_Instance.DMA_Port == DMA1)
	{
		if(DMA_Instance.DMA_Stream == DMA1_Stream0)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*0);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream1)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*1);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream2)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*2);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream3)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*3);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream4)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*0);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream5)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*1);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream6)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*2);
		}
		else if(DMA_Instance.DMA_Stream == DMA1_Stream7)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*3);
		}
	}
	else if(DMA_Instance.DMA_Port == DMA2)
	{
		if(DMA_Instance.DMA_Stream == DMA2_Stream0)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*0);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream1)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*1);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream2)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*2);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream3)
		{
			DMA_Instance.DMA_Port ->LIFCR |= 0X1F << (6*3);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream4)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*0);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream5)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*1);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream6)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*2);
		}
		else if(DMA_Instance.DMA_Stream == DMA2_Stream7)
		{
			DMA_Instance.DMA_Port ->HIFCR |= 0X1F << (6*3);
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}

	DMA_Instance.DMA_Stream -> M0AR = (uint32_t)&(DMA_Instance.Source_Address);
	DMA_Instance.DMA_Stream -> PAR = (uint32_t)&(DMA_Instance.Destination_Address);
	DMA_Instance.DMA_Stream -> NDTR = DMA_Instance.length;
	DMA_Instance.DMA_Stream -> CR |= DMA_SxCR_EN;

	return 0;
}


