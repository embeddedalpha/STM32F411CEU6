/*
 * INA260.h
 *
 *  Created on: 22-Sep-2021
 *      Author: Kunal
 */

#ifndef INA260_INA260_H_
#define INA260_INA260_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "I2C/I2C.h"

uint8_t INA260_Address;

struct I2C_Config INA280;

//Select one, comment out the rest
#define INA260_Address_0	0x40
#define INA260_Address_1	0x41
#define INA260_Address_2	0x42
#define INA260_Address_3	0x43
#define INA260_Address_4	0x44
#define INA260_Address_5	0x45
#define INA260_Address_6	0x46
#define INA260_Address_7	0x47
#define INA260_Address_8	0x48
#define INA260_Address_9	0x48
#define INA260_Address_10	0x4a
#define INA260_Address_11	0x4b
#define INA260_Address_12	0x4c
#define INA260_Address_13	0x4d
#define INA260_Address_14	0x4e
#define INA260_Address_15	0x4f

#define Power_Down_Mode_INA260	                            0 //SHUTDOWN MODE
#define Shunt_Current_Mode_TRIGGERED_INA260	                1 //SHUNT CURRENT TRIGGERED
#define Bus_Voltage_Mode_TRIGGERED_INA260	                  2 //BUS VOLTAGE TRIGGERED
#define Shunt_Voltage_and_Current_TRIGGERED_Mode_INA260	    3 //SHUNT CURRENT AND BUS VOLTAGE TRIGGERED

#define Shunt_Current_Continuous_Mode_INA260	              6 //SHUNT CURRENT
#define Bus_Voltage_Continuous_Mode_INA260	                7 //BUS VOLTAGE
#define Shunt_Voltage_and_Current_Continuous_Mode_INA260	  8 //SHUNT CURRENT AND BUS VOLTAGE

#define Configuration_Register_INA260                       0x00 //READ-WRITE
#define Current_Register_INA260                             0x01 //READ ONLY
#define Bus_Voltage_Register_INA260                         0x02 //READ ONLY
#define Power_Register_INA260                               0x03 //READ ONLY
#define Mask_Enable_Register_INA260                         0x06 //READ-WRITE
#define Alert_Limit_Register_INA260                         0x07 //READ-WRITE
#define Manufacturer_ID_Register_INA260                     0xFE //READ ONLY
#define Die_ID_Register_INA260                              0xFF //READ ONLY


void INA260_Init(I2C_TypeDef *I2C);

void INA260_Mode(uint8_t mode);

float INA260_Get_Temp(void);

float INA260_Get_Current(void);

float INA260_Get_Voltage(void);

float INA260_Get_Power(void);


#endif /* INA260_INA260_H_ */

