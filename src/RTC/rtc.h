#ifndef RTC_H
#define RTC_H
#include<LPC21xx.h>
#include"types.h"
#include"lcd_defines.h"
#include"delay.h"
#include"lcd.h"
#include"kpm.h"
//char week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
//extern char week_day[][10];
void RTC_Init(void);
void GetRTCTimeInfo(s32 *,s32 *,s32 *);
void DisplayRTCTime(u32,u32,u32);
void GetRTCDateInfo(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);

void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);

void GetRTCDay(s32 *);
void DisplayRTCDay(u32);
void SetRTCDay(u32);
void ReadNum(u32 *num,u32 *lastKey);
//logic
void PrintMenu(void);
void EditTime(void);
void Hour_Set(void);
void Min_Set(void);
void Sec_Set(void);
void Date_Day(void);
void Date(void);
void Day_Set(void);
void Month_Set(void);
void Year_Set(void);
void Day_set(void);


#endif

