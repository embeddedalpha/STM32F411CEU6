/*
 * main.h
 *
 *  Created on: 09-Jul-2021
 *      Author: Kunal
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "stdbool.h"
#include "stdint.h"
#include "system_stm32f4xx.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "USART/USART.h"
#include "stdio.h"

int baud;

__STATIC_INLINE void MCU_Clock_Setup(void)
{
	uint8_t pll_m = 25;
	uint8_t pll_n = 192;
	uint8_t pll_p = 0;
	uint8_t pll_q = 4;

	RCC->PLLCFGR = 0x00000000;

	RCC -> CR |= RCC_CR_HSEON;
	while(!(RCC -> CR & RCC_CR_HSERDY)){}
	RCC -> APB1ENR |= RCC_APB1ENR_PWREN;
	PWR ->CR |= PWR_CR_VOS;
	FLASH -> ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_DCEN |
			FLASH_ACR_LATENCY_3WS;
	RCC->PLLCFGR |= (pll_q << 24) | (pll_p << 16) | (pll_n << 6) | (pll_m << 0);
	RCC ->PLLCFGR |= 1 << 22;
//    RCC->PLLCFGR = 0x4403019;
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC -> CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC -> CFGR |= RCC_CFGR_PPRE2_DIV1;
//	RCC -> APB2ENR |= 0x4000;
	RCC -> CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY)){}
//	RCC -> CR |= RCC_CR_PLLI2SON;
//	while(!(RCC->CR & RCC_CR_PLLI2SRDY)){}
	RCC -> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC -> CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
SystemCoreClockUpdate();
//SysTick_Config(SystemCoreClock/1000);

}

__STATIC_INLINE int I2S_Clock_Init()
{
//	int plli2s_m = 16;
//	int plli2s_n = 192;
//	int plli2s_r = 2;
//	RCC -> PLLI2SCFGR |= (plli2s_m << 0) | (plli2s_n << 6) | (plli2s_r << 28);
//	RCC -> PLLI2SCFGR = 0x20003010;
	RCC -> PLLI2SCFGR = 0x20005619; //0x20006019
	RCC -> CR |= RCC_CR_PLLI2SON;
	while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
	return (0UL);
}



__STATIC_INLINE uint32_t Delay_Config(void)
{

	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE uint32_t Delay_us(unsigned long us)
{

	SysTick->LOAD = (uint32_t)(us * (1/1000000) * SystemCoreClock);
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE uint32_t Delay_ms(unsigned long ms)
{
	SysTick->LOAD = (uint32_t)(ms * (1/1000) * SystemCoreClock);
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}


__STATIC_INLINE uint32_t Delay_s(unsigned long s)
{
	s = s * 1000;
	for (; s>0; s--)
	{
		Delay_ms(1);
	}
	return (0UL);
}

__STATIC_INLINE void Console_Init(int baudrate)
{
	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	GPIOA -> MODER   |= (2 << 18) | (2 << 20);	//9 -> tx	10 -> rx
	GPIOA -> OTYPER  |= (0 << 9)  | (0 << 10) ;
	GPIOA -> OSPEEDR |= (3 << 9)  | (3 << 10);
	GPIOA -> PUPDR   |= (0 << 18) | (0 << 20);
	GPIOA -> AFR[1]  |= (7 << 4)  | (5 << 8);
	USART1 ->CR1 |= USART_CR1_UE;
	baud = baudrate;
	USART1->BRR = (int)(SystemCoreClock / (16 * baudrate)) << 4;
	USART1 ->CR1 |= USART_CR1_TE | USART_CR1_RE  ;
}

__STATIC_INLINE void printConsole(char *msg, ...)
{

char buff[100];
//	#ifdef DEBUG_UART

	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i<= strlen(buff); i++){
	USART1 -> DR = buff[i];
	USART1 -> CR1 |= USART_CR1_SBK;
			while (!(USART1->SR & USART_SR_TXE));
	}

//	#endif
}



#endif /* MAIN_H_ */
