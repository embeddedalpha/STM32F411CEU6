#include "main.h"
#include "I2S/I2S.h"
#include "USART/USART.h"
#include "Console/Console.h"

int16_t data[2048];
int16_t ldata[1024];
int callback;

void D()
{
	for(int i = 0; i < 1000; i++)
	{

	}
}

void DMA2_Stream2_IRQHandler(void)
{
	if((DMA2 ->LISR & DMA_LISR_TCIF2) == DMA_LISR_TCIF2)
	{
		GPIOA -> BSRR |= GPIO_BSRR_BS2;
		DMA2 -> LIFCR |= DMA_LIFCR_CTCIF2;
        callback = 2;

	}
	if((DMA2 ->LISR & DMA_LISR_HTIF2) == DMA_LISR_HTIF2)
	{
		GPIOA -> BSRR |= GPIO_BSRR_BR2;
		DMA2 -> LIFCR |= DMA_LIFCR_CHTIF2;
		callback = 1;
	}
//	GPIOA -> BSRR |= GPIO_BSRR_BR2;
}

//void DMA2_Stream0_IRQHandler(void)
//{
////	if((DMA2 ->LISR & DMA_HISR_TCIF4) == DMA_HISR_TCIF4)
////	{
////		GPIOA -> BSRR |= GPIO_BSRR_BR2;
////		DMA2 -> LIFCR |= DMA_HIFCR_CTCIF4;
////	}
//	GPIOA -> BSRR |= GPIO_BSRR_BR2;
//}


int main(void)
{
	MCU_Clock_Setup();
	I2S_Clock_Init();
	Delay_Config();
	Console_Init(USART1, 115200);

	GPIO_Pin_Setup('A', 2, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
	GPIO_Pin_Setup('A', 3, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);

I2S_Config z;
z.I2S = I2S1;
z.audio_frequency = 48000;
z.channel_length = Channel_16bit;
z.data_length = Frame_16bit;
z.mode = I2S_Master_RX;
z.standard = Philips_Standard;

I2S_Master_Init(z);

NVIC_SetPriority(DMA2_Stream2_IRQn,0);
NVIC_EnableIRQ(DMA2_Stream2_IRQn);

SPI1 -> CR1 |= SPI_CR1_SPE;
RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
DMA2_Stream2 -> CR |= ( 3 << 25 ) | (1 << 10) | (1 << 13) | (1 << 11) | (1 << 8) | (0 << 6) | (1 << 4) | (1 << 3) |
		 (1 << 2) |  (1 << 1) ;
DMA2_Stream2 -> NDTR = 2048;
DMA2_Stream2 -> M0AR = (uint32_t)&data;
DMA2_Stream2 -> PAR = (uint32_t)&(SPI1->DR);
DMA2_Stream2 -> CR |= 1 << 0;


	while(1)
	{

		if(callback == 1)
		{
			int i;
			for( i = 0; i < 512; i++)
			{
				ldata[i] = data[2*i];
			}
		}
		if(callback == 2)
		{
			int i;
			for( i = 512; i < 1024; i++)
			{
				ldata[i] = data[2*i];
			}
		}

		for(int i =0;i < 1024; i++)
		{
			printConsole(USART1, "%"PRId16"\r\n",ldata[i]);
		}

	}
}


