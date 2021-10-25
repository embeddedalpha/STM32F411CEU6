/*
 * NAU7802.c
 *
 *  Created on: 25-Oct-2021
 *      Author: Kunal
 */



static void NAU7802_Single_Write(uint8_t reg_address, uint8_t data);
static void NAU7802_Burst_Write(uint8_t reg_address, uint8_t *data);
static void NAU7802_Single_Read(uint8_t reg_address);
static void NAU7802_Burst_Read(uint8_t reg_address, uint8_t *data);
