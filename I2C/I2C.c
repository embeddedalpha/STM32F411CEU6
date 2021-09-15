/*
 * I2C.c
 *
 *  Created on: 08-Jul-2021
 *  Updated on: 15-Sep-2021
 *      Author: Kunal
 */


#include "I2C.h"


int I2C_Master_Init(I2C_Config I2C)
{
	if (I2C.I2C == I2C1)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C1EN;
		GPIO_Pin_Setup('B', 6, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2C1_SCL);
		GPIO_Pin_Setup('B', 7, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2C1_SDA);

	}
	if (I2C.I2C == I2C2) //PB3 -> SDA	PB4 -> SDA
	{
		//PB3 -> SDA
		//PB4 -> SDA
		RCC -> APB1ENR |= RCC_APB1ENR_I2C2EN;
		GPIO_Pin_Setup('B', 3, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLUP, I2C2_SCL);
		GPIO_Pin_Setup('B', 4, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLUP, I2C2_SDA);

	}
	if (I2C.I2C == I2C3)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C3EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
		//PA8 -> SDA
		//PB10 -> SCL
		GPIO_Pin_Setup('A', 8, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLUP, I2C3_SCL);
		GPIO_Pin_Setup('B', 10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLUP, I2C3_SDA);
	}

	if (I2C.mode)
	{
		I2C.I2C -> CR1 &= ~I2C_CR1_PE;
		I2C.I2C -> CR1 |= I2C_CR1_SWRST;
		I2C.I2C -> CR1 &= ~I2C_CR1_SWRST;

		I2C.I2C -> OAR1 = 0x4000;
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

//	if((I2C.I2C->SR2 & I2C_SR2_BUSY) == 1)


return 0;
}


void I2C_Master_Start(I2C_Config I2C)
{
	uint16_t reg;
	I2C.I2C -> CR1 &= ~I2C_CR1_POS;
	I2C.I2C -> CR1 |= I2C_CR1_START;
	while(!(I2C.I2C -> SR1 & I2C_SR1_SB)){}
	 reg = I2C.I2C ->SR1;
}

void I2C_Master_Send_Address(I2C_Config I2C, char address)
{
	uint16_t reg1;
	I2C.I2C -> DR = (address << 1) | 0x00;
	while(!(I2C.I2C -> SR1 & I2C_SR1_ADDR)){}
	reg1 = 0x00;
	reg1 = I2C.I2C -> SR1;
	reg1 = I2C.I2C -> SR2;
	while(!(I2C.I2C -> SR1 & I2C_SR1_TXE)){}

}

void I2C_Master_Receive_Address(I2C_Config I2C, char address)
{
//	I2C.I2C -> CR1 |= I2C_CR1_ACK;
	I2C.I2C -> DR = (address << 1) | 0x01;
	while(!(I2C.I2C->SR1 & I2C_SR1_ADDR)){}
	reg1 = I2C.I2C -> SR1;
	reg2 = I2C.I2C -> SR2;

}

void I2C_Master_Send_Data(I2C_Config I2C, char data)
{
	I2C.I2C -> DR = data;
	while(!(I2C.I2C->SR1 & I2C_SR1_TXE));
}

char I2C_Master_Receive_Data(I2C_Config I2C)
{
//	I2C.I2C -> CR1 |= I2C_CR1_POS;
	I2C.I2C -> CR1 |= I2C_CR1_ACK;
	char temp = 0;
//	while(!(I2C.I2C->SR1 & I2C_SR1_BTF));
//	I2C.I2C -> CR1 |= I2C_CR1_STOP;
//	temp = I2C.I2C -> DR;
//	I2C.I2C -> CR1 |= I2C_CR1_ACK;
	while(!(I2C.I2C -> SR1 & I2C_SR1_RXNE)){}
	temp = I2C.I2C -> DR;
	I2C.I2C -> CR1 |= I2C_CR1_ACK;
	return temp;
}

void I2C_Master_Stop(I2C_Config I2C)
{
//	while(!(I2C.I2C->SR1 & I2C_SR1_TXE));
//	while(!(I2C.I2C->SR1 & I2C_SR1_BTF));

	I2C.I2C -> CR1 |= I2C_CR1_STOP;
}

void I2C_Master_Send_NACK(I2C_Config I2C)
{
	I2C.I2C -> CR1 &= ~I2C_CR1_ACK;
}
