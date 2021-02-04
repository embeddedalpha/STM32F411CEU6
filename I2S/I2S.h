#ifndef		_I2S_H_
#define 	_I2S_H_

#include "stm32f411xe.h"



void I2S1_Master__Init(void);
void I2S2_Master_Init(void);
void I2S3_Master__Init(void);
void I2S4_Master_Init(void);
void I2S5_Master__Init(void);


void I2S_Master_Send_Data(SPI_TypeDef *I2S, uint32_t *r_channel,  uint32_t *l_channel , int length);












#endif

