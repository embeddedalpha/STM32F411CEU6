/*
 * I2S.c
 *
 *  Created on: 28-Jun-2021
 *      Author: Kunal
 */


#include "I2S.h"


void I2C_Master_Init(I2S_Config I2S)
{
	int plli2s_m = 12;
//	int plli2s_m = 16;
	int plli2s_n = 192;
	int plli2s_r = 2;
	uint8_t temp;
	RCC -> PLLI2SCFGR |= (plli2s_m << 0) | (plli2s_n << 6) | (plli2s_r << 28);
	//I2S_CLK = 200MHz
	//	RCC -> PLLI2SCFGR = 0x20003010;
	RCC -> CR |= RCC_CR_PLLI2SON;
	while(!(RCC -> CR & RCC_CR_PLLI2SRDY));

	if(I2S.I2S == SPI1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		GPIOA -> MODER |= (2 << 8) | (2 << 10) | (2 << 14) ;
		GPIOA -> OTYPER |= (0 << 4) | (0 << 5) | (0 << 7) ;
		GPIOA -> OSPEEDR |= (3 << 8) | (3 << 10) | (3 << 14) ;
		GPIOA -> PUPDR |= (0 << 8) | (0 << 10) | (0 << 14) ;
		GPIOA -> AFR[0] |= (5 << 8) | (5 << 10) | (5 << 14) ;
	}

	if(I2S.I2S == SPI2)
	{
		RCC -> APB1ENR |= RCC_APB2ENR_SPI2EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //pick from here
		GPIOA -> MODER |= (2 << 8) | (2 << 10) | (2 << 14) ;
		GPIOA -> OTYPER |= (0 << 4) | (0 << 5) | (0 << 7) ;
		GPIOA -> OSPEEDR |= (3 << 8) | (3 << 10) | (3 << 14) ;
		GPIOA -> PUPDR |= (0 << 8) | (0 << 10) | (0 << 14) ;
		GPIOA -> AFR[0] |= (5 << 8) | (5 << 10) | (5 << 14) ;
	}

	if(I2S.I2S == SPI3)
	{

	}

	if(I2S.I2S == SPI4)
	{

	}

	if(I2S.I2S == SPI5)
	{

	}

	I2S.I2S -> I2SCFGR |= SPI_I2SCFGR_I2SMOD;
	I2S.I2S -> I2SCFGR |= I2S.mode << 8;
	I2S.I2S -> I2SCFGR |= I2S.channel_length << 0;
	I2S.I2S -> I2SCFGR |= I2S.data_length << 1;
	I2S.I2S -> I2SCFGR |= I2S.standard << 4;

	if (I2S.data_length == 0)
	{
		temp = (uint8_t)((200000000/(I2S.audio_frequency * 16 * 2))/2);
		I2S.I2S -> I2SPR |= (1 << 8) | temp;
	}
	else
	{
		temp = (uint8_t)((200000000/(I2S.audio_frequency * 32 * 2))/2);
		I2S.I2S -> I2SPR |= (1 << 8) | temp;
	}

	I2S.I2S -> I2SCFGR |= SPI_I2SCFGR_I2SE;

}

void I2S_Master_Shut_Down(SPI_TypeDef *I2S)
{
	while(READ_BIT(I2S->SR,SPI_SR_BSY) == 1 && READ_BIT(I2S->SR,SPI_SR_TXE) == 0)
	{

	}
	I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SE;

}

uint32_t I2S_Master_Receive(SPI_TypeDef *I2S)
{
	uint16_t left,right;
	uint32_t packet;
	while(!(I2S -> SR & SPI_SR_RXNE));
	if((I2S->SR & SPI_SR_CHSIDE) == 0){
		left =  I2S -> DR;
	}
	else{
		right =  I2S -> DR;
	}

	packet = left << 16 | right;
	return packet;
}


void I2S_Master_Transmit(SPI_TypeDef *I2S, uint16_t tx)
{
	I2S->DR = tx;
	while(!(I2S -> SR & SPI_SR_TXE));
}



