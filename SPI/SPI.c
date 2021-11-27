/*
 * SPI.c
 *
 *  Created on: 18-Jul-2021
 *      Author: Kunal
 */

#include "SPI.h"

void SPI_Init(SPI_Config SPI)
{
	if (SPI.SPI == SPI1)   //CK -> PA5 	//MISO -> PA6 	//MOSI -> PA7
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
		GPIO_Pin_Setup(GPIOA, 5, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, SPI1_CLK);
		GPIO_Pin_Setup(GPIOA, 6, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, SPI1_MISO);
		GPIO_Pin_Setup(GPIOA, 7, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, SPI1_MOSI);

	}
	if(SPI.SPI == SPI2)	//CK -> PB10 	//MISO -> PB14 	//MOSI -> PB15
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;
        GPIO_Pin_Setup(GPIOB, 10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOB, 14, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOB, 15, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}
	if(SPI.SPI == SPI3)	//CK -> PB12 	//MISO -> PB4 	//MOSI -> PB5
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
		GPIO_Pin_Setup(GPIOB, 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOB, 4, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOB, 5, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}
	if(SPI.SPI == SPI4)	//CK -> PB13 	//MISO -> PA11 	//MOSI -> PA1
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI4EN;
		GPIO_Pin_Setup(GPIOB, 13, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOB, 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOA, 1, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}
	if(SPI.SPI == SPI5)	//CK -> PB0 	//MISO -> PA12 	//MOSI -> PB8
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI5EN;
		GPIO_Pin_Setup(GPIOB, 0, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOB, 8, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup(GPIOA, 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}

	SPI.SPI -> CR1 &= ~SPI_CR1_SPE;
	SPI.SPI -> CR1 |= SPI.phase << 0;
	SPI.SPI -> CR1 |= SPI.polarity << 1;
	SPI.SPI -> CR1 |= SPI.mode  << 2;
	SPI.SPI -> CR1 |= SPI.frequency << 3;
	SPI.SPI -> CR1 |= SPI.Frame << 11;
	SPI.SPI -> CR1 |= SPI.CRC_Enable << 13;
	SPI.SPI -> CR1 |= SPI.LSB_MSB << 7;

	SPI.SPI -> CR1 &= ~SPI_CR1_SSM;

	SPI.SPI -> CR2 |= SPI.DMA_TX << 1 | SPI.DMA_RX << 0 | SPI_CR2_SSOE ;

	if(SPI.mode == SPI_Master)
	{
		SPI.SPI -> CR1 |= SPI_CR1_MSTR;
		switch (SPI.type)
		{
			case SPI_Full_Duplex_Master:
				SPI.SPI -> CR1 &= ~SPI_CR1_BIDIMODE;
				break;
			case SPI_Half_Duplex_Master_TX:
				SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE;
				SPI.SPI -> CR1 |= SPI_CR1_BIDIOE;
				break;
			case SPI_Half_Duplex_Master_RX:
				SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE;
				SPI.SPI -> CR1 &= ~SPI_CR1_BIDIOE;
				break;
			default:
				break;
		}
	}

	if(SPI.mode == SPI_Slave)
	{
	SPI.SPI -> CR1 &= ~SPI_CR1_MSTR;
	switch (SPI.type)
	 {
		case SPI_Full_Duplex_Slave:
			SPI.SPI -> CR1 &= ~SPI_CR1_BIDIMODE;
			break;
		case SPI_Half_Duplex_Slave_TX:
			SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE;
			SPI.SPI -> CR1 |= SPI_CR1_BIDIOE;
			break;
		case SPI_Half_Duplex_Slave_RX:
			SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE;
			SPI.SPI -> CR1 &= ~SPI_CR1_BIDIOE;
			break;
		default:
			break;
	 }
	}

	SPI.SPI -> CR1 |= SPI_CR1_SPE;

	GPIO_Pin_Setup(SPI.nCSS_Port, SPI.nCSS_pin, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);

}


void SPI_CSS_Low(SPI_Config SPI)
{
	GPIO_Pin_Low(SPI.nCSS_Port, SPI.nCSS_pin);
}


void SPI_CSS_High(SPI_Config SPI)
{
	GPIO_Pin_High(SPI.nCSS_Port, SPI.nCSS_pin);
}


void SPI_Send_Data(SPI_Config SPI, int data)
{

	while(!(SPI.SPI->SR & SPI_SR_TXE));
	SPI.SPI -> DR = data;
	while(!(SPI.SPI->SR & SPI_SR_TXE));
//	while(!(SPI.SPI->SR & SPI_SR_TXE));
	while((SPI.SPI->SR & SPI_SR_BSY));
}

int SPI_Receive_Data(SPI_Config SPI)
{
	int data1,data2 = 0;
	int temp = 0;
	if(SPI.Frame == SPI_Frame_8Bit)
	{
		SPI_Send_Data(SPI, 0xA5); //Send dummy byte
		while((SPI.SPI->SR & SPI_SR_BSY));
// 		while((SPI.SPI -> SR & SPI_SR_RXNE))
		temp = (SPI.SPI -> DR);
	}
	if(SPI.Frame == SPI_Frame_16Bit)
	{
		SPI_Send_Data(SPI, 0xAAAA); //Send dummy byte
		while((SPI.SPI->SR & SPI_SR_BSY));
//		while((SPI.SPI -> SR & SPI_SR_RXNE))
		temp = SPI.SPI -> DR;
	}

return temp;
}
