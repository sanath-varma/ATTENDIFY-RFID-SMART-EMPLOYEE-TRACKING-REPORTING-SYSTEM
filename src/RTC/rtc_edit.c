#include"rtc.h"
#include"kpm.h"
char week_day[][10]={"SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};
s32 Hour,Min,Sec,Day,Month,Year,flag=0;
void PrintMenu(void)
{
	u8 digit=0;
	Start:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.E.TIME");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2.DATE");
	CmdLCD(GOTO_LINE2_POS0+10);
	StrLCD("3.EXIT");
	while(1)
	{
		digit=KeyScan();
		if(digit!='\0')
		{
			switch(digit)
			{
				case'1':EditTime();
					    CmdLCD(CLEAR_LCD);
						goto Start;
				case'2':Date_Day();
				        CmdLCD(CLEAR_LCD);
				        goto Start;
				case'3'://CmdLCD(CLEAR_LCD);
						return;
				        
			}
		}
	}

}
void EditTime(void)
{
	u8 digit1;
	begin:CmdLCD(CLEAR_LCD);
	StrLCD("1.HR 2.MI 3.SE");
	CmdLCD(GOTO_LINE2_POS0+2);
	if(HOUR<=9)
	{
		CharLCD('0');
	}
	U32LCD(HOUR);
	CmdLCD(GOTO_LINE2_POS0+7);
	if(MIN<=9)
	{
		CharLCD('0');
	}
	U32LCD(MIN);
	CmdLCD(GOTO_LINE2_POS0+12);
	if(SEC<=9)
	{
		CharLCD('0');
	}
	U32LCD(SEC);
	
	while(1)
	{
	digit1=KeyScan();
	if(digit1 != '\0')
	{
	switch(digit1)
	{
	case'1':Hour_Set();
		    CmdLCD(CLEAR_LCD);
			StrLCD("HOUR UPDATED!");
			delay_ms(500);
		     goto begin;
	case'2':Min_Set();
					CmdLCD(CLEAR_LCD);
					StrLCD("MINUTE UPDATED!");
					delay_ms(500);
			    goto begin;
	case'3':Sec_Set();
					CmdLCD(CLEAR_LCD);
					StrLCD("SECONDS UPDATED!");
					delay_ms(500);
	        goto begin;
	case'4':CmdLCD(CLEAR_LCD);
		      return;
	}
	}
	}
	}
