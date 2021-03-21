/*
 * GPIO.h
 *
 *  Created on: 21-Mar-2021
 *      Author: Kunal
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "stm32f4xx.h"
#include "stm32f411xe.h"

#define GEN_PUSH_PULL_OUT	        0b0101100
#define GEN_PUSH_PULL_OUT_PULL_UP	0b0101101
#define GEN_PUSH_PULL_OUT_PULL_DW	0b0101110
#define GEN_PUSH_PULL_OUT	        0b0101100
#define GEN_PUSH_PULL_OUT_PULL_UP	0b0101101
#define GEN_PUSH_PULL_OUT_PULL_DW	0b0101110

#define ALT_PUSH_PULL_OUT	        0b1001100
#define ALT_PUSH_PULL_OUT_PULL_UP	0b1001101
#define ALT_PUSH_PULL_OUT_PULL_DW	0b1001110
#define ALT_PUSH_PULL_OUT	        0b1001100
#define ALT_PUSH_PULL_OUT_PULL_UP	0b1001101
#define ALT_PUSH_PULL_OUT_PULL_DW	0b1001110

#define FLOAT_PUSH_PULL_IN	      0b0000000
#define INPUT_PULL_UP	            0b0000001
#define INPUT_PULL_DW	            0b0000010
#define INPUT_ANALOG      	      0b1100000


#define Rising_Edge     1
#define Falling_Ege     2
#define Rise_n_Fall_Edge 3


void GPIO_Pin_Setup(GPIO_TypeDef *port, int pin, int mode);

void GPIO_Pin_Interrupt_Setup(GPIO_TypeDef *port, int pin, int type);

void GPIO_Interrupt_Enable(int pin, int priority, IRQn_Type irqnum);



#endif /* GPIO_GPIO_H_ */
