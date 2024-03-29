/*
 * GPIO.c
 *
 *  Created on: 10-Sep-2021
 *      Author: Kunal
 */


#include "GPIO.h"


void GPIO_Pin_Setup(char Port, uint8_t pin, uint8_t function, uint8_t alternate_function)
{
	if(Port == 'A' || Port == 'a')
	{
		RCC -> AHB1ENR   |= RCC_AHB1ENR_GPIOAEN;

		GPIOA -> MODER   |= ((0xC0  & function)>>6) << (2 * pin);
		GPIOA -> OTYPER  |= ((0x30  & function)>>4) << (1 * pin);
		GPIOA -> OSPEEDR |= ((0x0C  & function)>>2) << (2 * pin);
		GPIOA -> PUPDR   |= ((0x03  & function)>>0) << (2 * pin);

		if(pin < 8)GPIOA -> AFR[0] |= ( alternate_function << (4 * (pin)));
		else	   GPIOA -> AFR[1] |= ( alternate_function << (4 * (pin - 8)));
	}
	if(Port == 'B' || Port == 'b')
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		GPIOB -> MODER   |= ((0xC0  & function)>>6) << (2 * pin);
		GPIOB -> OTYPER  |= ((0x30  & function)>>4) << (1 * pin);
		GPIOB -> OSPEEDR |= ((0x0C  & function)>>2) << (2 * pin);
		GPIOB -> PUPDR   |= ((0x03  & function)>>0) << (2 * pin);

		if(pin < 8)GPIOB -> AFR[0] |= ( alternate_function << (4 * (pin)));
		else	   GPIOB -> AFR[1] |= ( alternate_function << (4 * (pin - 8)));
	}
	if(Port == 'C' || Port == 'c')
	{
		RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
		GPIOC -> MODER   |= ((0xC0  & function)>>6) << (2 * pin);
		GPIOC -> OTYPER  |= ((0x30  & function)>>4) << (1 * pin);
		GPIOC -> OSPEEDR |= ((0x0C  & function)>>2) << (2 * pin);
		GPIOC -> PUPDR   |= ((0x03  & function)>>0) << (2 * pin);
		if(pin < 8)GPIOC -> AFR[0] |= ( alternate_function << (4 * (pin)));
		else	   GPIOC -> AFR[1] |= ( alternate_function << (4 * (pin - 8)));

		if (alternate_function == NONE) {}

	}
}


void GPIO_Interrupt_Setup(int pin, int edge_select)
{
	EXTI ->IMR |= 1 << pin;
	switch (edge_select) {
		case 0:
			EXTI ->RTSR |= 1 << pin;
			break;
		case 1:
			EXTI ->FTSR |= 1 << pin;
			break;
		case 2:
			EXTI ->RTSR |= 1 << pin;
			EXTI ->FTSR |= 1 << pin;
			break;
	}

	NVIC_SetPriority(EXTI0_IRQn,0);
	NVIC_EnableIRQ(EXTI0_IRQn);
}