void Date(void)
{
	u8 date;
	begin:CmdLCD(CLEAR_LCD);
	StrLCD("1.DD 2.MM 3.YYYY");
	CmdLCD(GOTO_LINE2_POS0+2);
	if(DOM<=9)
	{
		CharLCD('0');
	}
	U32LCD(DOM);
	CmdLCD(GOTO_LINE2_POS0+7);
	if(MONTH==0)
	{
		StrLCD("00");
	}
	else if((MONTH>0)&&(MONTH<=9))
	{
		CharLCD('0');
		CmdLCD(GOTO_LINE2_POS0+8);
		U32LCD(MONTH);
	}
	else
	U32LCD(MONTH);
	CmdLCD(GOTO_LINE2_POS0+12);
	if(YEAR>=1000&&YEAR<=4095)
	{
		U32LCD(YEAR);
	}
	if(YEAR>=100&&YEAR<=999)
	{
		CmdLCD(GOTO_LINE2_POS0+12);
		CharLCD('0');
		U32LCD(YEAR);
	}
	if(YEAR>=10&&YEAR<=99)
	{
		CmdLCD(GOTO_LINE2_POS0+12);
		CharLCD('0');
		CmdLCD(GOTO_LINE2_POS0+13);
		CharLCD('0');
		U32LCD(YEAR);
	}
	if(YEAR<=9)
	{
		CmdLCD(GOTO_LINE2_POS0+12);
		CharLCD('0');
		CmdLCD(GOTO_LINE2_POS0+13);
		CharLCD('0');
		CmdLCD(GOTO_LINE2_POS0+14);
		CharLCD('0');
		U32LCD(YEAR);
	}
	while(1)
	{
	date=KeyScan();
	if(date!='\0')
	{
	switch(date)
	{
	case'1':Day_Set();
					CmdLCD(CLEAR_LCD);
					StrLCD("DATE UPDATED!");
					delay_ms(500);
		      goto begin;
	case'2':Month_Set();
					CmdLCD(CLEAR_LCD);
					StrLCD("MONTH UPDATED!");
					delay_ms(500);
		      goto begin;
	case'3':Year_Set();
					CmdLCD(CLEAR_LCD);
					StrLCD("YEAR UPDATED!");
					delay_ms(500);
		      goto begin;
	case'4':CmdLCD(CLEAR_LCD);
					return;
		
	}
}
}	
}
void Hour_Set(void)
{
	u8 digit1;
	start:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0+2);
	StrLCD("HH");
	CmdLCD(GOTO_LINE2_POS0+2);
	while(1)
	{
	IN:digit1=KeyScan();
	if((digit1!='\0')&&(digit1!='B'))
	{
	if(((digit1-48)<=9)&&(digit1!='*'))
	{
	CharLCD(digit1);
	Hour=digit1-48;
	break;
	}
	}
	} 
  while(1)
	{
	HE:digit1=KeyScan();
	if(digit1!='\0')
	{
	if(digit1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+2);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+2);
	Hour=0;
	goto IN;
	}
	if(digit1 == 'A')
	{
	HOUR=Hour;
	return;
	}
	CmdLCD(GOTO_LINE2_POS0+3);
	CharLCD(digit1);
	Hour=(Hour*10)+(digit1-48);
	break;
	}
	}
  while(1)
	{
	digit1=KeyScan();
	if(digit1!='\0')
	{
	if(digit1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+3);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+3);
	Hour=Hour/10;
	goto HE;
	}
	if(digit1 == 'A')
	{
	if(Hour>=0&&Hour<=23)
	{
	HOUR=Hour;
	return;
	}
	else	
	{
	CmdLCD(CLEAR_LCD);
	StrLCD("INVALID HOUR");
	delay_ms(500);
	goto start;
	}
	}
	}
	}
}
void Min_Set(void)
{
	u8 digit1;
	start:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0+2);
	StrLCD("HH");
	CmdLCD(GOTO_LINE2_POS0+2);
	if(Hour <= 9){
		CharLCD('0');
		U32LCD(Hour);
	}
	else{
		U32LCD(Hour);
	}
	CmdLCD(GOTO_LINE1_POS0+7);
	StrLCD("MI");
	CmdLCD(GOTO_LINE2_POS0+7);
	while(1)
	{
		Here:digit1=KeyScan();
		if((digit1!='\0')&&(digit1!='B'))
		{
		if(((digit1-48)<=9)&&(digit1!='*'))
		{
		CharLCD(digit1);
        Min=digit1-48;
		break;
		}
		}
	}
	while(1)
	{
	Begin:digit1=KeyScan();
	if(digit1!='\0')
	{
	if(digit1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+7);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+7);
	Min=0;
	goto Here;
	}
	if(digit1 == 'A')
	{
	MIN=Min;
	return;
	}
	CmdLCD(GOTO_LINE2_POS0+8);
	CharLCD(digit1);
	Min=(Min*10)+(digit1-48);
	break;
	}
	}
	while(1)
	{
	digit1=KeyScan();
	if(digit1!='\0')
	{
	if(digit1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+8);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+8);
	Min=Min/10;
	goto Begin;
	}
	if(digit1 == 'A')
	{
	if(Min>=0&&Min<=59)
	{
	MIN=Min;
	return;
	}
	else	
	{
	CmdLCD(CLEAR_LCD);
	StrLCD("INVALID MINUTE");
	delay_ms(500);
	goto start;
	}
	}
	}
	}
}
void Sec_Set(void)
{
u8 digit1;
start:CmdLCD(CLEAR_LCD);
CmdLCD(GOTO_LINE1_POS0+2);
StrLCD("HR");
CmdLCD(GOTO_LINE2_POS0+2);
if(Hour <= 9){
		CharLCD('0');
		U32LCD(Hour);
	}
	else{
		U32LCD(Hour);
	}
CmdLCD(GOTO_LINE1_POS0+7);
StrLCD("MI");
CmdLCD(GOTO_LINE2_POS0+7);
if(Min  <= 9){
		CharLCD('0');
		U32LCD(Min);
	}
	else{
		U32LCD(Min);
	}
CmdLCD(GOTO_LINE1_POS0+12);
StrLCD("SE");
CmdLCD(GOTO_LINE2_POS0+12);
while(1)
{
last:digit1=KeyScan();
if((digit1!='\0')&&(digit1!='B'))
{
if(((digit1-48)<=9)&&(digit1!='*'))
CharLCD(digit1);
Sec=digit1-48;
break;
}
}
while(1)
{
Last:digit1=KeyScan();
if(digit1!='\0')
{
if(digit1=='B')
{
CmdLCD(GOTO_LINE2_POS0+12);
CharLCD(' ');
CmdLCD(GOTO_LINE2_POS0+12);
Sec=0;
goto last;
}
if(digit1 == 'A')
{
SEC=Sec;
return;
}
CmdLCD(GOTO_LINE2_POS0+13);
CharLCD(digit1);
Sec=(Sec*10)+(digit1-48);
break;
}
}
while(1)
{
digit1=KeyScan();
if(digit1!='\0')
{
if(digit1=='B')
{
CmdLCD(GOTO_LINE2_POS0+13);
CharLCD(' ');
CmdLCD(GOTO_LINE2_POS0+13);
Sec=Sec/10;
goto Last;
}
if(digit1 == 'A')
{
if(Sec>=0&&Sec<=59)
{
SEC=Sec;
return;
}
else	
{
CmdLCD(CLEAR_LCD);
StrLCD("INVALID SECOND");
delay_ms(500);
goto start;
}
}
}
}
}
void Day_Set(void)
{
	u8 date;
	start:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0+2);
	StrLCD("DD");
	CmdLCD(GOTO_LINE2_POS0+2);
	while(1)
	{
	IN:date=KeyScan();
	if((date>=49)&&(date<=57))
	{
	CharLCD(date);
	Day=date-48;
	break;
	}
	else
	{
		goto IN;
	}
	}
  while(1)
	{
	HE:date=KeyScan();
	if(date!='\0')
	{
	if(date=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+2);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+2);
	Day=0;
	goto IN;
	}
	if(date == 'A')
	{
	DOM=Day;
	return;
	}
	CmdLCD(GOTO_LINE2_POS0+3);
	CharLCD(date);
	Day=(Day*10)+(date-48);
	break;
	}
	}
	while(1)
	{
	date=KeyScan();
	if(date!='\0')
	{
	if(date=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+3);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+3);
	Day=Day/10;
	goto HE;
	}
	if(date == 'A')
	{
	if(Day>=0&&Day<=31)
	{
	DOM=Day;
	return;
	}
	else	
	{
	CmdLCD(CLEAR_LCD);
	StrLCD("INVALID DAY");
	delay_ms(500);
	goto start;
	}
	}
	}
	}
}
void Month_Set(void)
{
	u8 date;
	start:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0+2);
	StrLCD("DD");
	CmdLCD(GOTO_LINE2_POS0+2);
	if(Day <= 9){
		CharLCD('0');
		U32LCD(Day);
	}
	else{
		U32LCD(Day);
	}
	CmdLCD(GOTO_LINE1_POS0+7);
	StrLCD("MM");
	CmdLCD(GOTO_LINE2_POS0+7);
	while(1)
	{
		Here:date=KeyScan();
		if((date>=49)&&(date<=57))
		{
			CharLCD(date);
      Month=date-48;
			break;
		}
		else
		{
			goto Here;
		}
	}
	while(1)
	{
		Begin:date=KeyScan();
		if(date!='\0')
		{
		if(date=='B')
		{
		CmdLCD(GOTO_LINE2_POS0+7);
		CharLCD(' ');
		CmdLCD(GOTO_LINE2_POS0+7);
		Month=0;
		goto Here;
		}
		if(date == 'A')
		{
		MONTH=Month;
		return;
    }
		CmdLCD(GOTO_LINE2_POS0+8);
		CharLCD(date);
		Month=(Month*10)+(date-48);
		break;
		}
  }
  while(1)
	{
		date=KeyScan();
		if(date!='\0')
		{
		if(date=='B')
		{
		CmdLCD(GOTO_LINE2_POS0+8);
		CharLCD(' ');
		CmdLCD(GOTO_LINE2_POS0+8);
		Month=Month/10;
		goto Begin;
		}
		if(date == 'A')
		{
		if(Month>=0&&Month<=12)
		{
		MONTH=Month;
		return;
		}
		else	
		{
		CmdLCD(CLEAR_LCD);
	  StrLCD("INVALID MONTH");
		delay_ms(1000);
		goto start;
		}
		}
		}
		}
}
void Year_Set(void)
{
	u8 year1;
	Temp:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0+2);
	StrLCD("DD");
	CmdLCD(GOTO_LINE2_POS0+2);
	if(Day <= 9){
		CharLCD('0');
		U32LCD(Day);
	}
	else{
		U32LCD(Day);
	}
	CmdLCD(GOTO_LINE1_POS0+7);
	StrLCD("MM");
	CmdLCD(GOTO_LINE2_POS0+7);
	if(Month <= 9){
		CharLCD('0');
		U32LCD(Month);
	}
	else{
		U32LCD(Month);
	}
  CmdLCD(GOTO_LINE1_POS0+12);
  StrLCD("YYYY");
  CmdLCD(GOTO_LINE2_POS0+12);
	while(1)
	{
		Last:year1=KeyScan();
		if((year1>=49)&&(year1<=57))
		{
			CharLCD(year1);
      Year=year1-48;
			break;
		}
		else
		{
			goto Last;
		}
	}
