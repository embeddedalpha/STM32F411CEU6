#include "US100_Serial.h"



void US100_Init(Serial US)
{
  US1.port = USART1;
  US1.baudrate = 9600;
  US1.mode = Full_Duplex;
  US1.hardware_control = 0;
  UART_Init(US1);
}



int US_Get_Temp(Serial US)
{
	int y;
	US.port -> DR = 80;
	while((US.port -> SR & (1 << 6)) == 0x80){}
	while(US.port -> SR & 0x20){}
	y = US.port -> DR;

	return y;
}

float US_Get_Distance(Serial US)
{
	float x;
	int a,b;
	US.port -> DR = 80;
	while((US.port -> SR & (1 << 6)) == 0x80){}
	while(US.port -> SR & 0x20){}
	a = US.port -> DR; //Higher byte
	b = US.port -> DR; //Lower byte
	x = (float)(a * 256 + b); //Calculate distance
	return x;
}
