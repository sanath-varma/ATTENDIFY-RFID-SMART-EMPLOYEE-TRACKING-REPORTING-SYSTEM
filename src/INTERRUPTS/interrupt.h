#include<Lpc21xx.h>
#include"types.h"
#include"admin.h"
#define EINT0_CHNO 14
void Intilisation(void);
void eint0_isr(void)__irq;
//void Admin_Change(void);
