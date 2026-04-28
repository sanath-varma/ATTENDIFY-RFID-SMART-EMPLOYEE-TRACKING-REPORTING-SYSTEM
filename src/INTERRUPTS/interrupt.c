#include"interrupt.h"
#include"admin.h"
void Intilisation(void)
{
	PINSEL1=0x15400001;
	VICIntEnable=1<<EINT0_CHNO;
	VICVectCntl0=(1<<5)|EINT0_CHNO;
	VICVectAddr0=(u32)eint0_isr;
	EXTMODE=1<<0;
}
void eint0_isr(void)__irq
{
	Admin_Change();
	EXTINT=1<<0;
	VICVectAddr=0;
}
