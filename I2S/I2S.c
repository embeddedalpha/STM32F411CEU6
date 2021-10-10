/*
 * I2S.c
 *
 *  Created on: 28-Jun-2021
 *  Updated on: 15-Sep-2021
 *      Author: Kunal
 */


#include "I2S.h"


void I2S_Master_Init(I2S_Config I2S)
{
	int x;
	I2S_Clock_Init();
	if (I2S.I2S == I2S1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
		GPIO_Pin_Setup('A', 4, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S1_WS);
		GPIO_Pin_Setup('A', 5, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S1_CK);
		GPIO_Pin_Setup('A', 7, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S1_SD);

	}
	if(I2S.I2S == I2S2)	//CK -> PB10 	//WS -> PB12 	//SD -> PB15
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;
        GPIO_Pin_Setup('B', 10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S2_CK);
		GPIO_Pin_Setup('B', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S2_WS);
		GPIO_Pin_Setup('B', 15, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S2_SD);
	}
	if(I2S.I2S == I2S3)	//CK -> PB12 	//WS -> PA15 	//SD -> PB5
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
		GPIO_Pin_Setup('B', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S3_CK);
		GPIO_Pin_Setup('A', 15, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S3_WS);
		GPIO_Pin_Setup('B', 5, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S3_SD);
	}
	if(I2S.I2S == I2S4)	//CK -> PB13 	//WS -> PB12 	//SD -> PA1
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI4EN;
		GPIO_Pin_Setup('A', 1,  ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S4_SD);
		GPIO_Pin_Setup('B', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S4_WS);
		GPIO_Pin_Setup('B', 13, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S4_CK);
	}
	if(I2S.I2S == I2S5)	//CK -> PB0 	//WS -> PB1 	//SD -> PA10
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI5EN;
		GPIO_Pin_Setup('B', 0, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S5_CK);
		GPIO_Pin_Setup('B', 1, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S5_WS);
		GPIO_Pin_Setup('A', 10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S5_SD);
	}
	I2S.I2S -> I2SCFGR |= (SPI_I2SCFGR_I2SMOD |
			               (I2S.mode << 8) |
						   (I2S.standard << 4) |
						   (I2S.data_length << 1) |
						   (I2S.channel_length << 0));

	if (I2S.channel_length == Channel_16bit)
	{
		x =(int)round(((172000000)/((16 * 2) * (2 * I2S.audio_frequency))));
		x = x + 1;
		I2S.I2S ->I2SPR = x;
	}
	else if (I2S.channel_length == Channel_32bit)
	{
		x =(int)(((172000000)/((32 * 2) * (2 * I2S.audio_frequency))));
		x = x + 1;
		I2S.I2S ->I2SPR = x;
	}
	I2S.I2S -> I2SPR |= 1 << 8; //ODD

	if( I2S.RX_Interrupt == 1 ) I2S.I2S -> CR2 |= SPI_CR2_RXNEIE;
	else I2S.I2S -> CR2 &= ~SPI_CR2_RXNEIE;

	if( I2S.TX_Interrupt == 1 ) I2S.I2S -> CR2 |= SPI_CR2_TXEIE;
	else I2S.I2S -> CR2 &= ~SPI_CR2_TXEIE;




	if(I2S.TX_DMA)
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		DMA2_Stream0 -> CR |= ( 3 << 25 ) | (1 << 10) | (1 << 8) | (1 << 6) | (1 << 4) | (1 << 3) |
		(1 << 2) |  (1 << 1);
		DMA2_Stream0 -> NDTR = I2S.length;
		DMA2_Stream0 -> M0AR = (uint32_t)&(I2S.data);
		DMA2_Stream0 -> PAR = (uint32_t)&(I2S.I2S -> DR);

		I2S.I2S -> CR2 |= SPI_CR2_TXDMAEN;

	}
	else
	{
		RCC -> AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
		DMA2_Stream0 -> CR = 0x00000000;
		DMA2_Stream0 -> NDTR = 0;
		DMA2_Stream0 -> M0AR = 0;
		DMA2_Stream0 -> PAR = 0;
		I2S.I2S -> CR2 &= ~SPI_CR2_TXDMAEN;
	}
	if(I2S.RX_DMA)
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
		DMA2_Stream0 -> CR |= ( 3 << 25 ) | (1 << 11) | (1 << 10) | (1 << 8) | (0 << 6) | (1 << 4) | (1 << 3) |
		(1 << 2) |  (1 << 1);
		DMA2_Stream0 -> NDTR = I2S.length;
		DMA2_Stream0 -> M0AR = (uint32_t)&(I2S.data);
		DMA2_Stream0 -> PAR = (uint32_t)&(I2S.I2S -> DR);
		I2S.I2S -> CR2 |= SPI_CR2_RXDMAEN;

	}
	else
	{
		RCC -> AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
		DMA2_Stream0 -> CR = 0x00000000;
		DMA2_Stream0 -> NDTR = 0;
		DMA2_Stream0 -> M0AR = 0;
		DMA2_Stream0 -> PAR = 0;
		I2S.I2S -> CR2 &= ~SPI_CR2_RXDMAEN;
	}




}


