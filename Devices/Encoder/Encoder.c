
#include "Encoder.h"


void Encoder_Init(TIM_TypeDef *timer)
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN ;

	GPIO_Pin_Setup(GPIOA, 8, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, TIM1_CH1);
	GPIO_Pin_Setup(GPIOA, 9, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, TIM1_CH2);
	timer ->ARR = 0xffff;
	timer -> CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	timer -> CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
	timer -> SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	timer -> CR1 |= TIM_CR1_CEN;
}

uint16_t Encoder_Read_Raw(TIM_TypeDef *timer)
{
return timer -> CNT;
}
