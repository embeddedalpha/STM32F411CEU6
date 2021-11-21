/*
 * I2C.h
 *
 *  Created on: 08-Jul-2021
 *      Author: Kunal
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

#include "main.h"
#include "GPIO/GPIO.h"

#define I2C_Fast_Mode	1
#define I2C_Normal_Mode	0


typedef struct I2C_Config
{
	I2C_TypeDef *I2C;
	bool mode;
}I2C_Config;


void I2C_Master_Init(I2C_Config I2C);

void I2C_Master_Start(I2C_Config I2C);

void I2C_Master_Address(I2C_Config I2C, uint8_t address, uint8_t read_write);

void I2C_Master_Send_Byte(I2C_Config I2C, uint8_t data);

void I2C_Master_Send_Buffer(I2C_Config I2C, uint8_t *data, int length);

void I2C_Master_Write_Register(I2C_Config I2C, uint8_t device_address, uint8_t reg_address, uint8_t data);

int I2C_Master_Receive_Byte(I2C_Config I2C);

void I2C_Master_NACK(I2C_Config I2C);

void I2C_Master_ACK(I2C_Config I2C);

void I2C_Master_Stop(I2C_Config I2C);


#endif /* I2C_I2C_H_ */
