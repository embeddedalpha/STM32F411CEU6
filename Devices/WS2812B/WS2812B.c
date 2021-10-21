#include "WS2812B.h"


void WS2811_Init()
{
   X.SPI = SPI1;
   X.phase = 1;
   X.polarity = 1;
   X.Frame = SPI_Frame_8Bit;
   X.LSB_MSB = 0;
   X.DMA_TX = 0;
   X.DMA_RX = 0;
   X.frequency = 2;
   X.mode = SPI_Master;
   X.type = SPI_Full_Duplex_Master;
   SPI_Init(X);
   SPI_CSS_Init(X);
}


void WS2811_Send(int led_no, int red, int blue, int green)
{
	uint32_t color = green << 16 | red << 8 | blue;
	SPI_CSS_Low(X);
	for(int i = 24; i >= 0; i--)
	{
		if(color & (1 << i))
		{
			SPI_Send_Data(X, active_high);
		}
		else{
			SPI_Send_Data(X, active_low);
		}
	}
	SPI_CSS_High(X);
//	Delay_us(50);
}

