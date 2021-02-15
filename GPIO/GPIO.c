#include "GPIO.h"



void GPIO_Init(GPIO_TypeDef *GPIO,uint8_t pin, uint8_t config)
{
	if(GPIO == GPIOA)
	{
		  RCC->APB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}
		else if(GPIO == GPIOB)
		{
			RCC->APB1ENR |= RCC_AHB1ENR_GPIOBEN;
		}
			else if(GPIO == GPIOC)
			{
				RCC->APB1ENR |= RCC_AHB1ENR_GPIOCEN;
			}
			
			GPIO->MODER |= (uint8_t)(((0x60 & config) >> 5) << (pin * 2));
			GPIO->OTYPER |= (uint8_t)(((0x10 & config) >> 4) << (pin * 1));
			GPIO->OSPEEDR |= (uint8_t)(((0x0C & config) >> 2) << (pin * 2));
			GPIO->PUPDR |= (uint8_t)((0x03 & config)  << (pin * 2));

}


