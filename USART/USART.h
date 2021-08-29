/*
 * USART.h
 *
 *  Created on: 30-Aug-2021
 *      Author: Kunal
 */

#ifndef USART_USART_H_
#define USART_USART_H_

#include "main.h"

#define Half_Duplex 1
#define Full_Duplex 0

typedef struct UART
{
	USART_TypeDef *port;
	bool mode;
	int baudrate;
	bool hardware_control;
	bool TX_DMA;
	bool RX_DMA;

}Serial;



void UART_Init(Serial UART);

#endif /* USART_USART_H_ */
