/*
 * SPI.c
 *
 *  Created on: 18-Jul-2021
 *  Updated on: 03-Oct-2021
 *      Author: Kunal
 */

#include "SPI.h"

void SPI_Init(SPI_Config SPI)
{
	if (SPI.SPI == SPI1)   //CK -> PA5 	//MISO -> PA6 	//MOSI -> PA7
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
		GPIO_Pin_Setup('A', 5, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, SPI1_CLK);
		GPIO_Pin_Setup('A', 6, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, SPI1_MISO);
		GPIO_Pin_Setup('A', 7, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, SPI1_MOSI);

	}
	if(SPI.SPI == SPI2)	//CK -> PB10 	//MISO -> PB14 	//MOSI -> PB15
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;
        GPIO_Pin_Setup('B', 10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('B', 14, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('B', 15, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}
	if(SPI.SPI == SPI3)	//CK -> PB12 	//MISO -> PB4 	//MOSI -> PB5
	{
		RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
		GPIO_Pin_Setup('B', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('B', 4, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('B', 5, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}
	if(SPI.SPI == SPI4)	//CK -> PB13 	//MISO -> PA11 	//MOSI -> PA1
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI4EN;
		GPIO_Pin_Setup('B', 13, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('B', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('A', 1, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}
	if(SPI.SPI == SPI5)	//CK -> PB0 	//MISO -> PA12 	//MOSI -> PB8
	{
		RCC -> APB2ENR |= RCC_APB2ENR_SPI5EN;
		GPIO_Pin_Setup('B', 0, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('B', 8, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
		GPIO_Pin_Setup('A', 12, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, 5);
	}



	SPI.SPI -> CR1 |= (
					  SPI.Frame << 11 |
					  SPI.LSB_MSB << 7 |
					  SPI.polarity << 1 |
					  SPI.CRC_Enable << 13 |
					  SPI.phase << 0
					  );

	SPI.SPI -> CR1 &= ~SPI_CR1_SSM;

	SPI.SPI -> CR2 |= SPI.DMA_TX << 1 | SPI.DMA_RX << 0 | SPI_CR2_SSOE ;

	if(SPI.mode == SPI_Master)
	{
		SPI.SPI -> CR1 |= SPI_CR1_MSTR;
		switch (SPI.type)
		{
			case Full_Duplex_Master:
				SPI.SPI -> CR1 &= ~SPI_CR1_BIDIMODE;
				break;
			case Half_Duplex_Master_TX:
				SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE;
				SPI.SPI -> CR1 |= SPI_CR1_BIDIOE;
				break;
			case Half_Duplex_Master_RX:
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
		case Full_Duplex_Slave:
			SPI.SPI -> CR1 &= ~SPI_CR1_BIDIMODE;
			break;
		case Half_Duplex_Slave_TX:
			SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE;
			SPI.SPI -> CR1 |= SPI_CR1_BIDIOE;
			break;
		case Half_Duplex_Slave_RX:
			SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE;
			SPI.SPI -> CR1 &= ~SPI_CR1_BIDIOE;
			break;
		default:
			break;
	 }
	}

	SPI.SPI -> CR1 |= SPI_CR1_SPE;
}


void SPI_CSS_Init(SPI_Config SPI)
{
	if (SPI.SPI == SPI1) GPIO_Pin_Setup('A', 4, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
	if (SPI.SPI == SPI2) GPIO_Pin_Setup('B', 1, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
	if (SPI.SPI == SPI3) GPIO_Pin_Setup('B', 2, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
	if (SPI.SPI == SPI4) GPIO_Pin_Setup('A', 15, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
	if (SPI.SPI == SPI5) GPIO_Pin_Setup('B', 3, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
}

void SPI_CSS_High(SPI_Config SPI)
{
	if (SPI.SPI == SPI1) GPIOA -> BSRR |= GPIO_BSRR_BS4;
	if (SPI.SPI == SPI2) GPIOB -> BSRR |= GPIO_BSRR_BS1;
	if (SPI.SPI == SPI3) GPIOB -> BSRR |= GPIO_BSRR_BS2;
	if (SPI.SPI == SPI4) GPIOA -> BSRR |= GPIO_BSRR_BS15;
	if (SPI.SPI == SPI5) GPIOB -> BSRR |= GPIO_BSRR_BS3;
}

void SPI_CSS_Low(SPI_Config SPI)
{
	if (SPI.SPI == SPI1) GPIOA -> BSRR |= GPIO_BSRR_BR4;
	if (SPI.SPI == SPI2) GPIOB -> BSRR |= GPIO_BSRR_BR1;
	if (SPI.SPI == SPI3) GPIOB -> BSRR |= GPIO_BSRR_BR2;
	if (SPI.SPI == SPI4) GPIOA -> BSRR |= GPIO_BSRR_BR15;
	if (SPI.SPI == SPI5) GPIOB -> BSRR |= GPIO_BSRR_BR3;
}


void SPI_Send_Data(SPI_Config SPI,int16_t data)
{

	while(!(SPI.SPI->SR & SPI_SR_TXE));
	SPI.SPI -> DR = data;
	while(!(SPI.SPI->SR & SPI_SR_TXE));
	while((SPI.SPI->SR & SPI_SR_BSY));
}

int16_t SPI_Receive_Data(SPI_Config SPI)
{
	uint16_t data;
	uint8_t  data1,data2;
	if(SPI.Frame == SPI_Frame_8Bit)
	{
		SPI_Send_Data(SPI, 0xAA); //Send dummy byte
		while((SPI.SPI->SR & SPI_SR_BSY));
		while((SPI.SPI -> SR & SPI_SR_RXNE))
		data = SPI.SPI -> DR;
	}
	if(SPI.Frame == SPI_Frame_16Bit)
	{
		SPI_Send_Data(SPI, 0xAA); //Send dummy byte
		while((SPI.SPI->SR & SPI_SR_BSY));
		while((SPI.SPI -> SR & SPI_SR_RXNE))
		data1 = SPI.SPI -> DR;
		SPI_Send_Data(SPI, 0xAA); //Send dummy byte
		while((SPI.SPI->SR & SPI_SR_BSY));
		while((SPI.SPI -> SR & SPI_SR_RXNE))
		data2 = SPI.SPI -> DR;
		data = data1 << 8 | data2;
	}
	return data;

}
