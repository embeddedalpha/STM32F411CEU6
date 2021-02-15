#ifndef _GPIO_H_
#define _GPIO_H_



#include "stm32f411xe.h"


#define GEN_PushPull_Output                    0x2C
#define GEN_PushPull_Output_PullUP             0x2D
#define GEN_PushPull_Output_PullDown           0x2E

#define GEN_PushPull_Output_OpenDrain          0x3C
#define GEN_PushPull_Output_OpenDrain_PullUP   0x3C
#define GEN_PushPull_Output_OpenDrain_PullDown 0x3C

#define ALT_PushPull_Output                    0x4C
#define ALT_PushPull_Output_PullUP             0x4D
#define ALT_PushPull_Output_PullDown           0x4E

#define ALT_PushPull_Output_OpenDrain          0x5C
#define ALT_PushPull_Output_OpenDrain_PullUP   0x5C
#define ALT_PushPull_Output_OpenDrain_PullDown 0x5C

#define Input_Floating	0x00
#define Input_PullUP		0x01
#define Input_PullDown	0x02
#define Analog_Pin      0x60


void GPIO_Init(GPIO_TypeDef *GPIO,uint8_t pin, uint8_t config);


void ADC_Pin_Init(uint8_t pin);
void SPI_Pin_Init(SPI_TypeDef *SPI);
void I2S_Pin_Init(SPI_TypeDef *SPI);
void I2C_Pin_Init(I2C_TypeDef *I2C);
void USART_Pin_Init(USART_TypeDef *USART);
void UART_Pin_Init(USART_TypeDef *USART);
void TIM_Pin_Init(TIM_TypeDef *TIM);
void SDIO_Pin_Init(SDIO_TypeDef *sdio);







#endif
