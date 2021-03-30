/*
 * SPI.c
 *
 *  Created on: 20-Mar-2021
 *      Author: Kunal
 */


#include "SPI.h"



void SPI_Master_Init(SPI_Config SPI)
{
	if(SPI.SPI == SPI1)
	{
		SPI1_Pin_Setup();
	}
	if(SPI.SPI == SPI2)
	{
		SPI2_Pin_Setup();
	}
	if(SPI.SPI == SPI3)
	{
		SPI3_Pin_Setup();
	}
	if(SPI.SPI == SPI4)
	{
		SPI4_Pin_Setup();
	}
	if(SPI.SPI == SPI5)
	{
		SPI5_Pin_Setup();
	}

	SPI.SPI -> CR1 |=
			(
			SPI.crc << 13 |
			SPI.frame_format << 11 |
			SPI.lsb_or_msb << 7 |
			SPI.clock_speed << 3 |
			SPI.clock_polarity << 1 |
			SPI.clock_phase << 0
			);

	SPI.SPI -> CR2 |=
			(
			SPI.txDMA << 1 |
			SPI.rxDMA << 0
			);
	if(SPI.interrupts)
	{
		SPI.SPI -> CR2 |=
				(
				SPI.err_int << 5 |
				SPI.tx_int << 7 |
				SPI.rx_int << 6
				);
	}
	if(SPI.mode)
	{
		SPI.SPI -> CR1 |= SPI_CR1_BIDIMODE | (SPI.onlyTXorRX << 14);
	}
	else
	{
		SPI.SPI -> CR1 &= ~SPI_CR1_BIDIMODE;
	}

	SPI.SPI -> CR1 |= SPI_CR1_MSTR | SPI_CR1_SPE;

}

///////////////////////////////////////////////////////////////////////////////////////


void SPI_Master_TX(SPI_Config SPI, uint16_t data)
{
	SPI.SPI->DR = data;
	while(!(SPI.SPI -> SR & SPI_SR_TXE));
}

///////////////////////////////////////////////////////////////////////////////////////


uint16_t SPI_Master_RX(SPI_Config SPI)
{
	SPI_Master_TX(SPI,0x00);
	while(!(SPI.SPI -> SR & SPI_SR_RXNE));
	return SPI.SPI -> DR;
}


//////////////////////////////////////////////////////////////////////////////////////

void SPI1_CSS_HIGH(void)
{
	GPIOA -> BSRR |= GPIO_BSRR_BS4;
}

void SPI1_CSS_LOW(void)
{
	GPIOA -> BRR |= GPIO_BRR_BR4;
}

/////////////////////////////////////////////////////////////////////////////////////


void SPI2_CSS_HIGH(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS12;
}

void SPI2_CSS_LOW(void)
{
	GPIOB -> BRR |= GPIO_BRR_BR12;
}

/////////////////////////////////////////////////////////////////////////////////////

void SPI3_CSS_HIGH(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS4;
}

void SPI3_CSS_LOW(void)
{
	GPIOB -> BRR |= GPIO_BRR_BR4;
}

/////////////////////////////////////////////////////////////////////////////////////

void SPI4_CSS_HIGH(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS12;
}

void SPI4_CSS_LOW(void)
{
	GPIOB -> BRR |= GPIO_BRR_BR12;
}

/////////////////////////////////////////////////////////////////////////////////////

void SPI5_CSS_HIGH(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS1;
}

void SPI5_CSS_LOW(void)
{
	GPIOB -> BRR |= GPIO_BRR_BR1;
}

/////////////////////////////////////////////////////////////////////////////////////



void SPI_Disable(SPI_Config SPI)
{

while(SPI.SPI -> SR & SPI_SR_RXNE);
while(SPI.SPI -> SR & SPI_SR_TXE);
while(~(SPI.SPI -> SR & SPI_SR_BSY));
SPI.SPI -> CR1 &= ~SPI_CR1_SPE;

}


/*
void SPI1_IRQHandler(void)
{
	if(SPI1->SR & SPI_SR_TXE)
	{
		//Your code goes here
	}
	if(SPI1->SR & SPI_SR_RXNE)
	{
		//Your code goes here
	}
	if(SPI1->SR & SPI_SR_OVR)
	{
		//Your code goes here
	}
	if(SPI1->SR & SPI_SR_MODF)
	{
		//Your code goes here
	}
	if(SPI1->SR & SPI_SR_CRCERR)
	{
		//Your code goes here
	}
	if(SPI1->SR & SPI_SR_UDR)
	{
		//Your code goes here
	}
*/
