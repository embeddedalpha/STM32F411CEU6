/*
 * I2S.h
 *
 *  Created on: 28-Jun-2021
 *      Author: Kunal
 */

#ifndef I2S_I2S_H_
#define I2S_I2S_H_

#include "main.h"
#include "stdbool.h"
#include "GPIO/GPIO.h"

#define I2S1 SPI1
#define I2S2 SPI2
#define I2S3 SPI3
#define I2S4 SPI4
#define I2S5 SPI5

#define I2S_Slave_TX 		0
#define I2S_Slave_RX 	 	1
#define I2S_Master_TX    	2
#define I2S_Master_RX 	 	3

#define  Philips_Standard	 0
#define  MSB_Justified		 1
#define  LSB_Justified		 2
#define  PCM_Standard		 3

#define Frame_16bit	         0
#define Frame_24bit	         1
#define Frame_32bit	         2

#define Channel_16bit        0
#define Channel_32bit        1



typedef struct I2S_Config
{
	SPI_TypeDef *I2S;
	uint8_t mode;
	uint8_t standard;
	uint8_t data_length;
	uint8_t channel_length;
	int32_t audio_frequency;
	bool RX_Interrupt;
	bool TX_Interrupt;

}I2S_Config;



void I2S_Master_Init(I2S_Config I2S);

void I2S_Master_Shut_Down(I2S_Config I2S);

int16_t I2S_Master_Receive_Left_Channel(I2S_Config I2S);

int16_t I2S_Master_Receive_Right_Channel(I2S_Config I2S);

void I2S_Master_Transmit_Left_Channel(I2S_Config I2S, int16_t data);

void I2S_Master_Transmit_Right_Channel(I2S_Config I2S, int16_t data);


#endif /* I2S_I2S_H_ */
