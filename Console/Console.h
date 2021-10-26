/*
 * Console.h
 *
 *  Created on: 25-Oct-2021
 *      Author: Kunal
 */

#ifndef CONSOLE_CONSOLE_H_
#define CONSOLE_CONSOLE_H_

#include "main.h"
#include "GPIO/GPIO.h"


  void Console_Init(USART_TypeDef *port,int baudrate);
  void printConsole(USART_TypeDef *port,char *msg, ...);
  int scanConsole(char *msg,...);
  char * Console_Return(char *s);







#endif /* CONSOLE_CONSOLE_H_ */

