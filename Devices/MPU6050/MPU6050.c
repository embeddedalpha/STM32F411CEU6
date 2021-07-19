/*
 * MPU6050.c
 *
 *  Created on: 08-Jul-2021
 *      Author: Kunal
 */


#include "MPU6050.h"

void MPU6050_I2C_Init(I2C_TypeDef *I2C)
{
	MPU6050.I2C = I2C;
	MPU6050.mode = Fast_Mode;
	I2C_Master_Init(MPU6050);
	I2C_Master_Start(MPU6050);
	I2C_Master_Send_Address(MPU6050, 0x68);
	I2C_Master_Send_Data(MPU6050, MPU6050_RA_PWR_MGMT_1); //0x6b
	I2C_Master_Send_Data(MPU6050, 0x01);
	I2C_Master_Send_Data(MPU6050, MPU6050_RA_CONFIG); //0x1a
	I2C_Master_Send_Data(MPU6050, 0x01);
	I2C_Master_Send_Data(MPU6050, MPU6050_RA_GYRO_CONFIG); //0x1b
	I2C_Master_Send_Data(MPU6050, 0x10);
	I2C_Master_Send_Data(MPU6050, MPU6050_RA_ACCEL_CONFIG); //0x1c
	I2C_Master_Send_Data(MPU6050, 0x00);
	I2C_Master_Send_Data(MPU6050, MPU6050_RA_INT_ENABLE); //0x3b8
	I2C_Master_Send_Data(MPU6050, 0x00);
	I2C_Master_Send_Data(MPU6050, MPU6050_RA_SIGNAL_PATH_RESET); //0x68
	I2C_Master_Send_Data(MPU6050, 0x00);
	I2C_Master_Stop(MPU6050);
}


void MPU6050_I2C_Write_Single(uint8_t reg, uint8_t data)
{
	I2C_Master_Start(MPU6050);
	I2C_Master_Send_Address(MPU6050, MPU6050_Dev_Add);
	I2C_Master_Send_Data(MPU6050, reg);
	I2C_Master_Send_Data(MPU6050, data);
	I2C_Master_Stop(MPU6050);
}

void MPU6050_I2C_Write_Burst(uint8_t reg, uint8_t *data, int len)
{
	int i = 0;
	I2C_Master_Start(MPU6050);
	I2C_Master_Send_Address(MPU6050, MPU6050_Dev_Add);
	for(i = 0; i < len; i++)
	{
		I2C_Master_Send_Data(MPU6050, data[i]);
	}
	I2C_Master_Stop(MPU6050);
}



char MPU6050_Register_Read(uint8_t reg_address)
{
	char temp;
	I2C_Master_Start(MPU6050);
	I2C_Master_Send_Address(MPU6050, MPU6050_Dev_Add);
	I2C_Master_Send_Data(MPU6050, reg_address);
	I2C_Master_Start(MPU6050);
	I2C_Master_Receive_Address(MPU6050, 0x68);
	temp = I2C_Master_Receive_Data(MPU6050);
	I2C_Master_Send_NACK(MPU6050);
	I2C_Master_Stop(MPU6050);
	return temp;
}

void MPU6050_I2C_Read_Burst(uint8_t reg, uint8_t *data, int len)
{
	int i;
	I2C_Master_Start(MPU6050);
	I2C_Master_Send_Address(MPU6050, MPU6050_Dev_Add);
	I2C_Master_Start(MPU6050);
	I2C_Master_Receive_Address(MPU6050, MPU6050_Dev_Add);
	for(i = 0; i < len; i++)
	{
		data[i] = I2C_Master_Receive_Data(MPU6050);
	}
	I2C_Master_Send_NACK(MPU6050);
	I2C_Master_Stop(MPU6050);

}

void MPU6050_I2C_Get_Raw_Data(uint16_t *accl_x,
		                  uint16_t *accl_y,
						  uint16_t *accl_z,
						  uint16_t *gyro_x,
						  uint16_t *gyro_y,
						  uint16_t *gyro_z)
{
	uint8_t x[14];
	MPU6050_I2C_Read_Burst(MPU6050_RA_GYRO_ZOUT_L, x, 14);
	*accl_x = (x[1] << 8 | x[0]);
	*accl_y = x[3] << 8 | x[2];
	*accl_z = x[5] << 8 | x[4];
	*gyro_x = x[9] << 8 | x[10];
	*gyro_y = x[11] << 8 | x[11];
	*gyro_z = x[13] << 8 | x[12];
}

void MPU6050_I2C_Get_Filtered_Data(uint16_t *accl_x,
                                   uint16_t *accl_y,
		                           uint16_t *accl_z,
		                           uint16_t *gyro_x,
		                           uint16_t *gyro_y,
		                           uint16_t *gyro_z)
{
	uint8_t x[14];
	MPU6050_I2C_Read_Burst(MPU6050_RA_GYRO_ZOUT_L, x, 14);
	*accl_x = (x[1]  << 8) + x[0];
	*accl_y = (x[3]  << 8) + x[0];
	*accl_z = (x[5]  << 8) + x[0];
	*gyro_x = (x[9]  << 8) + x[10];
	*gyro_y = (x[11] << 8) + x[11];
	*gyro_z = (x[13] << 8) + x[12];
}
