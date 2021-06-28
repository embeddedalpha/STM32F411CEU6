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
	I2S->I2SCFGR |= SPI_I2SCFGR_CKPOL;
	I2S->I2SPR |= SPI_I2SPR_ODD | 12;
	I2S->I2SCFGR |= SPI_I2SCFGR_I2SE; //Enable i2s peripheral
}


