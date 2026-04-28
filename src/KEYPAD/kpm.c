#include<LPC21xx.h>
#include "kpm.h"
s8 KeyScan(void)
{
	s32 row,col;
       /* u8 key[4][4] = {
    {'7', '8', '9', 'A'},
    {'4', '5', '6', 'B'},
    {'1', '2', '3', 'C'},
    {'*', '0', '=', 'D'}
        };*/
		u8 key[4][4]={
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','=','D'}
		};
		IODIR1|=(0xF<<R1);
		IODIR1&= 0x0FFFFFFF;

		while(1){
				for(row = 0; row < ROWS; row++)
				{
					WRITENIBBLE(IOSET1,R1,0xF);
					CLRBIT(IOCLR1,(R1 + row));
					for(col = 0; col < COLS; col++)
					{
						if(!(IOPIN1 & (1 << (C1 + col))))
							{
								delay_us(50);
								if(!(IOPIN1 & (1 << (C1 + col))))
									{
										while(!(IOPIN1 & (1 << (C1 + col))));
										WRITENIBBLE(IOSET1,R1,0xF);
                    return key[row][col];
                   }
               }
           }
        }
		}
}
