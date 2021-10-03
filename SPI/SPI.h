/*
 * SPI.h
 *
 *  Created on: 18-Jul-2021
 *  Updated on: 03-Oct-2021
 *      Author: Kunal
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_

#include "main.h"
#include "GPIO/GPIO.h"

#define Full_Duplex_Master    0
#define Half_Duplex_Master_TX 1
#define Half_Duplex_Master_RX 2
#define Full_Duplex_Slave     3
#define Half_Duplex_Slave_TX  4
#define Half_Duplex_Slave_RX  5

#define SPI_Frame_8Bit 0
#define SPI_Frame_16Bit 1

#define SPI_Master 1
#define SPI_Slave 0




typedef struct SPI_Config
{
	SPI_TypeDef *SPI;
	uint8_t type;
	bool mode;
	int frequency;
	bool phase;
	bool polarity;
	bool LSB_MSB;
	bool CRC_Enable;
	bool DMA_TX;
	bool DMA_RX;
	bool Frame;
}SPI_Config;

void SPI_Init(SPI_Config SPI);
void SPI_CSS_Init(SPI_Config SPI);
void SPI_CSS_High(SPI_Config SPI);
void SPI_CSS_Low(SPI_Config SPI);
void SPI_Send_Data(SPI_Config SPI,int16_t data);
int16_t SPI_Receive_Data(SPI_Config SPI);




#endif /* SPI_SPI_H_ */
