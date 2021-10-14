/*
 * W25Qx_Flash.c
 *
 *  Created on: 03-Oct-2021
 *      Author: Kunal
 */


#include <W25Qx_Flash/W25Qx_Flash.h>

//******************************************** Device Specific Functions ****************************************

static uint8_t W25Qx_Read_SR1(void)
{
	uint8_t SR1[2];
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x05); //SR1
	SR1[0] = SPI_Receive_Data(W25Q);
	SR1[1] = SPI_Receive_Data(W25Q);
	SPI_CSS_High(W25Q);
	return SR1[1];
}

 static uint8_t W25Qx_Read_SR2(void)
{
	uint8_t SR2[2];
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x31); //SR2
	SR2[0] = SPI_Receive_Data(W25Q);
	SR2[1] = SPI_Receive_Data(W25Q);
	SPI_CSS_High(W25Q);
	return SR2[1];
}


 static uint8_t W25Qx_Read_Busy_Bit(void)
{
	 uint8_t a,b;
	 a = W25Qx_Read_SR1();
	 b = ((0x01 & a) >> 0);
	 if(b == 1)
	 {
		 return 1;
	 }
	 else{
		 return 0;
	 }
}

 static uint8_t W25Qx_Read_Write_Enable_Latch(void)
 {
	 uint8_t a;
	 a = W25Qx_Read_SR1();
	 if(((0x02 & a) >> 1) == 1)
	 {
		 return 1;
	 }
	 else{
		 return 0;
	 }

 }

 static uint8_t W25Qx_Read_Block_Protection_Bits(void)
  {
 	 uint8_t a;
 	 a = W25Qx_Read_SR1();
 	 a = (0x1c & a);
 	 return a;

  }

 static uint8_t W25Qx_Read_Sector_Protect_Bits(void)
  {
 	 uint8_t a;
 	 a = W25Qx_Read_SR1();
 	 a = (0x1C & a);
 	 return a;

  }

 static  uint8_t W25Qx_Suspend_Status_Bit(void)
{
	 uint8_t a;
	 a = W25Qx_Read_SR2();
	 a = (0x80 & a);
	 return a;
}

 static void W25Qx_Write_SR1(uint8_t data)
{
	 	SPI_CSS_Low(W25Q);
	 	SPI_Send_Data(W25Q, 0x50); //Write SR volatile
	 	SPI_CSS_High(W25Q);

	 	SPI_CSS_Low(W25Q);
	 	SPI_Send_Data(W25Q, 0x01); //Write SR volatile
	 	SPI_Send_Data(W25Q, data); //Write SR volatile
	 	SPI_CSS_High(W25Q);

}

 static void W25Qx_Flash_Write_Enable()
 {
//	 do{
 	SPI_CSS_Low(W25Q);
 	SPI_Send_Data(W25Q, 0x06); //Write Enable
 	SPI_CSS_High(W25Q);
//	 }
// 	while(W25Qx_Read_Write_Enable_Latch() == 0);
Delay_us(50);

 }

 static void W25Qx_Flash_Write_Disable()
 {
 	SPI_CSS_Low(W25Q);
 	SPI_Send_Data(W25Q, Write_Disable); //Write Disable
 	SPI_CSS_High(W25Q);
 	while(W25Qx_Read_Write_Enable_Latch() == 1){}
 }

//******************************************** End **************************************************************


void W25Qx_Init(SPI_TypeDef *SPI)
{
	W25Q.SPI = SPI1;
	W25Q.Frame = SPI_Frame_8Bit;
	W25Q.phase = 1;
	W25Q.polarity = 1;
	W25Q.frequency = 3;
	W25Q.mode = SPI_Master;
	W25Q.type = SPI_Full_Duplex_Master;
	SPI_Init(W25Q);
	SPI_CSS_Init(W25Q);
}

void W25Qx_Reset()
{
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x66); //RESET ENABLE
	SPI_Send_Data(W25Q, 0x99); //SOFTWARE RESET
	SPI_CSS_High(W25Q);
}

void W25Qx_Chip_Erase()
{
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x60);
	SPI_CSS_High(W25Q);


}

void W25Qx_Erase_Sector(uint32_t address)
{
	W25Qx_Flash_Write_Enable();
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x20);
	SPI_Send_Data(W25Q,(address & 0xff0000) >> 16);
	SPI_Send_Data(W25Q,((address & 0xFF00) >> 8));
	SPI_Send_Data(W25Q,((address & 0xFF)));
	SPI_CSS_High(W25Q);


}



void W25Qx_Write_Flash(uint32_t addr, uint8_t data)
{
	W25Qx_Flash_Write_Enable();
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, Page_Program);
	SPI_Send_Data(W25Q,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(W25Q,((addr & 0xFF00) >> 8));
	SPI_Send_Data(W25Q,((addr & 0xFF)));
	SPI_Send_Data(W25Q, data);
	SPI_CSS_High(W25Q);

}

