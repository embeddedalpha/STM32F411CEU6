/*
 * QH32x_Flash_Commands.h
 *
 *  Created on: 05-Oct-2021
 *      Author: Kunal
 */

#ifndef QH32X_FLASH_QH32X_FLASH_COMMANDS_H_
#define QH32X_FLASH_QH32X_FLASH_COMMANDS_H_


#define Write_Enable              0x06
#define Write_Disable             0x04
#define Read_Status_Register_1    0x05   //(S7–S0) (2)
#define Read_Status_Register_2    0x35   //(S15-S8) (2)
#define Write_Status_Register     0x01   //(S7–S0) (S15-S8)
#define Page_Program              0x02   //A23–A16 A15–A8 A7–A0 (D7–D0)
#define Quad_Page Program         0x32   //A23–A16 A15–A8 A7–A0 (D7–D0, …)(3)
#define Block_Erase_64K           0xD8   // A23–A16 A15–A8 A7–A0 (64KB)
#define Block_Erase_32K           0x52   // A23–A16 A15–A8 A7–A0 (32KB)
#define Sector_Erase              0x20   //A23–A16 A15–A8 A7–A0 (4KB)
#define Chip_Erase                0xC7
#define Erase_Suspend             0x75
#define Erase_Resume 			  0x7A
#define Power_down 				  0xB9
#define High_Performance_Mode     0xA3   //dummy dummy dummy
#define Mode_Bit_Reset            0xFF   //FFh
#define Release_Power_Down	      0xAB   //dummy dummy dummy (ID7-ID0) (5)
#define Manufacturer_Device_ID    0x90   //dummy dummy 00h (M7-M0) (ID7-ID0)
#define Read_Unique_ID            0x4B   //dummy dummy dummy Dummy (ID63-ID0)
#define JEDEC_ID                  0x9F   //(M7-M0) Manufacturer (ID15-ID8) Memory Type (ID7-ID0) Capacity
#define Read_Data 				  0x03h //A23–A16 A15–A8 A7–A0 (D7–D0)
#define Fast_Read                 0x0Bh //A23–A16 A15–A8 A7–A0 dummy (D7–D0)
#define Fast_Read_Dual_Output     0x3Bh //A23–A16 A15–A8 A7–A0 dummy (D7–D0, …)(1)
#define Fast_Read_Dual_IO         0xBBh //A23-A8(2) A7-A0, M7-M0(2) (D7–D0, …)(1)
#define Fast_Read_Quad_Output     0x6Bh //A23–A16 A15–A8 A7–A0 dummy (D7–D0, …)(3)
#define Fast_Read_Quad_IO         0xEBh //A23-A0, M7-M0(4) (x,x,x,x, D7–D0, …)(5) (D7-D0, …)(3

#endif /* QH32X_FLASH_QH32X_FLASH_COMMANDS_H_ */
