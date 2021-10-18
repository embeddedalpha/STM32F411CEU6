/*
 * RTC.c
 *
 *  Created on: Oct 18, 2021
 *      Author: Kunal
 */


#include "RTC.h"



void RTC_Init(void)
{
	PWR -> CR |= PWR_CR_DBP;
	RCC -> CFGR |= 25 << 16;
	RCC -> BDCR |= RCC_BDCR_RTCSEL;
	RCC -> BDCR |= RCC_BDCR_RTCEN;
	RTC -> WPR = 0xCA;
	RTC -> WPR = 0x53; //DISABLE RTC WRITE PROTECT
	RTC -> ISR |= RTC_ISR_INIT; //INITIALIZE RTC
	while(!(RTC -> ISR & RTC_ISR_INITF)); //WAIT
	RTC -> PRER = 0x00000000;
	RTC -> PRER = 0x7C << 16;
	RTC -> PRER |= 0x1F3F << 0;
}

void RTC_Set_Time(RTC_Time *T, int time_format)
{
	int ht,hu,mt,mu,st,su;
	uint32_t t;
	ht = T->hour / 10;
	hu = T->hour % 10;
	mt = T->min / 10;
	mu = T->min % 10;
	st = T->seconds / 10;
	su = T->seconds % 10;
	t = ht << 20 | hu << 16 | mt << 12 | mu << 8 | st << 4 | su << 0;
	RTC -> TR = t ;// time
}


void RTC_Set_Date(RTC_Date *D)
{
	int yt,yu,wd,mt,mu,dt,du;
	uint32_t d;
	D->year = D -> year - 2000;
	yt = D->year / 10;
	yu = D->year % 10;

	wd = D->week_day;

	mt = D->month / 10;
	mu = D->month % 10;

	dt = D->day / 10;
	du = D->day % 10;

	d = yt << 20 | yu << 16 | wd << 13 | mt << 12 | mu << 8 | dt << 4 | du << 0;
	RTC -> DR = d ;// time

}
void RTC_Start(void)
{
	RTC -> CR |= RTC_CR_FMT | RTC_CR_TSE; //Configure the time format
	RTC -> ISR &= ~RTC_ISR_INIT; //Exit initialization mode.
	RTC -> WPR = 0xFF;
	PWR -> CR &= ~PWR_CR_DBP;
}

void RTC_Get_Time(RTC_Time *T)
{
	uint32_t t;
	int hour_tens, hour_unit;
	int mins_tens, mins_unit;
	int second_tens, second_unit;
	int seconds, mins, hour;

	t = RTC -> TR;
	hour_tens = (t & 0x300000)>>20;
	hour_unit = (t & 0xF0000)>>16;
	mins_tens = (t & 0x7000)>>12;
	mins_unit = (t & 0xf00) >> 8;
	second_tens = (t & 0x70) >> 4;
	second_unit = (t & 0xf);
	hour = (hour_tens * 10) + hour_unit;
	mins = (mins_tens * 10) + mins_unit;
	seconds = (second_tens * 10) + second_unit;
	T->hour = hour;
	T->min = mins;
	T->seconds = seconds;
}



void RTC_Get_Date(RTC_Date *D)
{
	uint32_t d;
	int date, datet, dateu;
	int month,montht,monthu;
	int year,yeart,yearu;
	int wd;

	d = RTC -> DR;

	yeart = (d & 0xf00000) >> 20;
	yearu = (d & 0xf0000) >> 16;
	year = 2000 + (yeart * 10) + yearu;

	montht = (d & 0x1000) >> 12;
	monthu = (d & 0xf00) >> 12;
	month = (montht * 10) + monthu;

	datet = (d & 0x30) >> 4;
	dateu = (d & 0xf) >> 0;
	date = (datet * 10) + dateu;

D -> day = date;
D -> month = month;
D -> year = year;
}
