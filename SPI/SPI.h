/*
 * SPI.h
 *
 *  Created on: 18-Jul-2021
 *      Author: Kunal
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_

#include "main.h"
#include "GPIO/GPIO.h"

#define SPI_Full_Duplex_Master    0
#define SPI_Half_Duplex_Master_TX 1
#define SPI_Half_Duplex_Master_RX 2

#define SPI_Full_Duplex_Slave     3
#define SPI_Half_Duplex_Slave_TX  4
#define SPI_Half_Duplex_Slave_RX  5

#define SPI_Frame_8Bit 0
#define SPI_Frame_16Bit 1

#define SPI_Master 1
#define SPI_Slave 0




typedef struct SPI_Config
{
	SPI_TypeDef *SPI;
	uint8_t type;
	uint8_t mode;
	int frequency;
	uint8_t phase;
	uint8_t polarity;
	uint8_t LSB_MSB;
	uint8_t CRC_Enable;
	uint8_t DMA_TX;
	uint8_t DMA_RX;
	uint8_t Frame;
	GPIO_TypeDef *nCSS_Port;
	int nCSS_pin;
}SPI_Config;

void SPI_Init(SPI_Config SPI);
void SPI_CSS_Init(SPI_Config SPI);
void SPI_CSS_High(SPI_Config SPI);
void SPI_CSS_Low(SPI_Config SPI);
void SPI_Send_Data(SPI_Config SPI, int data);
int SPI_Receive_Data(SPI_Config SPI);


#endif /* SPI_SPI_H_ */
