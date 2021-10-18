# RTC


```C
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

```

```C
void RTC_Init(void);
void RTC_Set_Time(RTC_Time *T, int time_format);
void RTC_Set_Date(RTC_Date *D);
void RTC_Start(void);
void RTC_Get_Time(RTC_Time *T);
void RTC_Get_Date(RTC_Date *D);
```
