#include "main.h"
#include "GPIO/GPIO.h"


void EXTI0_IRQHandler(void)
{
	printConsole("IN \r\n");
	printConsole("Button was pressed \r\n");
	EXTI ->PR |= 1 << 0;
	printConsole("OUT \r\n");
}

int main()
{

	MCU_Clock_Setup();
	Console_Init(9600);
	Delay_Config();
  
	GPIO_Pin_Setup('a', 0, INPUT_PULLDW, NONE);
	EXTI ->IMR |= 1 << 0;
	EXTI ->RTSR |= 1 << 0;
	NVIC_SetPriority(EXTI0_IRQn,0);
	NVIC_EnableIRQ(EXTI0_IRQn);
  
	while(1)
	{

	}
}






