/*
 * SPI.h
 *
 *  Created on: 20-Mar-2021
 *      Author: Kunal
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_

#include "stm32f411xe.h"
#include "stm32f4xx.h"
#include "stdbool.h"
#include "GPIO/GPIO.h"


typedef struct SPI_Config
{
	SPI_TypeDef *SPI;
	bool mode;
	bool onlyTXorRX;
	bool frame_format;
	uint8_t clock_speed;
	uint8_t lsb_or_msb;
	bool crc;
	bool interrupts;
	bool tx_int;
	bool err_int;
	bool rx_int;
	bool clock_phase;
	bool clock_polarity;
	bool txDMA;
	bool rxDMA;

}SPI_Config;


void SPI_Master_Init(SPI_Config SPI);

void SPI_Master_TX(SPI_Config SPI, uint16_t data);

uint16_t SPI_Master_RX(SPI_Config SPI);

void SPI_Slave_Init(SPI_Config SPI);

void SPI_Slave_TX(SPI_Config SPI, uint16_t data);

uint16_t SPI_Slave_RX(SPI_Config SPI);

void SPI_Disable(SPI_Config SPI);


void SPI1_CSS_HIGH(void);

void SPI1_CSS_LOW(void);

void SPI2_CSS_HIGH(void);

void SPI2_CSS_LOW(void);


#endif /* SPI_SPI_H_ */

