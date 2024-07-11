/*
 * I2C.c
 *
 *  Created on: 08-Jul-2021
 *  Updated on: 15-Sep-2021
 *      Author: Kunal
 */


#include "I2C.h"


void I2C_Master_Init(I2C_Config I2C)
{
	if (I2C.I2C == I2C1)
		{
			RCC -> APB1ENR |= RCC_APB1ENR_I2C1EN;
			GPIO_Pin_Setup('B', 6, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, I2C1_SCL);
			GPIO_Pin_Setup('B', 7, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, I2C1_SDA);

		}
		if (I2C.I2C == I2C2) //PB3 -> SDA	PB4 -> SDA
		{
			//PB3 -> SDA
			//PB4 -> SDA
			RCC -> APB1ENR |= RCC_APB1ENR_I2C2EN;
			GPIO_Pin_Setup('B', 3, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, I2C2_SCL);
			GPIO_Pin_Setup('B', 4, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, I2C2_SDA);

		}
		if (I2C.I2C == I2C3)
		{
			RCC -> APB1ENR |= RCC_APB1ENR_I2C3EN;
			RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
			//PA8 -> SDA
			//PB10 -> SCL
			GPIO_Pin_Setup('A', 8, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, I2C3_SCL);
			GPIO_Pin_Setup('B', 10, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, I2C3_SDA);
		}

		if (I2C.mode)
		{
			I2C.I2C -> CR1 &= ~I2C_CR1_PE;
			I2C.I2C -> CR1 |= I2C_CR1_SWRST;
			I2C.I2C -> CR1 &= ~I2C_CR1_SWRST;

	//		I2C.I2C -> OAR1 = 0x4000;
			I2C.I2C -> CR2 = 0x30; //48MHz
			I2C.I2C -> CCR = 0x8028; //FS mode | 40
			I2C.I2C -> TRISE = 0xf;
			I2C.I2C -> CR1 |= I2C_CR1_NOSTRETCH;
			I2C.I2C -> CR1 |= I2C_CR1_PE;
		}
		else
		{
			I2C.I2C -> CR2 = 0x8;
			I2C.I2C -> CCR = 0x28;
			I2C.I2C -> TRISE = 0x8;
			I2C.I2C -> CR1 |= I2C_CR1_PE;
			I2C.I2C -> CR1 &= ~I2C_CR1_POS;
		}

}

void I2C_Master_Start(I2C_Config I2C)
{
	volatile int temp;
//	temp = I2C.I2C -> SR1 | I2C.I2C -> SR2;
	I2C.I2C -> CR1 |= I2C_CR1_START;
	while(!(I2C.I2C -> SR1 & I2C_SR1_SB)){}
}

void I2C_Master_Address(I2C_Config I2C, uint8_t address, uint8_t read_write)
{
	volatile int temp;
	I2C.I2C -> DR = address << 1  | read_write;
	while((I2C.I2C -> SR1 & 2) == 0){}
	while((I2C.I2C -> SR1 & 2))
	{
		temp = I2C.I2C -> SR1;
		temp = I2C.I2C -> SR2;
		if((I2C.I2C -> SR1 & 2) == 0)
		{
			break;
		}
	}
}

void I2C_Master_Send_Byte(I2C_Config I2C, uint8_t data)
{
	while((I2C.I2C -> SR1 & 0x80) == 0){}
	I2C.I2C -> DR = data;
	while((I2C.I2C -> SR1 & 0x80) == 0){}
}

void I2C_Master_Send_Buffer(I2C_Config I2C, uint8_t *data, int length)
{
	for(int i = 0; i < length; i++)
	{
		while((I2C.I2C -> SR1 & 0x80) == 0){}
		I2C.I2C -> DR = data[i];
		while((I2C.I2C -> SR1 & 0x80) == 0){}
	}
}

int I2C_Master_Receive_Byte(I2C_Config I2C)
{
	volatile int temp;
	I2C.I2C -> CR1 |= I2C_CR1_ACK;
	while((I2C.I2C -> SR1 & I2C_SR1_RXNE) == 0){}
	temp = I2C.I2C -> DR;
	I2C.I2C -> CR1 &= ~I2C_CR1_ACK;
	return temp;
}

void I2C_Master_NACK(I2C_Config I2C)
{
	I2C.I2C -> CR1 &= ~I2C_CR1_ACK;
}

void I2C_Master_ACK(I2C_Config I2C)
{
	I2C.I2C -> CR1 |= I2C_CR1_ACK;
}

void I2C_Master_Stop(I2C_Config I2C)
{
//	volatile int temp;
//	temp = I2C.I2C -> SR1 | I2C.I2C -> SR2;
	I2C.I2C -> CR1 |= I2C_CR1_STOP;
}

/*****************************************************************************************/

void I2C_Master_Write_Register(I2C_Config I2C, uint8_t device_address, uint8_t reg_address, uint8_t data)
{
	I2C_Master_Start(I2C);
	I2C_Master_Address(I2C, device_address,0);
	I2C_Master_Send_Byte(I2C, reg_address);
	I2C_Master_Send_Byte(I2C, data);
	I2C_Master_Stop(I2C);
}

int I2C_Master_Read_Register(I2C_Config I2C, uint8_t device_address, uint8_t reg_address)
{
	volatile int temp;
	I2C_Master_Start(I2C);
	I2C_Master_Address(I2C, device_address, 0);
	I2C_Master_Send_Byte(I2C, reg_address);
	I2C_Master_Stop(I2C);
	I2C_Master_Start(I2C);
	I2C_Master_Address(I2C, device_address, 1);
	temp = I2C_Master_Receive_Byte(I2C);
	I2C_Master_Stop(I2C);
	return temp;
}

void I2C_Master_Set_Bit(I2C_Config I2C,uint8_t device_address, uint8_t reg_address, uint8_t byte_postition)
{
	int temp;
	temp = I2C_Master_Read_Register(I2C, device_address, reg_address);
	temp |= 1 << byte_postition;
	I2C_Master_Write_Register(I2C, device_address, reg_address, temp);
}


void I2C_Master_Reset_Bit(I2C_Config I2C,uint8_t device_address, uint8_t reg_address, uint8_t byte_postition)
{
	int temp;
	temp = I2C_Master_Read_Register(I2C, device_address, reg_address);
	temp &= ~(1 << byte_postition);
	I2C_Master_Write_Register(I2C, device_address, reg_address, temp);
}
