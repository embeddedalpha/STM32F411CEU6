/*
 * QH32x_Flash.h
 *
 *  Created on: 03-Oct-2021
 *      Author: Kunal
 */

#ifndef QH32X_FLASH_QH32X_FLASH_H_
#define QH32X_FLASH_QH32X_FLASH_H_

#include "main.h"
#include "SPI/SPI.h"


SPI_Config QH32;

bool QH32x_Init(SPI_TypeDef *SPI);

void QH32x_Reset();
void QH32x_Flash_Write_Enable();
void QH32x_Write_Flash(uint32_t addr, uint8_t data);
void QH32x_Write_Flash_Buffer(uint32_t addr, int len, uint8_t *data);

void QH32x_Read_Flash(uint32_t addr);
void QH32x_Read_Flash_Buffer(uint32_t addr, int len, uint8_t *data);



void QH32x_Test();


#endif /* QH32X_FLASH_QH32X_FLASH_H_ */
