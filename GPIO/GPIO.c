#include "GPIO.h"



void GPIO_Init(GPIO_TypeDef *GPIO,uint8_t pin, uint8_t config)
{
	if(GPIO == GPIOA)
	{
		  RCC->APB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}
		else if(GPIO == GPIOB)
		{
			RCC->APB1ENR |= RCC_AHB1ENR_GPIOBEN;
		}
			else if(GPIO == GPIOC)
			{
				RCC->APB1ENR |= RCC_AHB1ENR_GPIOCEN;
			}
			
			GPIO->MODER |= (uint8_t)(((0x60 & config) >> 5) << (pin * 2));
			GPIO->OTYPER |= (uint8_t)(((0x10 & config) >> 4) << (pin * 1));
			GPIO->OSPEEDR |= (uint8_t)(((0x0C & config) >> 2) << (pin * 2));
			GPIO->PUPDR |= (uint8_t)((0x03 & config)  << (pin * 2));

}
//

void ADC_Pin_Init(uint8_t pin)
{
	GPIO_Init(GPIOA,pin,Analog_Pin);
}
//


void SPI_Master_Pin_Init(SPI_TypeDef *SPI,uint8_t mode)
{
	if(SPI == SPI1)
	{
	switch(mode)
	{
		case SPI_FULL_DUPLEX_MASTER:
		{
		
		break;
		}
		//
		case SPI_FULL_DUPLEX_SLAVE:
		{
		
		break;
		}
		//
		case SPI_HALF_DUPLEX_MASTER:
		{
		
		break;
		}
		//
		case SPI_HALF_DUPLEX_SLAVE:
		{
		
		break;
		}
		//
		case SPI_RECEIVE_ONLY_MASTER:
		{
		
		break;
		}
    //
		case SPI_RECEIVE_ONLY_SLAVE:
		{
		
		break;
		}	
		case SPI_TRANSMIT_ONLY_MASTER:
		{
		
		break;
		}				
	}
	
	}
		else if(SPI == SPI2)
		{}
			else if(SPI == SPI3)
			{}
				else if(SPI == SPI4)
				{}
					else if(SPI == SPI5)
					{}
}
//



void I2S_Pin_Init(SPI_TypeDef *SPI){}
void I2C_Pin_Init(I2C_TypeDef *I2C){}
void USART_Pin_Init(USART_TypeDef *USART){}
void UART_Pin_Init(USART_TypeDef *USART){}
void TIM_Pin_Init(TIM_TypeDef *TIM){}
void SDIO_Pin_Init(SDIO_TypeDef *sdio){}
	
	
	