void W25Qx_Write_Flash_Buffer(uint32_t addr, int len, char *data)
{
	W25Qx_Flash_Write_Enable(); //write enable
	SPI_CSS_Low(W25Q); //
	SPI_Send_Data(W25Q, 0x02); //PAGE PROGRAM
	SPI_Send_Data(W25Q,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(W25Q,((addr & 0xFF00) >> 8));
	SPI_Send_Data(W25Q,((addr & 0xFF)));
	for(int i = 0; i < len; i++)
	{
		SPI_Send_Data(W25Q, data[i]);
	}
	SPI_CSS_High(W25Q);
//	while(W25Qx_Read_Busy_Bit() == 1);
	Delay_us(50);

}

uint8_t W25Qx_Read_Flash(uint32_t addr)
{
	while(W25Qx_Read_Busy_Bit() == 1);
	uint8_t x[2];
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x03);
	SPI_Send_Data(W25Q,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(W25Q,((addr & 0xFF00) >> 8));
	SPI_Send_Data(W25Q,((addr & 0xFF)));
	x[0] = SPI_Receive_Data(W25Q);
	x[1] = SPI_Receive_Data(W25Q);
	SPI_CSS_High(W25Q);

	return x[1];
}


void W25Qx_Read_Flash_Buffer(uint32_t addr, int len, uint8_t data[])
{
	Delay_us(50);
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x03);
	SPI_Send_Data(W25Q,((addr & 0xFF0000) >> 16));
	SPI_Send_Data(W25Q,((addr & 0xFF00) >> 8));
	SPI_Send_Data(W25Q,((addr & 0xFF)));
	for(int i = 0; i < len; i++)
	{
		data[i] = SPI_Receive_Data(W25Q);
	}
	SPI_CSS_High(W25Q);
	Delay_us(50);
}


uint32_t W25Qx_Read_ID(void)
{
	uint8_t x[6];
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, 0x9f); //9F
	x[0] = SPI_Receive_Data(W25Q);
	x[1] = SPI_Receive_Data(W25Q);
	x[2] = SPI_Receive_Data(W25Q);
	SPI_CSS_High(W25Q);
	return (x[0] << 16) | (x[1] << 8) | x[0];
}



void W25Qx_Erase_Data(uint32_t start_address, uint32_t end_address)
{
	uint32_t diff;
	uint8_t data[255];
	if(end_address == 0)
	{
		W25Qx_Write_Flash(start_address, 0x00);
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


void W25Qx_Read_JEDEC_ID(void)
{
	uint8_t x[4];
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, JEDEC_ID);
	x[0] = SPI_Receive_Data(W25Q);
	x[1] = SPI_Receive_Data(W25Q);
	x[2] = SPI_Receive_Data(W25Q);
	x[3] = SPI_Receive_Data(W25Q);
	SPI_CSS_High(W25Q);
}


uint64_t W25Qx_Read_Unique_ID(void) //works
{
	uint8_t x[8];
	uint64_t id;
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, Read_Unique_ID);
	SPI_Send_Data(W25Q, 0xff);
	SPI_Send_Data(W25Q, 0xff);
	SPI_Send_Data(W25Q, 0xff);
	SPI_Send_Data(W25Q, 0xff);
	x[0] = SPI_Receive_Data(W25Q); //0-7
	x[1] = SPI_Receive_Data(W25Q); //8-15
	x[2] = SPI_Receive_Data(W25Q); //15-
	x[3] = SPI_Receive_Data(W25Q);
	x[4] = SPI_Receive_Data(W25Q);
	x[5] = SPI_Receive_Data(W25Q);
	x[6] = SPI_Receive_Data(W25Q);
	x[7] = SPI_Receive_Data(W25Q);
	SPI_CSS_High(W25Q);
	id =    (x[0] << 56) | (x[1] << 48) |
			(x[2] << 40) | (x[3] << 32) |
			(x[4] << 24) | (x[5] << 16) |
			(x[6] << 8)  | (x[7] << 0) ;
return id;
}


uint8_t W25Qx_Read_Manufacturing_ID(void) //works
{
	uint8_t manu_id;
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, Manufacturer_Device_ID);
	SPI_Send_Data(W25Q, 0xff);
	SPI_Send_Data(W25Q, 0xff);
	SPI_Send_Data(W25Q, 0x00);
//	SPI_Send_Data(W25Q, 0xff);
	manu_id = SPI_Receive_Data(W25Q); //0-7
	SPI_CSS_High(W25Q);
	return manu_id ;
}


uint8_t W25Qx_Read_Device_ID(void) //works
{
	uint8_t device_id;
	SPI_CSS_Low(W25Q);
	SPI_Send_Data(W25Q, Manufacturer_Device_ID);
	SPI_Send_Data(W25Q, 0xff);
	SPI_Send_Data(W25Q, 0xff);
	SPI_Send_Data(W25Q, 0xFF);
	device_id = SPI_Receive_Data(W25Q); //0-7
	SPI_CSS_High(W25Q);
	return device_id ;
}


void W25Qx_Save_String(uint32_t addr,char *msg, ...)
{

char buff[10000];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for(int i = 0; i<= strlen(buff); i++)
	{
		W25Qx_Write_Flash(addr+i, buff[i]);
	}

//	#endif
}
