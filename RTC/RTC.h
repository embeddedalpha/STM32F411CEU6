/*
 * RTC.h
 *
 *  Created on: Oct 18, 2021
 *      Author: Kunal
 */

#ifndef RTC_RTC_H_
#define RTC_RTC_H_

#include "main.h"

#define Time_Format_24Hour	0
#define Time_Format_12Hour	1

#define Monday 		1
#define Tuesday 	2
#define Wednesday 	3
#define Thurday 	4
#define Friday 		5
#define Saturday	6
#define Sunday 		7

#define	January		1
#define	February	2
#define	March		3
#define	April		4
#define	May			5
#define	June		6
#define	July		7
#define	August		8
#define	September	9
#define	October		10
#define	November	11
#define	December	12

typedef struct RTC_Date{
	int day;
	int month;
	int year;
	int week_day;
}RTC_Date;

typedef struct RTC_Time{
	int am_pm;
	int hour;
	int min;
	int seconds;
	int milliseconds;
}RTC_Time;



void RTC_Init(void);
void RTC_Set_Time(RTC_Time *T, int time_format);
void RTC_Set_Date(RTC_Date *D);
void RTC_Start(void);

void RTC_Get_Time(RTC_Time *T);
void RTC_Get_Date(RTC_Date *D);


#endif /* RTC_RTC_H_ */
