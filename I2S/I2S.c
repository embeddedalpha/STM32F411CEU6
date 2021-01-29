#include "I2S.h"



void I2S_Init(SPI_TypeDef *I2S, uint8_t mode, uint8_t standard, uint8_t data_length, uint8_t channel_length)
{
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SMOD |
									 SPI_I2SCFGR_I2SE; //Enable I2S
		
	switch(mode){
		case 1:
		{
		I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SCFG;
			break;
		}
		
		case 2:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SCFG_0;
		I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SCFG_1 ;
			break;
		}	

		case 3:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SCFG_1;
		I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SCFG_0 ;
			break;
		}

		case 4:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SCFG_0;
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SCFG_1 ;
			break;
		}		
		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch(standard){
		case 1:
		{
		I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SSTD;
			break;
		}
		
		case 2:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SSTD_0;
		I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SSTD_1 ;
			break;
		}	

		case 3:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SSTD_1;
		I2S->I2SCFGR &= ~SPI_I2SCFGR_I2SSTD_0 ;
			break;
		}

		case 4:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SSTD_0;
		I2S->I2SCFGR |= SPI_I2SCFGR_I2SSTD_1 ;
			break;
		}		
			
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch(data_length){
		case 1:
		{
		I2S->I2SCFGR &= ~SPI_I2SCFGR_DATLEN;
			break;
		}
		
		case 2:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_DATLEN_0;
		I2S->I2SCFGR &= ~SPI_I2SCFGR_DATLEN_1 ;
			break;
		}	

		case 3:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_DATLEN_1;
		I2S->I2SCFGR &= ~SPI_I2SCFGR_DATLEN_0 ;
			break;
		}
	
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

switch(channel_length){
		case 0:
		{
		I2S->I2SCFGR &= ~SPI_I2SCFGR_CHLEN;
			break;
		}
		
		case 1:
		{
		I2S->I2SCFGR |= SPI_I2SCFGR_CHLEN;
			break;
		}	
		
	}

}
