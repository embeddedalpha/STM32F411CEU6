#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "SPI/SPI.h"
#include "GPIO/GPIO.h"

void SPI1_IRQHandler(void)
{
	if(SPI1->SR & SPI_SR_TXE)
	{
		SPI1 -> DR = 0x0A;
	}
	if(SPI1->SR & SPI_SR_RXNE)
	{
		a = SPI1 -> DR;
	}
}

int a;

int main(void)
{
	uint8_t c;

SPI1_Pin_Setup();
struct SPI_Config X;
X.SPI = SPI1;
X.clock_phase = 1;
X.clock_polarity = 1;
X.clock_speed = 0;
X.frame_format = 0;
X.lsb_or_msb = 1;
X.interrupts = 1;
X.rx_int = 1;
X.tx_int = 1;


SPI_Master_Init(X);
NVIC_EnableIRQ(SPI1_IRQn);

	for(;;)
	{

	}
}

