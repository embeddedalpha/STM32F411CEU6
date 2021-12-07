#define ARM_MATH_CM4

#include "main.h"
#include "GPIO/GPIO.h"
#include "arm_math.h"


	uint8_t OUT_ARRAY[3000];
	int16_t MIC_DATA_IN[8192];
	int16_t MIC_DATA_LEFT[4098];
	float32_t in_fft[4098], out_fft[4098];

	arm_rfft_fast_instance_f32 fft_handler;

int main()
{


	MCU_Clock_Setup();
	I2S_Clock_Init();
	Delay_Config();

//  USART1 Initialization:
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	GPIO_Pin_Setup(GPIOA, 9, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, USART1_TX);
	GPIO_Pin_Setup(GPIOA, 10, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN, USART1_RX);
	USART1 -> CR1 |= USART_CR1_UE;
	USART1 -> BRR = (int)(SystemCoreClock / (16 * 115200)) << 4;
	USART1 -> CR1 |= USART_CR1_TE ;
	USART1 -> CR1 |=  USART_CR1_RE;
	USART1 -> CR3 |= USART_CR3_DMAT;

//	USART1 DMA Initialization:
	DMA2_Stream2 -> CR |= 7 << 25 	//CHANNEL 3
			           |  2 << 16	//HIGH PRIORITY
					   |  1 << 13	//16 BIT MEMORY SIZE
					   |  0 << 11	//16 BIT PERIPHERAL SIZE
					   |  0 << 10	//MEMORY INCREMENT MODE
					   |  1 << 8	//CIRCULAR MODE
					   |  0 << 6    //PERIPHERAL TO MEMORY
					   |  1 << 4	//TRANSFER COMPLETE INTERRUPT ENABLE
					   |  1 << 3;	//HALF TRANSFER INTERRUPT ENABLE

	DMA2_Stream2 -> NDTR = 10;
	DMA2_Stream2 -> M0AR =  (uint32_t)&(OUT_ARRAY[0]);
	DMA2_Stream2 -> PAR = (uint32_t)&(USART1->DR);

//   I2S Initialization:
	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
	GPIO_Pin_Setup(GPIOA, 4, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S1_WS);
	GPIO_Pin_Setup(GPIOA, 5, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S1_CK);
	GPIO_Pin_Setup(GPIOA, 7, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, I2S1_SD);
	SPI1 -> I2SCFGR |= SPI_I2SCFGR_I2SMOD
			        | 3 << 8
					| 0 << 4
					| 0 << 1
					| 0 << 0;
	SPI1 -> I2SPR = 56;
	SPI1 -> I2SPR |= 1 << 8;
	SPI1 -> CR2 |= SPI_CR2_RXDMAEN;
	SPI1 -> I2SCFGR |= SPI_I2SCFGR_I2SE;

//	I2S DMA Initialization:
	DMA2_Stream2 -> CR |= 3 << 25 	//CHANNEL 3
				       |  2 << 16	//HIGH PRIORITY
					   |  1 << 13	//16 BIT MEMORY SIZE
					   |  1 << 11	//16 BIT PERIPHERAL SIZE
					   |  1 << 10	//MEMORY INCREMENT MODE
					   |  1 << 8	//CIRCULAR MODE
					   |  1 << 6    //PERIPHERAL TO MEMORY
					   |  1 << 4	//TRANSFER COMPLETE INTERRUPT ENABLE
					   |  1 << 3;	//HALF TRANSFER INTERRUPT ENABLE

	DMA2_Stream2 -> NDTR = 10;
	DMA2_Stream2 -> PAR =  (uint32_t)&(SPI1->DR);
	DMA2_Stream2 -> M0AR = (uint32_t)&(MIC_DATA_IN[0]);


	while(1)
	{


	}

}


void USART1_DMA_Enable()
{
	DMA2_Stream2 -> CR |= 1 << 0;
}

void I2S1_DMA_Enable()
{
	DMA2_Stream2 -> CR |= 1 << 0;
}
//
//float complexABS(float real, float compl)
//{
//	return sqrtf(real*real+compl*compl);
//}
//
//void DoFFT()
//{
//	arm_rfft_fast_f32(&fft_handler,&in_fft,&out_fft,0);
//
//	int freq_bins[8192];
//	int freqpoint = 0;
//	int offset = 150;
//
//	for(int i = 0; i < 2048; i = i+2)
//	{
//		freq_bins[freqpoint] = (int)(20*log10f(complexABS(in_fft[i], out_fft[i+1])))-offset;
//		if(freq_bins[freqpoint] < 0)
//		{
//			freq_bins[freqpoint] = 0;
//		}
//		freqpoint++;
//	}
//
//
//	OUT_ARRAY[0] = 0xff;
//	OUT_ARRAY[1] = (uint8_t)freq_bins[1];
//	OUT_ARRAY[2] = (uint8_t)freq_bins[3];
//	OUT_ARRAY[3] = (uint8_t)freq_bins[5];
//	OUT_ARRAY[4] = (uint8_t)freq_bins[11];
//	OUT_ARRAY[5] = (uint8_t)freq_bins[22];
//	OUT_ARRAY[6] = (uint8_t)freq_bins[44];
//	OUT_ARRAY[7] = (uint8_t)freq_bins[96];
//	OUT_ARRAY[8] = (uint8_t)freq_bins[197];
//	OUT_ARRAY[9] = (uint8_t)freq_bins[393];
//	OUT_ARRAY[10] = (uint8_t)freq_bins[655];
////	OUT_ARRAY[11] = '\r';
////	OUT_ARRAY[11] = '\n';
//
//	for(int i = 0; i < 11; i++)
//	{
////		printConsole(USART1, "%d"PRId16,"",OUT_ARRAY[i]);
//	}
//
//}
//
