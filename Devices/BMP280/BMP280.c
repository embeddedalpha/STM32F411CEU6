/*
 * BMP280.c
 *
 *  Created on: 14-Dec-2021
 *      Author: Kunal
 */


#include "BMP280.h"

#if	BMP280_I2C

static int BMP280_Read_ID(void)
{
	uint8_t x;
	x = I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_ID_Register);
	return x;
}

static void BMP280_Reset(void)
{
	I2C_Master_Write_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Reset_Register, 0xB6);
}

void BMP280_Init(I2C_TypeDef *I2C)
{

}

uint32_t BMP280_Read_Pressure(void)
{
	uint32_t x;

	x = (uint32_t)(
			I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Pressure_MSB) << 16 |
			I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Pressure_LSB) << 8 |
			I2C_Master_Read_Register(BMP280_I2C_Struct, BMP280_Address, BMP280_Pressure_XLSB) << 0 |
	);
	return x;
}

#endif


#if	BMP280_SPI

void BMP280_Init(SPI_TypeDef *SPI)
{

}

int BMP280_Read_Data(void)
{

}

#endif
