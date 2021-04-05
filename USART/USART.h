/*
 * USART.h
 *
 *  Created on: 05-Apr-2021
 *      Author: Kunal
 */

#ifndef USART_USART_H_
#define USART_USART_H_

#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "stdbool.h"
#include "GPIO/GPIO.h"

#define Baud_2400		4375
#define Baud_9600		1093.75
#define Baud_19200		546.875
#define Baud_38400		273.5
#define Baud_57600		182.25
#define Baud_115200		91.125
#define Baud_230400		45.625
#define Baud_460800		22.75
#define Baud_921600		11.375
#define Baud_1792000	5.875
#define Baud_1843200	5.75
#define Baud_3584000	2.875
#define Baud_3686400	2.875
#define Baud_7168000	1.5
#define Baud_7372800	1.375
#define Baud_9000000	1.125
#define Baud_10500000	1


typedef struct USART_Config
{
	USART_TypeDef *USART;
	bool word_length;
	bool parity;
	bool tx_int;
	bool rx_int;
	bool tx_enable;
	bool rx_enable;
	uint8_t stop_bits;
	bool clock_enable;
	bool clock_polarity;
	bool clock_phase;
	bool ctse_enable;
	bool rtse_enable;
	bool dma_tx;
	bool dma_rx;

}USART_Config;


void USART_Init(USART_Config USART);

void USART_TX(USART_Config USART, uint8_t data);
uint8_t USART_RX(USART_Config USART);

void USART_TX_HFC(USART_Config USART, uint8_t data);
uint8_t USART_RX_HFC(USART_Config USART);




#endif /* USART_USART_H_ */
