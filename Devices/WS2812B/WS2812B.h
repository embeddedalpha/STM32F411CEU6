/*
 * WS2812B.h
 *
 *  Created on: 21-Oct-2021
 *      Author: Kunal
 */

#ifndef WS2812B_WS2812B_H_
#define WS2812B_WS2812B_H_



#include "main.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"



SPI_Config WS2812B;


#define MAX_LEDS 1000

uint32_t led_color[MAX_LEDS][1];

void WS2812B_Init(SPI_TypeDef *SPI);
void WS2812B_Set_Color(int led_no, int red, green, int blue);
void WS2812B_Send_Data(uint32_t *led_color);
void WS2812B_Clear_Strip(void);



#endif /* WS2812B_WS2812B_H_ */

