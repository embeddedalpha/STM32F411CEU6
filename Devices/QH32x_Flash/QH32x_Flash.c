/*
 * QH32x_Flash.c
 *
 *  Created on: 03-Oct-2021
 *      Author: Kunal
 */


#include "QH32x_Flash.h"

//******************************************** Device Specific Functions ****************************************

static uint8_t QH32x_Read_SR1(void)
{
	uint8_t SR1;
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x01); //SR1
	SR1 = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);
	return SR1;
}

 static uint8_t QH32x_Read_SR2(void)
{
	uint8_t SR2;
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x31); //SR2
	SR2 = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);
	return SR2;
}

 static  void QH32x_Read_Busy_Bit(void)
{
	 uint8_t a;
	 a = QH32x_Read_SR1();
	 return (0x01 & a);
}

 static bool QH32x_Read_Write_Enable_Latch(void)
 {
	 uint8_t a;
	 a = QH32x_Read_SR1();
	 return (0x02 & a);

 }

 static uint8_t QH32x_Read_Block_Protection_Bits(void)
  {
 	 uint8_t a;
 	 a = QH32x_Read_SR1();
 	 return (0x1C & a);

  }

 static uint8_t QH32x_Read_Sector_Protect_Bits(void)
  {
 	 uint8_t a;
 	 a = QH32x_Read_SR1();
 	 return (0x1C & a);

  }

 static  void QH32x_Suspend_Status_Bit(void)
{
	 uint8_t a;
	 a = QH32x_Read_SR2();
	 return (0x80 & a);
}

 static void QH32x_Write_SR2(void)
{

}

//******************************************** End **************************************************************


bool QH32x_Init(SPI_TypeDef *SPI)
{
	QH32.SPI = SPI1;
	QH32.Frame = SPI_Frame_8Bit;
	QH32.phase = 1;
	QH32.polarity = 1;
	QH32.frequency = 4;
	QH32.mode = SPI_Master;
	QH32.type = Full_Duplex_Master;
	SPI_Init(QH32);
	SPI_CSS_Init(QH32);
}

void QH32x_Reset()
{

}
void QH32x_Flash_Write_Enable()
{
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x06); //Write Enable
	SPI_CSS_High(QH32);

}
void QH32x_Write_Flash(uint32_t addr, uint8_t data);
void QH32x_Write_Flash_Buffer(uint32_t addr, int len, uint8_t *data);

void QH32x_Read_Flash(uint32_t addr);
void QH32x_Read_Flash_Buffer(uint32_t addr, int len, uint8_t *data);



void QH32x_Test();

