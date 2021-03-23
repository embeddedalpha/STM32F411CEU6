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

#define GEN_PUSH_PULL_OUT	        0b01011000
#define GEN_PUSH_PULL_OUT_PULL_UP	0b01011010
#define GEN_PUSH_PULL_OUT_PULL_DW	0b01011100
#define GEN_OPEN_DRAIN_OUT	        0b01011000
#define GEN_OPEN_DRAIN_OUT_PULL_UP	0b01011010
#define GEN_OPEN_DRAIN_OUT_PULL_DW	0b01011100

#define ALT_PUSH_PULL_OUT	        0b10011000
#define ALT_PUSH_PULL_OUT_PULL_UP	0b10011010
#define ALT_PUSH_PULL_OUT_PULL_DW	0b10011100
#define ALT_OPEN_DRAIN_OUT	        0b10011000
#define ALT_OPEN_DRAIN_OUT_PULL_UP	0b10011010
#define ALT_OPEN_DRAINL_OUT_PULL_DW	0b10011100

#define FLOAT_PUSH_PULL_IN	        0b00000000
#define INPUT_PULL_UP	            0b00000010
#define INPUT_PULL_DW	            0b00000100
#define INPUT_ANALOG      	        0b11000000


#define Rising_Edge     1
#define Falling_Ege     2
#define Rise_n_Fall_Edge 3


void GPIO_Pin_Setup(GPIO_TypeDef *port, int pin, int mode);

void GPIO_Pin_Interrupt_Setup(GPIO_TypeDef *port, int pin, int type);

void GPIO_Interrupt_Enable(int pin, int priority, IRQn_Type irqnum);


void I2C1_Pin_Setup(void);
void I2C2_Pin_Setup(void);
void I2C3_Pin_Setup(void);

void SPI1_Pin_Setup(void);
void SPI2_Pin_Setup(void);
void SPI3_Pin_Setup(void);
void SPI4_Pin_Setup(void);
void SPI5_Pin_Setup(void);

void I2S1_Pin_Setup(void);
void I2S2_Pin_Setup(void);
void I2S3_Pin_Setup(void);
void I2S4_Pin_Setup(void);
void I2S5_Pin_Setup(void);

void SDIO_MMC_8_Bit_Pin_Setup(void);
void SDIO_MMC_4_Bit_Pin_Setup(void);
void SDIO_MMC_1_Bit_Pin_Setup(void);
void SD_4_Bit_Pin_Setup(void);
void SD_1_Bit_Pin_Setup(void);

void UART1_Pin_Setup(void);
void UART1_HW_Flow_Control_Pin_Setup(void);
void USART1_Pin_Setup(void);

void UART2_Pin_Setup(void);
void UART2_HW_Flow_Control_Pin_Setup(void);
void USART2_Pin_Setup(void);

#endif /* GPIO_GPIO_H_ */
