/*
 * NAU7802.h
 *
 *  Created on: 25-Oct-2021
 *      Author: Kunal
 */

#ifndef NAU7820_NAU7802_H_
#define NAU7820_NAU7802_H_


#include "main.h"
#include "GPIO/GPIO.h"
#include "I2C/I2C.h"

I2C_Config nau780;

#define nau7802_address          0x2A
#define nau7802_address_read     0x2B
#define nau7802_address_write    0x2A

void NAU7802_Init(I2C_TypeDef *PORT);
void NAU7802_Get_Data(void);


#endif /* NAU7820_NAU7802_H_ */
