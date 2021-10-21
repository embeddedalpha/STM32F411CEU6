/*
 * WS2812B.c
 *
 *  Created on: 21-Oct-2021
 *      Author: Kunal
 */


#include "WS2812B.h"



void WS2812B_Init(SPI_TypeDef *SPI)
{
	WS2812BSPI = SPI;
	WS2812Bphase = 1;
	WS2812Bpolarity = 1;
	WS2812BFrame = SPI_Frame_8Bit;
	WS2812BLSB_MSB = 0;
	WS2812BDMA_TWS2812B = 0;
	WS2812BDMA_RWS2812B = 0;
	WS2812Bfrequency = 2;
	WS2812Bmode = SPI_Master;
	WS2812Btype = SPI_Full_DupleWS2812B_Master;
	SPI_Init(WS2812B);
	SPI_CSS_Init(WS2812B);
}


void WS2812B_Set_Color(int led_no, int red, int green, int blue)
{
	uint32_t color  = green << 16 | red << 8 | blue;
	led_color[len_no][color];

}


void WS2812B_Send_Data(uint32_t *led_color)
{
	int length = sizeof(led_color)/sizeof(led_color[0]);
	for(int i = 0; i< length; i++)
	{
		for(int j = 24; j >= 0; j--)
		{
			if(led_color[i][j] & (1 << j))
			{
				SPI_Send_Data(WS2812B, active_high);
			}
			else{
				SPI_Send_Data(WS2812B, active_low);
			}
		}
	}
}



void WS2812B_Clear_Strip(void)
{
	uint32_t color = 0x000000;
	for(int i = 0; i< MAX_LEDS; i++)
	{
		for(int j = 24; j >= 0; j--)
		{
				SPI_Send_Data(WS2812B, active_low);
		}
	}
}


