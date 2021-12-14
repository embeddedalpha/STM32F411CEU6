/*
 * BMP280.h
 *
 *  Created on: 14-Dec-2021
 *      Author: Kunal
 */

#ifndef BMP280_BMP280_H_
#define BMP280_BMP280_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "I2C/I2C.h"
#include "SPI/SPI.h"


#define BMP280_SPI	0
#define BMP280_I2C	0

I2C_Config BMP280_I2C_Struct;
SPI_Config BMP280_SPI_Struct;

#define BMP280_Address	                    0x76
#define BMP280_ID_Register	                0xD0
#define BMP280_Reset_Register	            0xE0
#define BMP280_Status_Register	            0xF3
#define BMP280_Ctrl_Measurement_Register	0xF4
#define BMP280_Config_Register	            0xF5

#define BMP280_Pressure_MSB	                0xF7
#define BMP280_Pressure_LSB	                0xF8
#define BMP280_Pressure_XLSB	            0xF9

#define BMP280_Temperature_MSB	            0xFA
#define BMP280_Temperature_LSB	            0xFB
#define BMP280_Temperature_XLSB	            0xFC

#endif /* BMP280_BMP280_H_ */