void I2S_Master_Start(I2S_Config I2S)
{
	I2S.I2S -> I2SCFGR |= SPI_I2SCFGR_I2SE;
}

void I2S_Master_Shut_Down(I2S_Config I2S)
{
	I2S.I2S ->I2SCFGR &= ~SPI_I2SCFGR_I2SMOD;
}

int16_t I2S_Master_Receive_Left_Channel(I2S_Config I2S)
{
	while(!(I2S.I2S-> SR & SPI_SR_CHSIDE)){}
	return  (I2S.I2S -> DR);

}

int16_t I2S_Master_Receive_Right_Channel(I2S_Config I2S)
{
	while((I2S.I2S-> SR & SPI_SR_CHSIDE)){}
	return  (I2S.I2S -> DR);
}


void I2S_Master_Transmit_Left_Channel(I2S_Config I2S, int16_t data)
{

	while((I2S.I2S-> SR & SPI_SR_CHSIDE)){}
	I2S.I2S -> DR = data;


}

void I2S_Master_Transmit_Right_Channel(I2S_Config I2S, int16_t data)
{
	while(!(I2S.I2S-> SR & SPI_SR_CHSIDE)){}
	I2S.I2S -> DR = data;

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
//		SPI1 -> I2SCFGR = 0xb05;
//		//SPI1 -> I2SPR = 0x118;
//		SPI1 -> I2SPR = 0x01C;
//		//SPI1 -> I2SPR = 0x10B;
//		SPI1 -> I2SCFGR |= 1 << 10;
//	}
//
//}


//RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
//		RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
//		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//		GPIOA -> MODER |= (2 << 8) | (2 << 10) | (2 << 14) ;
//		GPIOA -> OTYPER |= (0 << 4) | (0 << 5) | (0 << 7) ;
//		GPIOA -> OSPEEDR |= (3 << 8) | (3 << 10) | (3 << 14) ;
//		GPIOA -> PUPDR |= (0 << 8) | (0 << 10) | (0 << 14) ;
//		GPIOA -> AFR[0] |= (5 << 16) | (5 << 20) | (5 << 28) ;
//
////		SPI1 ->CR2 |= SPI_CR2_RXDMAEN;
//
//		SPI1 -> I2SCFGR |= 1 << 11; //I2SMODE
//		SPI1 -> I2SCFGR |= 3 << 8; //I2SCFG
//		SPI1 -> I2SCFGR |= 0 << 0; //CHLEN
//		SPI1 -> I2SCFGR |= 0 << 1; //DATLEN
//		SPI1 -> I2SCFGR |= 0 << 0; //CKPOL
//
//
//
//		SPI1 -> I2SCFGR |= 0 << 0; //I2SSTD
//		SPI1 -> I2SCFGR |= 0 << 0; //PCMSYNC
//
//
//		SPI1 -> I2SPR = 56; //0x1c 12
//		SPI1 -> I2SPR |= 1 << 8; //ODD
//		SPI1 -> I2SCFGR |= 1 << 10;
//while(!(SPI1 -> SR & SPI_SR_CHSIDE)){
//	int16_t x = (SPI1 -> DR);
//	printConsole("%ld \n\r",x);
//}
//SPI1 -> I2SCFGR |= 1 << 10;
