/*
 * DMA.h
 *
 *  Created on: Jul 28, 2022
 *      Author: Kunal
 */

#ifndef DMA_H_
#define DMA_H_

#include "main.h"

#define DMA_Channel0                                 ~DMA_SxCR_CHSEL
#define DMA_Channel_1                                 DMA_SxCR_CHSEL_0
#define DMA_Channel_2                                 DMA_SxCR_CHSEL_1
#define DMA_Channel_3                                 DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1
#define DMA_Channel_4                                 DMA_SxCR_CHSEL_2
#define DMA_Channel_5                                 DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_0
#define DMA_Channel_6                                 DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1
#define DMA_Channel_7                                 DMA_SxCR_CHSEL

#define DMA_Direction_Peripheral_To_Memory  		 ~DMA_SxCR_DIR
#define DMA_Direction_Memory_To_Peripheral			  DMA_SxCR_DIR_0
#define DMA_Direction_Memory_To_Memory                DMA_SxCR_DIR_1

#define DMA_Priority_Level_Low                       ~DMA_SxCR_PL
#define DMA_Priority_Level_Medium                     DMA_SxCR_PL_0
#define DMA_Priority_Level_High                       DMA_SxCR_PL_1
#define DMA_Priority_Level_Very_High                  DMA_SxCR_PL

#define DMA_Memory_Size_8_Bits                       ~DMA_SxCR_MSIZE
#define DMA_Memory_Size_16_Bits                       DMA_SxCR_MSIZE_0
#define DMA_Memory_Size_32_Bits                       DMA_SxCR_MSIZE_1

#define DMA_Peripheral_Size_8_Bits                    ~DMA_SxCR_MSIZE
#define DMA_Peripheral_Size_16_Bits                    DMA_SxCR_MSIZE_0
#define DMA_Peripheral_Size_32_Bits                    DMA_SxCR_MSIZE_1




typedef struct DMA_Config_TypeDef{
	DMA_TypeDef *DMA_Port;
	DMA_Stream_TypeDef *DMA_Stream;
	uint8_t channel_number;
	uint32_t *Source_Address;
	uint32_t *Destination_Address;
	uint32_t direction;
	uint8_t priority;
	int16_t length;
	bool interrupt_enable;
	uint8_t memory_size;
	uint8_t peripheral_size;
	bool circular_mode;				//ENABLE or DISABLE
	bool transfer_complete_interrupt;
	bool half_transfer_interrupt;
	bool transfer_error_interrupt;
	bool direct_mode_error_interrupt;
}DMA_Config_TypeDef;

int DMA_Init(DMA_Config_TypeDef DMA_Instance);

int DMA_Interrupt_Setup(DMA_Config_TypeDef DMA_Instance);

int DMA_Start(DMA_Config_TypeDef DMA_Instance);

#endif /* DMA_H_ */
