#include "main.h"
#include "RTC/RTC.h"

int main()
{
	MCU_Clock_Setup();
	Console_Init(9600);
	Delay_Config();

	RTC_Time X;
	X.am_pm = 1;
	X.hour = 6;
	X.min = 00;
	X.seconds = 0;

	RTC_Date Y;
	Y.day = 18;
	Y.month = 10;
	Y.year = 2021;
	Y.week_day = Monday;

	RTC_Init();
	RTC_Set_Date(&Y);
	RTC_Set_Time(&X, Time_Format_12Hour);
	RTC_Start();


	while(1)
	{
		RTC_Get_Date(&Y);
		RTC_Get_Time(&X);
		printConsole("Date: %d/%d/%d \r\n",Y.day,Y.month,Y.year);
		printConsole("Time: %d:%d:%d \r\n", X.hour, X.min, X.seconds);
		Delay_s(1);
	}
}


