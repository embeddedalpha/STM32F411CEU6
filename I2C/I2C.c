/*
 * I2C.c
 *
 *  Created on: 08-Jul-2021
 *      Author: Kunal
 */


#include "I2C.h"


int I2C_Master_Init(I2C_Config I2C)
{
	if (I2C.I2C == I2C1)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C1EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		//PB6 -> SCL
		//PB7 -> SDA
		GPIOB -> MODER = 0x00000000;
		GPIOB -> MODER  |= 0xa280;
		GPIOB -> OTYPER |= GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7;
		GPIOB -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7;
		GPIOB -> PUPDR |= GPIO_PUPDR_PUPD6_0 | GPIO_PUPDR_PUPD7_0;
		GPIOB -> AFR[0] |= (4 << 24) | (4 << 28);
		GPIOB -> IDR = 0x0000;
//		GPIOB -> IDR = 0xf7f8;

	}
	if (I2C.I2C == I2C2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C2EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		//PB3 -> SDA
		//PB4 -> SDA
		GPIOB -> MODER = 0x00000000;
		GPIOB -> MODER  = 0xa280;
		GPIOB -> OTYPER |= GPIO_OTYPER_OT3 | GPIO_OTYPER_OT4;
		GPIOB -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4;
		GPIOB -> AFR[0] |= (4 << 12) | (4 << 16);

	}
	if (I2C.I2C == I2C3)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C3EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
		//PA8 -> SDA
		//PB10 -> SCL
		GPIOA -> MODER   |= GPIO_MODER_MODE8 ;
		GPIOA -> OTYPER  |= GPIO_OTYPER_OT8 ;
		GPIOA -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 ;
		GPIOA -> AFR[1] |= (4 << 0) ;
		GPIOB -> MODER   |= GPIO_MODER_MODE10 ;
		GPIOB -> OTYPER  |= GPIO_OTYPER_OT10 ;
		GPIOB -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10 ;
		GPIOB -> AFR[1] |= (4 << 8) ;
	}

	if (I2C.mode)
	{
		I2C.I2C -> CR1 &= ~I2C_CR1_PE;
		I2C.I2C -> CR1 |= I2C_CR1_SWRST;
		I2C.I2C -> CR1 &= ~I2C_CR1_SWRST;

		I2C.I2C -> OAR1 = 0x4000;
		I2C.I2C -> CR2 = 0x30;
		I2C.I2C -> CCR = 0x8028; // 0x8F0 cd5
		I2C.I2C -> TRISE = 0xf;
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
	if(READ_BIT(I2C.I2C -> SR2, I2C_SR2_BUSY) == I2C_SR2_BUSY)
	{
		for(int i = 0; i < 1000; i++)
		{
			READ_BIT(I2C.I2C -> SR2, I2C_SR2_BUSY);
			I2C.I2C -> CR1 |= I2C_CR1_STOP;
			READ_REG(I2C.I2C -> DR);
		}
	}

	I2C.I2C -> CR1 |= I2C_CR1_START;
	while(!(I2C.I2C -> SR1 & I2C_SR1_SB)){}
	 reg1 = I2C1 ->SR1;
}

void I2C_Master_Send_Address(I2C_Config I2C, char address)
{
	I2C.I2C -> DR = (address << 1) | 0x00;
//	while(!(I2C.I2C -> SR1 & I2C_SR1_TXE)){}

	while((I2C.I2C -> SR1 & I2C_SR1_AF) == I2C_SR1_AF)
	{
		I2C.I2C -> DR = (address << 1) | 0x00;
	}
//		while(!(I2C.I2C->SR1 & I2C_SR1_ADDR));
		reg1 = I2C.I2C -> SR1;
		reg2 = I2C.I2C -> SR2;

}

int I2C_Master_Receive_Address(I2C_Config I2C, char address)
{
	I2C.I2C -> DR = (address << 1) | 0x01;
	while((I2C.I2C->SR1 & I2C_SR1_ADDR))
	{
		if ((I2C.I2C->SR1 & I2C_SR1_AF) == 1)
		{
			//ERROR HANDLING
			return 0;
		}
	}
	reg1 = I2C.I2C -> SR1;
	reg2 = I2C.I2C -> SR2;
return (int)(I2C.I2C->DR);
}

void I2C_Master_Send_Data(I2C_Config I2C, char data)
{
	I2C.I2C -> DR = data;
	while(!(I2C.I2C->SR1 & I2C_SR1_TXE));
}

char I2C_Master_Receive_Data(I2C_Config I2C)
{
	I2C.I2C -> CR1 |= I2C_CR1_POS;
	I2C.I2C -> CR1 |= I2C_CR1_ACK;


	char temp = 0;
	while(!(I2C.I2C->SR1 & I2C_SR1_BTF));
	I2C.I2C -> CR1 |= I2C_CR1_STOP;
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




void I2C_Send_Buffer(I2C_Config I2C, uint8_t address, uint8_t *buffer, int length)
{
		uint16_t reg;
	I2C.I2C -> CR1 &= ~I2C_CR1_POS;
	I2C.I2C -> CR1 |= I2C_CR1_START;
	while(!(I2C.I2C -> SR1 & I2C_SR1_SB)){}
	I2C.I2C -> DR = (address << 1) | 0x00;
	while(!(I2C.I2C -> SR1 & I2C_SR1_ADDR)){}
	reg = 0x00;
	reg = I2C.I2C -> SR1;
	reg = I2C.I2C -> SR2;
	while(!(I2C.I2C -> SR1 & I2C_SR1_TXE)){}
	for(int i = 0 ; i < length; i++)
	{
		I2C.I2C -> DR = buffer[i];
		while(!(I2C.I2C -> SR1 & I2C_SR1_TXE)){}
		while(!(I2C.I2C -> SR1 & I2C_SR1_BTF)){}
		reg = 0x00;
		reg = I2C.I2C -> SR1;
		reg = I2C.I2C -> SR2;
	}
	I2C.I2C -> CR1 |= I2C_CR1_STOP;
	reg = I2C.I2C -> SR1;
	reg = I2C.I2C -> SR2;
	
}
