/*
 * US100_Serial.h
 *
 *  Created on: 02-Oct-2021
 *      Author: Kunal
 */

#ifndef US100_SERIAL_H_
#define US100_SERIAL_H_

#include "main.h"
#include "USART.h"


void US100_Init(Serial US);
int US_Get_Temp(Serial US);
float US_Get_Distance(Serial US);



#endif
