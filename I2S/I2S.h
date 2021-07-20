/*
 * I2S.h
 *
 *  Created on: 28-Jun-2021
 *      Author: Kunal
 */

#ifndef I2S_I2S_H_
#define I2S_I2S_H_

#include "stm32f411xe.h"
#include "stm32f4xx.h"
#include "stdbool.h"

#define channel_length_16_bit 0;
#define channel_length_32_bit 1;

#define data_length_16_bit 0;
#define data_length_24_bit 1;
#define data_length_32_bit 2;

#define Philips_Standard 0;
#define MSB_Justified_Standard 1;
#define LSB_Justified_Standard 2;
#define PCM_Standard 3;

#define Slave_Transmit 0;
#define Slave_Receive 1;
#define Master_Transmit 2;
#define Master_Receive 3;

typedef struct I2S_Config
{
	SPI_TypeDef *I2S;
	uint8_t mode;
	uint8_t standard;
	uint8_t data_length;
	uint8_t channel_length;
	int32_t audio_frequency;

}I2S_Config;


void I2C_Master_Init(I2S_Config I2S);

void I2S_Master_Shut_Down(SPI_TypeDef *I2S);

uint32_t I2S_Master_Receive(SPI_TypeDef *I2S);

void I2S_Master_Transmit(SPI_TypeDef *I2S, uint16_t tx);

#endif /* I2S_I2S_H_ */
