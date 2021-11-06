#define ARM_MATH_CM4

#include "main.h"
#include "I2S/I2S.h"
#include "arm_math.h"

int16_t data[16384];
int16_t ldata[8192];
int callback;

uint8_t outarray[11];
float in_fft[8192], out_fft[8192];

arm_rfft_fast_instance_f32 fft_handler;

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



int main(void)
{
	MCU_Clock_Setup();
	I2S_Clock_Init();
	Delay_Config();
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	GPIO_Pin_Setup('A', 9, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART1_TX);
	GPIO_Pin_Setup('A', 10, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, USART1_RX);
	USART1 -> CR1 |= USART_CR1_UE;
	USART1 -> BRR = (int)(SystemCoreClock / (16 * 115200)) << 4;
	USART1 -> CR1 |= USART_CR1_TE ;
	USART1 -> CR1 |=  USART_CR1_RE;
	USART1 -> CR3 |= USART_CR3_DMAT;


	GPIO_Pin_Setup('A', 2, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
	GPIO_Pin_Setup('A', 3, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);

I2S_Config z;
z.I2S = I2S1;
z.audio_frequency = 48000;
z.channel_length = Channel_16bit;
z.frame_length = Frame_16bit;
z.mode = I2S_Master_RX;
z.standard = Philips_Standard;
I2S_Master_Init(z);

NVIC_SetPriority(DMA2_Stream2_IRQn,0);
NVIC_EnableIRQ(DMA2_Stream2_IRQn);

//NVIC_SetPriority(USART1_IRQn,1);
//NVIC_EnableIRQ(USART1);

SPI1 -> CR1 |= SPI_CR1_SPE;
RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
DMA2_Stream2 -> CR |= ( 3 << 25 ) | (1 << 10) | (1 << 13) | (1 << 11) | (1 << 8) | (0 << 6) | (1 << 4) | (1 << 3) |
		 (1 << 2) |  (1 << 1) ;
DMA2_Stream2 -> NDTR = 16384;
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


float complexABS(float real, float compl)
{
	return sqrtf(real*real+compl*compl);
}


void DoFFT()
{
	arm_rfft_fast_f32(&fft_handler,&in_fft,&out_fft,0);

	int freq_bins[8192];
	int freqpoint = 0;
	int offset = 150;

	for(int i = 0; i < 2048; i = i+2)
	{
		freq_bins[freqpoint] = (int)(20*log10f(complexABS(in_fft[i], out_fft[i+1])))-offset;
		if(freq_bins[freqpoint] < 0)
		{
			freq_bins[freqpoint] = 0;
		}
		freqpoint++;
	}


	outarray[0] = 0xff;
	outarray[1] = (uint8_t)freq_bins[1];
	outarray[2] = (uint8_t)freq_bins[3];
	outarray[3] = (uint8_t)freq_bins[5];
	outarray[4] = (uint8_t)freq_bins[11];
	outarray[5] = (uint8_t)freq_bins[22];
	outarray[6] = (uint8_t)freq_bins[44];
	outarray[7] = (uint8_t)freq_bins[96];
	outarray[8] = (uint8_t)freq_bins[197];
	outarray[9] = (uint8_t)freq_bins[393];
	outarray[10] = (uint8_t)freq_bins[655];
//	outarray[11] = '\r';
//	outarray[11] = '\n';

	for(int i = 0; i < 11; i++)
	{
		printConsole(USART1, "%d"PRId16,"",outarray[i]);
	}

}



