/*
 * GPIO.c
 *
 *  Created on: 21-Mar-2021
 *      Author: Kunal
 */


#include "GPIO.h"



void GPIO_Pin_Setup(GPIO_TypeDef *GPIO, int pin, int mode)
{
	if(GPIO == GPIOA)RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	if(GPIO == GPIOB)RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	if(GPIO == GPIOC)RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	GPIO->MODER   |= ((mode & 0b11000000) >> 6) << (2 * pin);
	GPIO->OTYPER  |= ((mode & 0b00100000) >> 5) << pin;
	GPIO->OSPEEDR |= ((mode & 0b00011000) >> 3) << (2 * pin);
	GPIO->PUPDR   |= ((mode & 0b00000110) >> 1) << (2 * pin);

}


void GPIO_Pin_Interrupt_Setup(GPIO_TypeDef *port, int pin, int type)
{}


void GPIO_Interrupt_Enable(int pin, int priority, IRQn_Type irqnum)
{}
