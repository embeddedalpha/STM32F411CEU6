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
	uint8_t SR1[2];
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x05); //SR1
	SR1[0] = SPI_Receive_Data(QH32);
	SR1[1] = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);
	return SR1[1];
}

 static uint8_t QH32x_Read_SR2(void)
{
	uint8_t SR2[2];
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x31); //SR2
	SR2[0] = SPI_Receive_Data(QH32);
	SR2[1] = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);
	return SR2[1];
}


 static uint8_t QH32x_Read_Busy_Bit(void)
{
	 uint8_t a,b;
	 a = QH32x_Read_SR1();
	 b = ((0x01 & a) >> 0);
	 if(b == 1)
	 {
		 return 1;
	 }
	 else{
		 return 0;
	 }

}

 static bool QH32x_Read_Write_Enable_Latch(void)
 {
	 uint8_t a;
	 a = QH32x_Read_SR1();
	 if(((0x02 & a) >> 1) == 1)
	 {
		 return 1;
	 }
	 else{
		 return 0;
	 }

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

 static  uint8_t QH32x_Suspend_Status_Bit(void)
{
	 uint8_t a;
	 a = QH32x_Read_SR2();
	 return (0x80 & a);
}

 static void QH32x_Write_SR1(uint8_t data)
{
	 	SPI_CSS_Low(QH32);
	 	SPI_Send_Data(QH32, 0x50); //Write SR volatile
	 	SPI_CSS_High(QH32);

	 	SPI_CSS_Low(QH32);
	 	SPI_Send_Data(QH32, 0x01); //Write SR volatile
	 	SPI_Send_Data(QH32, data); //Write SR volatile
	 	SPI_CSS_High(QH32);

}

 static void QH32x_Flash_Write_Enable()
 {
	 do{
 	SPI_CSS_Low(QH32);
 	SPI_Send_Data(QH32, 0x06); //Write Enable
 	SPI_CSS_High(QH32);
	 }
 	while(QH32x_Read_Write_Enable_Latch() == 0);

 }

 static void QH32x_Flash_Write_Disable()
 {
 	SPI_CSS_Low(QH32);
 	SPI_Send_Data(QH32, Write_Disable); //Write Disable
 	SPI_CSS_High(QH32);
 	while(QH32x_Read_Write_Enable_Latch() == 1){}
 }

//******************************************** End **************************************************************


void QH32x_Init(SPI_TypeDef *SPI)
{
	QH32.SPI = SPI1;
	QH32.Frame = SPI_Frame_8Bit;
	QH32.phase = 1;
	QH32.polarity = 1;
	QH32.frequency = 3;
	QH32.mode = SPI_Master;
	QH32.type = Full_Duplex_Master;
	SPI_Init(QH32);
	SPI_CSS_Init(QH32);
}

void QH32x_Reset()
{
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x66); //RESET ENABLE
	SPI_Send_Data(QH32, 0x99); //SOFTWARE RESET
	SPI_CSS_High(QH32);
}

void QH32x_Chip_Erase()
{
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x60);
	SPI_CSS_High(QH32);


}

void QH32x_Erase_Sector(uint32_t address)
{
	QH32x_Flash_Write_Enable();
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x20);
	SPI_Send_Data(QH32,(address & 0xff0000) >> 16);
	SPI_Send_Data(QH32,((address & 0xFF00) >> 8));
	SPI_Send_Data(QH32,((address & 0xFF)));
	SPI_CSS_High(QH32);
}



void QH32x_Write_Flash(uint32_t addr, uint8_t data)
{
	QH32x_Flash_Write_Enable();
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, Page_Program);
	SPI_Send_Data(QH32,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(QH32,((addr & 0xFF00) >> 8));
	SPI_Send_Data(QH32,((addr & 0xFF)));
	SPI_Send_Data(QH32, data);
	SPI_CSS_High(QH32);

}

