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



void I2S_Mater_Init(SPI_TypeDef *I2S, bool tx_or_rx);

void I2S_Master_Shut_Down(SPI_TypeDef *I2S);

uint32_t I2S_Master_Receive(SPI_TypeDef *I2S);

void I2S_Master_Transmit(SPI_TypeDef *I2S, uint16_t tx);

#endif /* I2S_I2S_H_ */
