/*
 * GPIO.h
 *
 *  Created on: 10-Sep-2021
 *      Author: Kunal
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "main.h"

//GENERAL PURPPOSE OUTPUT
#define GENERAL_PURPOSE_OUTPUT_PUSHPULL		    		0x2C
#define GENERAL_PURPOSE_OUTPUT_PUSHPULL_PULLUP			0x2D
#define GENERAL_PURPOSE_OUTPUT_PUSHPULL_PULLDW			0x2E
#define GENERAL_PURPOSE_OUTPUT_OPENDRAIN				0x3C
#define GENERAL_PURPOSE_OUTPUT_OPENDRAIN_PULLUP			0x3D
#define GENERAL_PURPOSE_OUTPUT_OPENDRAIN_PULLDW			0x3E

//ALTERNATE FUNCTION OUTPUT
#define ALTERNATE_FUNCTION_OUTPUT_PUSHPULL		    	0x4C
#define ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLUP		0x4D
#define ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLDW		0x4E
#define ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN		    	0x5C
#define ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP		0x5D
#define ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLDW		0x5E

//GENERAL PURPPOSE INTPUT
#define INPUT_FLOATING	0x00
#define INPUT_PULLUP	0x01
#define INPUT_PULLDW	0x02

//ANALOG INPUT
#define ANALOG_INPUT	0x60

//ALTERNATE FUNCTION
#define MCO_FUNCTION	    0

#define TIM1_BKIN		1
#define TIM1_CH1		1
#define TIM1_CH2		1
#define TIM1_CH3		1
#define TIM1_CH4		1
#define TIM1_CH1N		1
#define TIM1_CH2N		1
#define TIM1_CH3N		1
#define TIM1_CH4N		1

#define TIM2_CH1  		1
#define TIM2_CH2		1
#define TIM2_CH3		1
#define TIM2_CH4		1

#define TIM3_CH1		  2
#define TIM3_CH2		  2
#define TIM3_CH3		  2
#define TIM3_CH4		  2

#define TIM4_CH1		  2
#define TIM4_CH2		  2
#define TIM4_CH3		  2
#define TIM4_CH4		  2

#define TIM5_CH1		  2
#define TIM5_CH2		  2
#define TIM5_CH3		  2
#define TIM5_CH4		  2

#define TIM9_CH1		  3
#define TIM9_CH2		  3
#define TIM9_CH3		  3
#define TIM9_CH4		  3

#define TIM10_CH1		  3
#define TIM10_CH2		  3
#define TIM10_CH3		  3
#define TIM10_CH4		  3

#define TIM11_CH1		  3
#define TIM11_CH2		  3
#define TIM11_CH3		  3
#define TIM11_CH4		  3

#define I2C1_SCL		  4
#define I2C1_SDA		  4
#define I2C2_SCL		  4
#define I2C2_SDA		  4
#define I2C3_SCL		  4
#define I2C3_SDA		  9

#define SPI1_CLK		  5
#define SPI1_MOSI		  5
#define SPI1_MISO		  5

#define SPI2_CLK		  5
#define SPI2_MOSI		  5
#define SPI2_MISO		  5

#define SPI3_CLK		  7
#define SPI3_MOSI		  6
#define SPI3_MISO		  6

#define SPI4_CLK		  6
#define SPI4_MOSI		  5
#define SPI4_MISO		  6

#define SPI5_CLK		  6
#define SPI5_MOSI		  6
#define SPI5_MISO		  6

#define USART1_CLK		7
#define USART1_TX		  7
#define USART1_RX		  7
#define USART1_CTS		7
#define USART1_RTS		7

#define USART2_CLK		7
#define USART2_TX		  7
#define USART2_RX		  7
#define USART2_CTS		7
#define USART2_RTS		7

#define USART6_TX		  7
#define USART6_RX		  7


#define SDIO_CMD 		12
#define SDIO_D1 		12
#define SDIO_D2 		12
#define SDIO_D3 		12
#define SDIO_D4 		12
#define SDIO_D5 		12
#define SDIO_D6 		12
#define SDIO_D7 		12


void GPIO_Pin_Setup(char Port, uint8_t pin, uint8_t function, uint8_t alternate_function);

#endif /* GPIO_GPIO_H_ */
