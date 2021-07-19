/*
 * MPU6050.h
 *
 *  Created on: 08-Jul-2021
 *      Author: Kunal
 */

#ifndef MPU6050_MPU6050_H_
#define MPU6050_MPU6050_H_

#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "MPU6050_Reg.h"
#include "I2C/I2C.h"
#include "main.h"

struct I2C_Config MPU6050;
#define MPU6050_Dev_Add	0x68

void MPU6050_I2C_Init();
void MPU6050_I2C_Write_Single(uint8_t reg, uint8_t data);
void MPU6050_I2C_Write_Burst(uint8_t reg, uint8_t *data, int len);
char MPU6050_Register_Read(uint8_t reg_address);
void MPU6050_I2C_Read_Burst(uint8_t reg, uint8_t *data, int len);
void MPU6050_I2C_Get_Raw_Data(uint16_t *accl_x,
		                  uint16_t *accl_y,
						  uint16_t *accl_z,
						  uint16_t *gyro_x,
						  uint16_t *gyro_y,
						  uint16_t *gyro_z);
void MPU6050_I2C_Get_Filtered_Data(uint16_t *accl_x,
                                   uint16_t *accl_y,
		                           uint16_t *accl_z,
		                           uint16_t *gyro_x,
		                           uint16_t *gyro_y,
		                           uint16_t *gyro_z);


#endif /* MPU6050_MPU6050_H_ */
