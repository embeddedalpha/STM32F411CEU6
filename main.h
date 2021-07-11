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
	RCC -> CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC -> CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC -> CFGR |= RCC_CFGR_PPRE2_DIV1;
	RCC->PLLCFGR |= (pll_q << 24) | (pll_p << 16) | (pll_n << 6) | (pll_m << 0);
	RCC ->PLLCFGR |= 1 << 22;
	RCC -> APB2ENR |= 0x4000;
	RCC -> CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY)){}
//	RCC -> CR |= RCC_CR_PLLI2SON;
//	while(!(RCC->CR & RCC_CR_PLLI2SRDY)){}
	RCC -> CFGR |= RCC_CFGR_SW_PLL;
	while((RCC -> CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL);
SystemCoreClockUpdate();
SysTick_Config(SystemCoreClock/1000);




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


#endif /* MAIN_H_ */
