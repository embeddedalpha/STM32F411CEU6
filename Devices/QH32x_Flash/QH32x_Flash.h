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
#include "QH32x_Flash_Commands.h"


SPI_Config QH32;

void QH32x_Init(SPI_TypeDef *SPI);

void QH32x_Reset();
void QH32x_Chip_Erase();
void QH32x_Erase_Block();
void QH32x_Erase_Sector(uint32_t address);


void QH32x_Write_Flash(uint32_t addr, uint8_t data);
void QH32x_Write_Flash_Buffer(uint32_t addr, int len, char *data);

uint8_t QH32x_Read_Flash(uint32_t addr);
void QH32x_Read_Flash_Buffer(uint32_t addr, int len, uint8_t *data);


void QH32x_Erase_Data(uint32_t start_address, uint32_t end_address);






#endif /* QH32X_FLASH_QH32X_FLASH_H_ */
