/*
 * GPIO.c
 *
 *  Created on: 21-Mar-2021
 *      Author: Kunal
 */


#include "GPIO.h"
/*

I2C	1 2 3
SPI	1 2 3 4 5
I2S 1 2 3 4 5
SDIO 1
USART 1 2 6
USB
*/





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

///////////////////////////////////////////////////////////////////////////////////////


void I2C1_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOB, 6, ALT_OPEN_DRAIN_OUT_PULL_UP); //PB6	SCL
	GPIO_Pin_Setup(GPIOB, 7, ALT_OPEN_DRAIN_OUT_PULL_UP); //PB6	SDA
	GPIOB -> AFR[0] |= (4 << 28) | (4 << 24);
}

void I2C2_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOB, 10, ALT_OPEN_DRAIN_OUT_PULL_UP); //PB10	SCL
	GPIO_Pin_Setup(GPIOB, 3, ALT_OPEN_DRAIN_OUT_PULL_UP); //PB3	SDA
	GPIOB -> AFR[0] |= (9 << 12);
	GPIOB -> AFR[1] |= (4 << 12);
}

void I2C3_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOA, 8, ALT_OPEN_DRAIN_OUT_PULL_UP); //PA8	SCL
	GPIO_Pin_Setup(GPIOB, 4, ALT_OPEN_DRAIN_OUT_PULL_UP); //PB4	SDA
	GPIOB -> AFR[1] |= (4 << 0);
	GPIOB -> AFR[0] |= (9 << 16);
}

/////////////////////////////////////////////////////////////////////////////////////////

void SPI1_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOB, 4, GEN_PUSH_PULL_OUT);	//NSS
	GPIO_Pin_Setup(GPIOB, 5, ALT_PUSH_PULL_OUT);	//SCK
	GPIO_Pin_Setup(GPIOB, 6, ALT_PUSH_PULL_OUT);	//MISO
	GPIO_Pin_Setup(GPIOB, 7, ALT_PUSH_PULL_OUT);	//MOSI

	GPIOB -> AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);
}

void SPI2_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOB, 12, GEN_PUSH_PULL_OUT);	//NSS
	GPIO_Pin_Setup(GPIOB, 10, ALT_PUSH_PULL_OUT);	//SCK
	GPIO_Pin_Setup(GPIOB, 14, ALT_PUSH_PULL_OUT);	//MISO
	GPIO_Pin_Setup(GPIOB, 15, ALT_PUSH_PULL_OUT);	//MOSI

	GPIOB -> AFR[1] |= (5 << 8) | (5 << 24) | (5 << 28);
}

void SPI3_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOB, 4, GEN_PUSH_PULL_OUT);	//NSS
	GPIO_Pin_Setup(GPIOB, 5, ALT_PUSH_PULL_OUT);	//SCK
	GPIO_Pin_Setup(GPIOB, 6, ALT_PUSH_PULL_OUT);	//MISO
	GPIO_Pin_Setup(GPIOB, 7, ALT_PUSH_PULL_OUT);	//MOSI

	GPIOB -> AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);
}

void SPI4_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOB, 12, GEN_PUSH_PULL_OUT);	//NSS
	GPIO_Pin_Setup(GPIOB, 13, ALT_PUSH_PULL_OUT);	//SCK
	GPIO_Pin_Setup(GPIOA, 11, ALT_PUSH_PULL_OUT);	//MISO
	GPIO_Pin_Setup(GPIOA,  1, ALT_PUSH_PULL_OUT);	//MOSI

	GPIOB -> AFR[1] |= 6 << 4*5;
	GPIOA -> AFR[1] |= 6 << 4*3;
	GPIOA -> AFR[0] |= 5 << 4*1;
}

void SPI5_Pin_Setup(void)
{
	GPIO_Pin_Setup(GPIOB,  1, GEN_PUSH_PULL_OUT);	//NSS
	GPIO_Pin_Setup(GPIOB,  0, ALT_PUSH_PULL_OUT);	//SCK
	GPIO_Pin_Setup(GPIOA, 12, ALT_PUSH_PULL_OUT);	//MISO
	GPIO_Pin_Setup(GPIOA,  5, ALT_PUSH_PULL_OUT);	//MOSI

	GPIOB -> AFR[0] |= (6 << 0) ;
	GPIOA -> AFR[1] |= (6 << 4*4);
	GPIOA -> AFR[0] |= (6 << 4*5);

}
