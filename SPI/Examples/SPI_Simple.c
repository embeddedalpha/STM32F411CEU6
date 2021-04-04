#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "SPI/SPI.h"
#include "GPIO/GPIO.h"



int main(void)
{


SPI1_Pin_Setup();
struct SPI_Config X;
X.SPI = SPI1;
X.clock_phase = 1;
X.clock_polarity = 1;
X.clock_speed = 0;
X.frame_format = 0;
X.lsb_or_msb = 1;

SPI_Master_Init(X);

	for(;;)
	{
		SPI1_CSS_HIGH();
		SPI_Master_TX(X, 0x0A);
		SPI1_CSS_LOW();
	}
}
