/*
 * I2S.c
 *
 *  Created on: 28-Jun-2021
 *      Author: Kunal
 */


#include "I2S.h"


//
//void I2S_Master_Transmit(SPI_TypeDef *I2S, uint16_t tx);



void I2S_Master_Init(I2S_Config I2S)
{
	int x;
	I2S_Clock_Init();
	if (I2S.I2S == I2S1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		GPIOA -> MODER |= (2 << 8) | (2 << 10) | (2 << 14) ;
		GPIOA -> OTYPER |= (0 << 4) | (0 << 5) | (0 << 7) ;
		GPIOA -> OSPEEDR |= (3 << 8) | (3 << 10) | (3 << 14) ;
		GPIOA -> PUPDR |= (0 << 8) | (0 << 10) | (0 << 14) ;
		GPIOA -> AFR[0] |= (5 << 16) | (5 << 20) | (5 << 28) ;
	}
	if(I2S.I2S == I2S2)	//CK -> PB10 	//WS -> PB12 	//SD -> PB15
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		GPIOB -> MODER    |= (2 << (2 * 10))  | (2 << (2 * 12)) | (2 << (2 * 15));
		GPIOB -> OTYPER   |= (0 << (1 * 10))  | (0 << (1 * 12)) | (0 << (1 * 15));
		GPIOB -> OSPEEDR  |= (3 << (2 * 10))  | (3 << (2 * 12)) | (3 << (2 * 15));
		GPIOB -> PUPDR    |= (0 << (2 * 10))  | (0 << (2 * 12)) | (0 << (2 * 15));
		GPIOB -> AFR[1]   |= (5 << (4 * (10-8)))  | (5 << (4 * (12-8))) | (5 << (4 * (15-8)));
	}
	if(I2S.I2S == I2S3)	//CK -> PB3 	//WS -> PA15 	//SD -> PB5
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
		GPIOB -> MODER    |= (2 << (2 * 5))  | (2 << (2 * 3)) ;
		GPIOB -> OTYPER   |= (0 << (1 * 5))  | (0 << (1 * 3)) ;
		GPIOB -> OSPEEDR  |= (3 << (2 * 5))  | (3 << (2 * 3)) ;
		GPIOB -> PUPDR    |= (0 << (2 * 5))  | (0 << (2 * 4)) ;
		GPIOB -> AFR[0]   |= (5 << (4 * (3-0)))  | (5 << (4 * (5-0))) ;

		GPIOA -> MODER    |= (2 << (2 * 15))  ;
		GPIOA -> OTYPER   |= (0 << (1 * 15)) ;
		GPIOA -> OSPEEDR  |= (3 << (2 * 15)) ;
		GPIOA -> PUPDR    |= (0 << (2 * 15)) ;
		GPIOA -> AFR[1]   |= (5 << (4 * (15-8))) ;
	}
	if(I2S.I2S == I2S4)	//CK -> PB13 	//WS -> PB12 	//SD -> PA1
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
		GPIOB -> MODER    |= (2 << (2 * 12))  | (2 << (2 * 13)) ;
		GPIOB -> OTYPER   |= (0 << (1 * 12))  | (0 << (1 * 13)) ;
		GPIOB -> OSPEEDR  |= (3 << (2 * 12))  | (3 << (2 * 13)) ;
		GPIOB -> PUPDR    |= (0 << (2 * 12))  | (0 << (2 * 13)) ;
		GPIOB -> AFR[1]   |= (5 << (4 * (13-8)))  | (5 << (4 * (12-8))) ;

		GPIOA -> MODER    |= (2 << (2 * 1)) ;
		GPIOA -> OTYPER   |= (0 << (1 * 1)) ;
		GPIOA -> OSPEEDR  |= (3 << (2 * 1)) ;
		GPIOA -> PUPDR    |= (0 << (2 * 1)) ;
		GPIOA -> AFR[0]   |= (5 << (4 * (1-0))) ;
	}
	if(I2S.I2S == I2S5)	//CK -> PB0 	//WS -> PB1 	//SD -> PA10
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
		GPIOB -> MODER    |= (2 << (2 * 0))  | (2 << (2 * 1)) ;
		GPIOB -> OTYPER   |= (0 << (1 * 0))  | (0 << (1 * 1)) ;
		GPIOB -> OSPEEDR  |= (3 << (2 * 0))  | (3 << (2 * 1)) ;
		GPIOB -> PUPDR    |= (0 << (2 * 0))  | (0 << (2 * 1)) ;
		GPIOB -> AFR[0]   |= (5 << (4 * (1-0)))  | (5 << (4 * (0-0))) ;

		GPIOA -> MODER    |= (2 << (2 * 10)) ;
		GPIOA -> OTYPER   |= (0 << (1 * 10)) ;
		GPIOA -> OSPEEDR  |= (3 << (2 * 10)) ;
		GPIOA -> PUPDR    |= (0 << (2 * 10)) ;
		GPIOA -> AFR[1]   |= (5 << (4 * (10-8))) ;
	}
	I2S.I2S -> I2SCFGR |= (SPI_I2SCFGR_I2SMOD |
			               (I2S.mode << 8) |
						   (I2S.standard << 4) |
						   (I2S.data_length << 1) |
						   (I2S.channel_length << 0));

	if (I2S.channel_length == Channel_16bit)
	{
		x =(int)((172000000)/((16 * 2) * (2 * I2S.audio_frequency)));
		I2S.I2S ->I2SPR = x;
	}
	else if (I2S.channel_length == Channel_32bit)
	{
		x =(int)((172000000)/((32 * 2) * (2 * I2S.audio_frequency)));
		I2S.I2S ->I2SPR = x;
	}
}

void I2S_Master_Shut_Down(I2S_Config I2S)
{
	I2S.I2S ->I2SCFGR &= ~SPI_I2SCFGR_I2SMOD;
}

int32_t I2S_Master_Receive_Left_Channel(I2S_Config I2S)
{
	while(!(I2S.I2S -> SR & SPI_SR_RXNE) & (I2S.I2S-> SR & SPI_SR_CHSIDE)){}
	return  (I2S.I2S -> DR);
}

int32_t I2S_Master_Receive_Right_Channel(I2S_Config I2S)
{
	while(!(I2S.I2S -> SR & SPI_SR_RXNE) & !(I2S.I2S-> SR & SPI_SR_CHSIDE)){}
	return  (I2S.I2S -> DR);
}




//void I2S_Master_Init(I2S_Config I2S)
//{
//	I2S_Clock_Init();
//	if (I2S.I2S == I2S1)
//	{
//		RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
//		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//		GPIOA -> MODER |= (2 << 8) | (2 << 10) | (2 << 14) ;
//		GPIOA -> OTYPER |= (0 << 4) | (0 << 5) | (0 << 7) ;
//		GPIOA -> OSPEEDR |= (3 << 8) | (3 << 10) | (3 << 14) ;
//		GPIOA -> PUPDR |= (0 << 8) | (0 << 10) | (0 << 14) ;
//		GPIOA -> AFR[0] |= (5 << 16) | (5 << 20) | (5 << 28) ;
//
//
//
//		SPI1 -> I2SCFGR = 0xb05;
//		//SPI1 -> I2SPR = 0x118;
//		SPI1 -> I2SPR = 0x01C;
//		//SPI1 -> I2SPR = 0x10B;
//		SPI1 -> I2SCFGR |= 1 << 10;
//	}
//
//}