while(1)
{
	last:year1=KeyScan();
	if(year1!='\0')
	{
	if(year1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+12);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+12);
	Year=0;
	goto Last;
	}
	if(year1=='A')
	{
		YEAR=Year;
		return;
	}
	CmdLCD(GOTO_LINE2_POS0+13);
	CharLCD(year1);
	Year=(Year*10)+(year1-48);
	break;
	}
 }
while(1)
	{
		up:year1=KeyScan();
	if(year1!='\0')
	{
	if(year1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+13);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+13);
	Year=Year/10;
	goto last;
	}
	if(year1 == 'A')
	{
	YEAR=Year;
	return;
	}
	CmdLCD(GOTO_LINE2_POS0+14);
	CharLCD(year1);
	Year=(Year*10)+(year1-48);
	break;
	}
	}
	while(1)
	{
	start:year1=KeyScan();
	if(year1!='\0')
	{
	if(year1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+14);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+14);
	Year=Year/10;
	goto up;
	}
	if(year1 == 'A')
	{
	YEAR=Year;
	return;
	}
	CmdLCD(GOTO_LINE2_POS0+15);
	CharLCD(year1);
	Year=(Year*10)+(year1-48);
	break;
	}
	}
	while(1)
	{
	year1=KeyScan();
	if(year1!='\0')
	{
	if(year1=='B')
	{
	CmdLCD(GOTO_LINE2_POS0+15);
	CharLCD(' ');
	CmdLCD(GOTO_LINE2_POS0+15);
	Year=Year/10;
	goto start;
	}
	if(year1 == 'A')
	{
		if(Year<4096)
		{
	YEAR=Year;
		delay_ms(500);
	return;
		}
		else	
		{
		CmdLCD(CLEAR_LCD);
	  StrLCD("INVALID YEAR");
		delay_ms(1000);
		goto Temp;
		}
	}
	}
	}
	
}
void Date_Day(void)
{
	u8 date;
	begin:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.DATE");
	CmdLCD(GOTO_LINE1_POS0+7);
	StrLCD("2.DAY");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("3.EXIT");
	while(1)
	{
		date=KeyScan();
		if(date!='\0')
		{
			switch(date)
			{
				case'1':Date();
						CmdLCD(CLEAR_LCD);
						StrLCD("DATE UPDATED");
				        delay_ms(500);
						goto begin;
				case'2':Day_set();
						CmdLCD(CLEAR_LCD);
						goto begin;
				case'3':CmdLCD(CLEAR_LCD);
						return;
			}
		}
	}
}
void Day_set(void)
{
	s32 temp,temp2;
	Begin:CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("SELECT_DAY:");
	CmdLCD(GOTO_LINE1_POS0+11);
	while(1)
	{
	temp=KeyScan();
	if(temp!='\0')
	{
	temp2=temp-48;
	if(temp2<=6)
	{
		U32LCD(temp2);
		CmdLCD(GOTO_LINE2_POS0+7);
		StrLCD(week_day[temp2]);
	}
	break;
	}
	} 
	while(1)
	{
		temp=KeyScan();
		if(temp!='\0')
		{
	     if(temp=='B')
                {
                CmdLCD(GOTO_LINE1_POS0+11);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0+7);
                StrLCD("'          '");
                CmdLCD(GOTO_LINE1_POS0+11);
                goto Begin;
                }
                if(temp=='A')
                {
                if((temp2>=0)&&(temp2<=6))
                {
                DOW=temp2;
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0+5);
                StrLCD(week_day[DOW]);
                CmdLCD(GOTO_LINE2_POS0+5);
                StrLCD("SELECTED");
                delay_ms(500);
                return;
                }
                }

                }
        }
}

