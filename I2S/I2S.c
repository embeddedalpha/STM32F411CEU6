/*
 * I2S.c
 *
 *  Created on: 28-Jun-2021
 *      Author: Kunal
 */


#include "I2S.h"


void I2S_Mater_Init(SPI_TypeDef *I2S, bool tx_or_rx)
{
	I2S->I2SCFGR |= SPI_I2SCFGR_I2SMOD; //Enable i2s mode
	if (tx_or_rx)
		{
			I2S->I2SCFGR |= SPI_I2SCFGR_I2SCFG_1 ; //i2s configured as master receive
		}
	else
		{
			I2S->I2SCFGR |= SPI_I2SCFGR_I2SCFG_1 | SPI_I2SCFGR_I2SCFG_0; //i2s configured as master receive
		}

	I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SSTD; //phillips standard
	I2S->I2SCFGR |= SPI_I2SCFGR_DATLEN_1; //24 bit data
	I2S->I2SCFGR |= SPI_I2SCFGR_CHLEN; //32 bit per channel
	I2S->I2SCFGR &= ~SPI_I2SCFGR_CKPOL;
	I2S->I2SPR |= SPI_I2SPR_ODD | 12;
	I2S->I2SCFGR |= SPI_I2SCFGR_I2SE; //Enable i2s peripheral
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
