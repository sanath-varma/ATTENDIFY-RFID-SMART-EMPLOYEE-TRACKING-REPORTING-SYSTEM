#include"types.h"
#include<LPC21xx.h>
void cfgPortPinFunc(u32 PortNo,u32 PinNo,u32 PinFunc)
{
if(PortNo==0)
{
if(PinNo<=15)
{
PINSEL0=((PINSEL0&~(3<<(PinNo*2)))|(PinFunc<<(PinNo*2)));
}
else if(PinNo>=16&&PinNo<=31)
{
PINSEL1=((PINSEL1&~(3<<((PinNo-16)*2)))|(PinFunc<<((PinNo-16)*2)));
}
}
else if(PortNo==1)
{
if(PinNo>=16&&PinNo<=31)
{
PINSEL2=((PINSEL2&~(3<<((PinNo-16)*2)))|(PinFunc<<((PinNo-16)*2))) ;
}
}
}
