/*
 * W25Qx_Flash.h
 *
 *  Created on: 03-Oct-2021
 *      Author: Kunal
 */

#ifndef W25QX_FLASH_W25QX_FLASH_H_
#define W25QX_FLASH_W25QX_FLASH_H_

#include <W25Qx_Flash/W25Qx_Flash_Commands.h>
#include "main.h"
#include "SPI/SPI.h"


SPI_Config W25Q;

void     W25Qx_Init(SPI_TypeDef *SPI);
void     W25Qx_Reset();
void     W25Qx_Chip_Erase();
void     W25Qx_Erase_Block();
void     W25Qx_Erase_Sector(uint32_t address);

void     W25Qx_Write_Flash(uint32_t addr, uint8_t data);
void     W25Qx_Write_Flash_Buffer(uint32_t addr, int len, char *data);

uint8_t  W25Qx_Read_Flash(uint32_t addr);
void     W25Qx_Read_Flash_Buffer(uint32_t addr, int len, uint8_t *data);

void     W25Qx_Erase_Data(uint32_t start_address, uint32_t end_address);

void 	 W25Qx_Read_JEDEC_ID(void);
uint64_t W25Qx_Read_Unique_ID(void);
uint8_t  W25Qx_Read_Manufacturing_ID(void);
uint8_t  W25Qx_Read_Device_ID(void);

void W25Qx_Save_String(uint32_t addr,char *msg, ...);





#endif /* W25QX_FLASH_W25QX_FLASH_H_ */
