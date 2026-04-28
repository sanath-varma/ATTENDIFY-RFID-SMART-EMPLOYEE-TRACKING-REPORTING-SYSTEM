#include<LPC21xx.h>
#include"types.h"
#include"lcd_defines.h"
#include"lcd.h"
#include"delay.h"
#include"rtc.h"
#include"kpm.h"
#include"uart1.h"
#include"uart1_function.h"
#include"gen_uart_defines.h"
#include"gen_uart_functions.h"
#include"SPI_defines.h"
#include"SPI_functions.h"
#include<string.h>

#include <ctype.h>
void Admin_Change(void);
void change_admin(void);
char check_admin(char *ID);
void admin(void);
void user(void);
void frame(char *frame, char *ID, char *purpose);
int string_len(char *ptr);

void Capitalize_String(char *ptr);

void LCD_SCROLL(char *str, int row, int dir);
