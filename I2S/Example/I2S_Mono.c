#include "main.h"
#include "I2S/I2S.h"


int main()
{

  //Variable Declaration
  int16_t x;
  I2S_Config INMP441;
  
  
	MCU_Clock_Setup();
	INMP441.I2S = SPI1;
	INMP441.audio_frequency = 48000;
	INMP441.channel_length = Channel_16bit;
	INMP441.data_length = Frame_16bit;
	INMP441.standard = Philips_Standard;
	INMP441.mode = I2S_Master_RX;
	I2S_Master_Init(INMP441);
  
  

  while(1)
    {
       x = I2S_Master_Receive_Left_Channel(INMP441); 
    }
  
  
}