void QH32x_Write_Flash_Buffer(uint32_t addr, int len, char *data)
{
	QH32x_Flash_Write_Enable(); //write enable
	SPI_CSS_Low(QH32); //
	SPI_Send_Data(QH32, 0x02); //PAGE PROGRAM
	SPI_Send_Data(QH32,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(QH32,((addr & 0xFF00) >> 8));
	SPI_Send_Data(QH32,((addr & 0xFF)));
	for(int i = 0; i < len; i++)
	{
		SPI_Send_Data(QH32, data[i]);
	}
	SPI_CSS_High(QH32);

}

uint8_t QH32x_Read_Flash(uint32_t addr)
{
	while(QH32x_Read_Busy_Bit() == 1);
	uint8_t x[2];
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x03);
	SPI_Send_Data(QH32,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(QH32,((addr & 0xFF00) >> 8));
	SPI_Send_Data(QH32,((addr & 0xFF)));
	x[0] = SPI_Receive_Data(QH32);
	x[1] = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);

	return x[1];
}


void QH32x_Read_Flash_Buffer(uint32_t addr, int len, uint8_t data[])
{
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x03);
	SPI_Send_Data(QH32,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(QH32,((addr & 0xFF00) >> 8));
	SPI_Send_Data(QH32,((addr & 0xFF)));
	for(int i = 0; i < len; i++)
	{
		data[i] = SPI_Receive_Data(QH32);
	}
	SPI_CSS_High(QH32);
}


uint32_t QH32x_Read_ID(void)
{
	uint8_t x[6];
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, 0x9f); //9F
	x[0] = SPI_Receive_Data(QH32);
	x[1] = SPI_Receive_Data(QH32);
	x[2] = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);
	return (x[0] << 16) | (x[1] << 8) | x[0];
}



void QH32x_Erase_Data(uint32_t start_address, uint32_t end_address)
{
	uint32_t diff;
	uint8_t data[255];
	if(end_address == 0)
	{
		QH32x_Write_Flash(start_address, 0x00);
	}
	else
	{
		diff = end_address - start_address;
		uint32_t i;
		for(i = 0; i < diff; i++)
		{
			data[i] = 0xFF;
		}
	}
}


void QH32x_Read_JEDEC_ID(void)
{
	uint8_t x[4];
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, JEDEC_ID);
	x[0] = SPI_Receive_Data(QH32);
	x[1] = SPI_Receive_Data(QH32);
	x[2] = SPI_Receive_Data(QH32);
	x[3] = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);
}


uint64_t QH32x_Read_Unique_ID(void) //works
{
	uint8_t x[8];
	uint64_t id;
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, Read_Unique_ID);
	SPI_Send_Data(QH32, 0xff);
	SPI_Send_Data(QH32, 0xff);
	SPI_Send_Data(QH32, 0xff);
	SPI_Send_Data(QH32, 0xff);
	x[0] = SPI_Receive_Data(QH32); //0-7
	x[1] = SPI_Receive_Data(QH32); //8-15
	x[2] = SPI_Receive_Data(QH32); //15-
	x[3] = SPI_Receive_Data(QH32);
	x[4] = SPI_Receive_Data(QH32);
	x[5] = SPI_Receive_Data(QH32);
	x[6] = SPI_Receive_Data(QH32);
	x[7] = SPI_Receive_Data(QH32);
	SPI_CSS_High(QH32);
	id =    (x[0] << 56) | (x[1] << 48) |
			(x[2] << 40) | (x[3] << 32) |
			(x[4] << 24) | (x[5] << 16) |
			(x[6] << 8)  | (x[7] << 0) ;
return id;
}


uint8_t QH32x_Read_Manufacturing_ID(void) //works
{
	uint8_t manu_id;
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, Manufacturer_Device_ID);
	SPI_Send_Data(QH32, 0xff);
	SPI_Send_Data(QH32, 0xff);
	SPI_Send_Data(QH32, 0x00);
//	SPI_Send_Data(QH32, 0xff);
	manu_id = SPI_Receive_Data(QH32); //0-7
	SPI_CSS_High(QH32);
	return manu_id ;
}


uint8_t QH32x_Read_Device_ID(void) //works
{
	uint8_t device_id;
	SPI_CSS_Low(QH32);
	SPI_Send_Data(QH32, Manufacturer_Device_ID);
	SPI_Send_Data(QH32, 0xff);
	SPI_Send_Data(QH32, 0xff);
	SPI_Send_Data(QH32, 0xFF);
	device_id = SPI_Receive_Data(QH32); //0-7
	SPI_CSS_High(QH32);
	return device_id ;
}
