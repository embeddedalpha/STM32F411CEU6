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

//********************************	Asynchronous Communication	********************************

void UART_Init(Serial UART);
void UART_Transmit(Serial UART, char *data);
char UART_Receive(Serial UART);
char UART_Transceive(Serial UART);


//********************************	Synchronous Communication	********************************

void USART_Init(Serial UART);
void USART_Transmit(Serial UART, char *data);
char USART_Receive(Serial UART);
char USART_Transceive(Serial UART, char byte);

#endif /* USART_USART_H_ */
