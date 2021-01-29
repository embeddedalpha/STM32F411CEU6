#ifndef		_I2S_H_
#define 	_I2S_H_



#include "stm32f411xe.h"


#define Philips_Standard	0
#define Left_Justified		1
#define Right_Justified		2
#define PCM_Standard			3

#define Data_Length_16Bit		0
#define Data_Length_24Bit		1
#define Data_Length_32Bit		2

#define Slave_Transmit		0
#define Slave_Receive			1
#define Master_Transmit		2
#define Master_Receive		3


void I2S_Init(SPI_TypeDef *I2S, 
	            uint8_t mode, 
              uint8_t standard, 
              uint8_t data_length, 
              uint8_t channel_length);













#endif


