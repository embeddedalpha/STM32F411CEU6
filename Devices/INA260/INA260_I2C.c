/*
 * INA260.c
 *
 *  Created on: 22-Sep-2021
 *      Author: Kunal
 */


#include "INA260.h"

void INA260_Init(I2C_TypeDef *I2C)
{

	INA280.I2C = I2C;
	INA280.mode = Fast_Mode;
	I2C_Master_Init(INA280);

	char high_byte, low_byte;
	I2C_Master_Init(INA280);
	I2C_Master_Start(INA280);
	I2C_Master_Send_Address(INA280, INA260_Address);
	high_byte = (3 << 1) ;
	low_byte  = (3 << 6)  | (3 << 3) ;
	I2C_Master_Send_Data(INA280, Configuration_Register_INA260);
	I2C_Master_Send_Data(INA280, high_byte );
	I2C_Master_Send_Data(INA280, low_byte);
	I2C_Master_Stop(INA280);
}

void INA260_Mode(uint8_t mode)
{
	I2C_Master_Start(INA280);
	I2C_Master_Send_Address(INA280, INA260_Address);
	I2C_Master_Send_Data(INA280, Configuration_Register_INA260);
	I2C_Master_Send_Data(INA280, 0x00);
	I2C_Master_Send_Data(INA280, mode << 0);
	I2C_Master_Stop(INA280);
}


float INA260_Get_Current(void)
{
	float current_dummy;
	uint8_t high_byte, low_byte;
	I2C_Master_Start(INA280);
	I2C_Master_Receive_Address(INA280, INA260_Address);
	I2C_Master_Send_Data(INA280, Current_Register_INA260);
	high_byte = I2C_Master_Receive_Data(INA280);
	low_byte = I2C_Master_Receive_Data(INA280);
	I2C_Master_Stop(INA280);
	current_dummy = ( ( high_byte << 8 ) | ( low_byte << 0) ) * 0.00125;
	return current_dummy;
}

float INA260_Get_Voltage(void)
{
	float voltage_dummy;
	char high_byte, low_byte;
	I2C_Master_Start(INA280);
	I2C_Master_Receive_Address(INA280, INA260_Address);
	I2C_Master_Send_Data(INA280, Bus_Voltage_Register_INA260);
	high_byte = I2C_Master_Receive_Data(INA280);
	low_byte = I2C_Master_Receive_Data(INA280);
	I2C_Master_Stop(INA280);
	voltage_dummy = ( ( high_byte << 8 ) | ( low_byte << 0) ) * 0.00125;
	return voltage_dummy;
}

float INA260_Get_Power(void)
{
	float power_dummy;
	char high_byte, low_byte;
	I2C_Master_Start(INA280);
	I2C_Master_Receive_Address(INA280, INA260_Address);
	I2C_Master_Send_Data(INA280, Power_Register_INA260);
	high_byte = I2C_Master_Receive_Data(INA280);
	low_byte = I2C_Master_Receive_Data(INA280);
	I2C_Master_Stop(INA280);
	power_dummy = ( ( high_byte << 8 ) | ( low_byte << 0) ) * 0.01;
	return power_dummy;
}

