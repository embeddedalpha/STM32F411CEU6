/*
 * NAU7802.c
 *
 *  Created on: 25-Oct-2021
 *      Author: Kunal
 */

#include "NAU7802.h"

void NAU7802_Single_Write(uint8_t address, uint8_t data)
{
	I2C_Master_TX_Start(A);
	I2C_Master_Send_Address(A, 0x2A);
	I2C_Master_Send_Data(A, address);
	I2C_Master_Send_Data(A, data);
	I2C_Master_Stop(A);
}


void NAU7802_Burst_Write(uint8_t address, uint8_t data[], int length)
{
	I2C_Master_TX_Start(A);
	I2C_Master_Send_Address(A, 0x2A);
	I2C_Master_Send_Data(A, address);
	for(int i =  0; i < length; i++)
	{
		I2C_Master_Send_Data(A, data[i]);
	}
	I2C_Master_Stop(A);
}


uint8_t NAU7802_Single_Read(uint8_t address)
{
	I2C_Master_TX_Start(A);
	I2C_Master_Send_Address(A, 0x2A);
	I2C_Master_Send_Data(A, address);
	I2C_Master_Stop(A);
	I2C_Master_TX_Start(A);
	I2C_Master_Receive_Address(A, 0x2A);
	uint8_t x = I2C_Master_Receive_Data(A);
	I2C_Master_Stop(A);
	return x;
}

void NAU7802_Burst_Read(uint8_t address, uint8_t *data, int length)
{
	I2C_Master_TX_Start(A);
	I2C_Master_Send_Address(A, 0x2A);
	I2C_Master_RX_Start(A);
	I2C_Master_Receive_Address(A, 0x2A);
	for(int i = 0; i < length; i++)
	{
		data[i] = I2C_Master_Receive_Data(A);
	}
	I2C_Master_Stop(A);
}

void NAU7802_Reset_Enable(void)
{
	NAU7802_Single_Write(0x00, 0x01);
}

void NAU7802_Reset_Diable(void)
{
	NAU7802_Single_Write(0x00, 0x00);
}

uint8_t NAU7802_Power_ON_Sequence(void)
{
	int x;
	NAU7802_Single_Write(0x00, 0x02);
	Delay_ms(2);
	x = NAU7802_Single_Read(0x00);
	if((x & 0x08) == 0x08){
		return 1;
	}
	else
	{
		return 0;
	}

}


uint8_t NAU7802_Init(I2C_TypeDef *I2C)
{
	int counter = 0;
	A.I2C = I2C1;
	A.mode = Fast_Mode;
	I2C_Master_Init(A);

//	//Reset Register Values:
//	NAU7802_Reset_Enable();
//	//Power on Sequence
//	uint8_t x;
//	do {
//		x = NAU7802_Power_ON_Sequence();
//		counter++;
//	} while (x == 0 || counter < 10);
//	if(counter > 10)
//	{
//		return 0;
//	}
//	else{
//		counter = 0;
//	}
//	Delay_ms(10);
//	x = 0;
//	do {
//		x = NAU7802_Single_Read(0x00);
//		counter++;
//	} while (x != 0xAE || counter < 10);
//	if(counter > 10)
//	{
//		return 0;
//	}
//	else{
//		counter = 0;
//	}
//	return 1;

}
