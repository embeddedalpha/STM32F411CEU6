#include "main.h"
#include "Console/Console.h"
#include "I2C/I2C.h"
#include "NAU7820/NAU7802_Reg.h"

	I2C_Config NAU7802;


int main()
{

	MCU_Clock_Setup();
	Delay_Config();
	Console_Init(USART1, 9600);
//	x.I2C = I2C1;
//	x.mode = I2C_Fast_Mode;
//	I2C_Master_Init(x);

	uint32_t a,b,c,d;
	int32_t sf;
	NAU7802.I2C = I2C1;
	NAU7802.mode = I2C_Fast_Mode;
	I2C_Master_Init(NAU7802);
	//reset,
	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_PU_CTRL, 0x01);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_PU_CTRL, 0x02);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_PU_CTRL, 0xAE);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_CTRL1, 0x20);
	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802, nau7802_address, 22, 0x30);
	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802, NAU7802_PGA, 21, (NAU7802_PGA_CHP_DIS | (1 << 5)));
//	Delay_ms(1);
	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_PU_CTRL, 0xbe);
	Delay_ms(1);


//	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_CTRL1, 0xA2);
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_CTRL2, 0x84);
//	Delay_ms(200);
//	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_ADC, 0x30);
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802, nau7802_address, NAU7802_PGA_PWR, NAU7802_PGA_PWR_PGA_CAP_EN);
//	Delay_ms(1);
//	I2C_Master_Write_Register(NAU7802, nau7802_address, 0x1b, 0x01);

	while(1)
	{
//		Delay_ms(100);
//		I2C_Master_Read_Register(NAU7802, nau7802_address, 0x00);
//		Delay_ms(1);
//		I2C_Master_Read_Register(NAU7802, nau7802_address, 0x01);
//		Delay_ms(1);
//		I2C_Master_Read_Register(NAU7802, nau7802_address, 0x02);
//		Delay_ms(1);
//		I2C_Master_Read_Register(NAU7802, nau7802_address, 21);
//		Delay_ms(1);
//		I2C_Master_Read_Register(NAU7802, nau7802_address, 28);
//		Delay_ms(1);
//		printConsole(USART1, "********************************************************\r\n");
//		for(int i  = 0; i <= 31; i++ )
//		{

			a = I2C_Master_Read_Register(NAU7802, nau7802_address, 0x12);
//			printConsole(USART1, "%" PRId32 "\r\n",a);
//			Delay_ms(1);
			b = I2C_Master_Read_Register(NAU7802, nau7802_address, 0x13);
//			printConsole(USART1, "%" PRId32 "\r\n",b);
//			Delay_ms(1);
			c = I2C_Master_Read_Register(NAU7802, nau7802_address, 0x14);
//			printConsole(USART1, "%" PRId32 "\r\n",c);
//			Delay_ms(1);
			d = a << 16 | b << 8 | c << 0;
//			d = d - sf;
			printConsole(USART1, "%" PRId32 "\r\n",d);
//		}
//		printConsole(USART1, "********************************************************\r\n");
//		Delay_ms(1000);
//		sf = d;


	}
}
