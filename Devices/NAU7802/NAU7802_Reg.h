/*
 * NAU7802_Reg.h
 *
 *  Created on: 25-Oct-2021
 *      Author: Kunal
 */

#ifndef NAU7820_NAU7802_REG_H_
#define NAU7820_NAU7802_REG_H_

//________________________________________________________________________________________________________________
//      Name	|    Address   | Bit7	| Bit6	| Bit5	| Bit4	| Bit3	| Bit2	| Bit1	| Bit0	| Default
//______________|______________|________|_______|_______|_______|_______|_______|_______|_______|_________________
#define	PU_CTRL		0x00	//	AVDDS	 OSCS	    CR	    CS	    PUR	    PUA	    PUD	    RR	    0x00
#define	CTRL1		0x01	//	CRP		 VLDO[2:0]                          GAINS[2:0]              0x00
#define	CTRL2		0x02	//	CHS		 CRS[1:0]                           CALS    CALMOD[1:0]     0x00
//________________________________________________________________________________________________________________
#define	OCAL1_B2	0x03	//	CH1 OFFSET Calibration[23:16]                                       0x00
#define	OCAL1_B1	0x04	//	CH1 OFFSET Calibration[15:8]                                        0x00
#define	OCAL1_B0	0x05	//	CH1 OFFSET Calibration[7:0]                                         0x00
#define	GCAL1_B3	0x06	//	CH1 GAIN Calibration[31:24]                                         0x00
#define	GCAL1_B2	0x07	//	CH1 GAIN Calibration[23:16]                                         0x80
#define	GCAL1_B1	0x08	//	CH1 GAIN Calibration[15:8]                                          0x00
#define	GCAL1_B0	0x09	//	CH1 GAIN Calibration[7:0]                                           0x00
#define	OCAL2_B2	0x0A	//	CH2 OFFSET Calibration[23:16]                                       0x00
#define	OCAL2_B1	0x0B	//	CH2 OFFSET Calibration[15:8]                                        0x00
#define	OCAL2_B0	0x0C	//	CH2 OFFSET Calibration[7:0]                                         0x00
#define	GCAL2_B3	0x0D	//	CH2 GAIN Calibration[31:24]                                         0x00
#define	GCAL2_B2	0x0E	//	CH2 GAIN Calibration[23:16]                                         0x80
#define	GCAL2_B1	0x0F	//	CH2 GAIN Calibration[15:8]                                          0x00
#define	GCAL2_B0	0x10	//	CH2 GAIN Calibration[7:0]                                           0x00
#define	I2C Control	0x11	//	CRSD	FDR	SPE/WPD		SI	BOPGA	TS / BGPCP                      0x00
#define	ADCO_B2		0x12	//	ADC_OUT[23:16]                                                      RO
#define	ADCO_B1		0x13	//	ADC_OUT[15:8]                                                       RO
#define	ADCO_B0		0x14	//	ADC_OUT[7:0]                                                        RO
#define	OTP_B1		0x15	//	OTP[15:8]                                                           RO
#define	OTP_B0		0x16	//	OTP[7:0]                                                            RO
#define	DEVICE_REV	0x1F	//	Device Revision Code                                                RO


#endif /* NAU7820_NAU7802_REG_H_ */
