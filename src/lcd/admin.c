#include"admin.h"
#define LCD 16
#define LEFT 0

#define RIGHT 1
u8 digit=0;
extern s8 DATA_FRAME[30];
extern s8 UART1_BUFFER[15];
extern u8 UART0_BYTE;
extern u32 UART0_Fired;
extern u32 UART1_Fired;
s8 UART0_BUFFER[25];
int IN;
char response;
void Admin_Change(void)
{   CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0+1);
	StrLCD("Admin Change");
	delay_ms(500);
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.ADMIN CHANGE");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2.E.RTC");
	CmdLCD(GOTO_LINE2_POS0+10);
	StrLCD("3.EXIT");
while(1)
{
	digit=KeyScan();
		if(digit!='\0')
		{
			switch(digit)
			{
				case'1':change_admin();
					     CmdLCD(CLEAR_LCD);
						 return;
				case'2': PrintMenu();
						CmdLCD(CLEAR_LCD);
						return;
				case'3':CmdLCD(CLEAR_LCD);
								return;
				        
			}
    }
}
}
void change_admin(void){
	char new_admin_id[12];
	char old_admin_id[10];
	char key;
	CmdLCD(CLEAR_LCD);
	StrLCD(" TAP NEW ADMIN");
	CmdLCD(GOTO_LINE2_POS0 + 5);
	StrLCD("CARD");
	Receive_string_UART1(new_admin_id, 10);
	ExtractRFID(new_admin_id);
	Receive_string_from_EEPROM(old_admin_id, 8, 0x0000);

	
	if(!(strcmp(new_admin_id, old_admin_id))){
		CmdLCD(CLEAR_LCD);
		StrLCD("ADMIN ID DETAILS");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("ALREADY EXISTED!");
		delay_ms(500);
	}
	else{
		CmdLCD(CLEAR_LCD);
		StrLCD(" PRESS ANY KEY");
		CmdLCD(GOTO_LINE2_POS0 + 3);
		StrLCD("TO CONFIRM");
		key = KeyScan();
		key = key;            // To eliminate Warning Message
		Write_string_to_EEPROM(new_admin_id, 0x0000);
		CmdLCD(CLEAR_LCD);
		StrLCD("  NEW ADMIN ID");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("    UPDATED");
		delay_ms(500);
	}
}

char check_admin(char *ID){
	char old_admin_id[10];
	Receive_string_from_EEPROM(old_admin_id, 8, 0x0000);
	if(!(strcmp(ID, old_admin_id))){
		return 'A';
	}
	else{
		return 'B';
	}
}

void admin(void){

	char key, response;

	int timeout = 6000000, display = 0;

	CmdLCD(CLEAR_LCD);

	StrLCD("1.ADD      2.DEL");

	CmdLCD(GOTO_LINE2_POS0);

	StrLCD("3.EDIT    4.EXIT");

	key = KeyScan();

	switch(key){

		case '1':	CmdLCD(CLEAR_LCD);

							StrLCD("  TAP NEW CARD");

							Receive_string_UART1(UART1_BUFFER, 10);

							CmdLCD(CLEAR_LCD);

							StrLCD("  CARD  TAPPED");

							delay_ms(500);      // kept for synchronization purpose

							ExtractRFID(UART1_BUFFER);

							frame(DATA_FRAME, UART1_BUFFER, "ADD");


							Transmit_string_UART0(DATA_FRAME);


							while(1){

								timeout--;

								if(UART0_Fired){

									UART0_Fired = 0;

									response = UART0_BYTE;

								}

								if((response == 'Y') || (response == 'y')){

									//Receive_string_UART0(UART0_BUFFER, 20);

									//Capitalize_String(UART0_BUFFER);

									CmdLCD(CLEAR_LCD);
									CmdLCD(GOTO_LINE1_POS0);
									//StrLCD(UART0_BUFFER);

								//	LCD_SCROLL(UART0_BUFFER, 0, 0);

									//CmdLCD(GOTO_LINE2_POS0);

									StrLCD("  USER ADDED");

									delay_ms(2000);

									break;

								}

								else if((response == 'N') || (response == 'n')){

									 CmdLCD(CLEAR_LCD);
									 CmdLCD(GOTO_LINE1_POS0);
									 //StrLCD(UART0_BUFFER);
								//	LCD_SCROLL(UART0_BUFFER, 0, 0);
								//	CmdLCD(GOTO_LINE2_POS0);
									StrLCD("  USER EXISTED");

									delay_ms(2000);

									break;

								}

								if(!timeout){

									timeout = 6000000;

									if(!display){

										display = 1;

										CmdLCD(CLEAR_LCD);

										StrLCD(" WAITING FOR OS");

										CmdLCD(GOTO_LINE2_POS0);

										StrLCD("   TO RESPOND");

									}

									else{

										display = 0;

										CmdLCD(CLEAR_LCD);

										StrLCD(" PLEASE WAIT...");

									}

								}

							}

							break;

		case '2':	CmdLCD(CLEAR_LCD);

							StrLCD("  TAP USERCARD");

							Receive_string_UART1(UART1_BUFFER, 10);

							CmdLCD(CLEAR_LCD) ;

							StrLCD("  CARD  TAPPED");

							delay_ms(500);      // kept for synchronization purpose

							ExtractRFID(UART1_BUFFER);

							frame(DATA_FRAME, UART1_BUFFER, "DEL");

							Transmit_string_UART0(DATA_FRAME);

							while(1){

								timeout--;

								if(UART0_Fired){

									UART0_Fired = 0;

									response = UART0_BYTE;

								}

								if((response == 'Y') || (response == 'y')){

									//Receive_string_UART0(UART0_BUFFER, 20);

								//	Capitalize_String(UART0_BUFFER);

									 CmdLCD(CLEAR_LCD);
									 CmdLCD(GOTO_LINE1_POS0);
									// StrLCD(UART0_BUFFER);
									//LCD_SCROLL(UART0_BUFFER, 0, 0);
									//CmdLCD(GOTO_LINE2_POS0);

									StrLCD("  USER DELETED");

									delay_ms(2000);

									break;

								}

								else if((response == 'N') || (response == 'n')){

									CmdLCD(CLEAR_LCD);

									StrLCD("USER NOT EXISTED");

									delay_ms(2000);

									break;

								}

								if(!timeout){

									timeout = 6000000;

									if(!display){

										display = 1;

										CmdLCD(CLEAR_LCD);

										StrLCD(" WAITING FOR OS");

										CmdLCD(GOTO_LINE2_POS0);

										StrLCD("   TO RESPOND");

									}

									else{

										display = 0;

										CmdLCD(CLEAR_LCD);

										StrLCD(" PLEASE WAIT...");

									}

								}

							}

							break;

		case '3':	CmdLCD(CLEAR_LCD);

							StrLCD("  TAP USERCARD");

							Receive_string_UART1(UART1_BUFFER, 10);

							CmdLCD(CLEAR_LCD);

							StrLCD("  CARD  TAPPED");

							delay_ms(500);      // kept for synchronization purpose

							ExtractRFID(UART1_BUFFER);

							frame(DATA_FRAME, UART1_BUFFER, "EDT");

							Transmit_string_UART0(DATA_FRAME);

							while(1){

								timeout--;

								if(UART0_Fired){

									UART0_Fired = 0;

									response = UART0_BYTE;

								}

								if((response == 'Y') || (response == 'y')){

									//Receive_string_UART0(UART0_BUFFER, 20);

									//Capitalize_String(UART0_BUFFER);

									 CmdLCD(CLEAR_LCD);
									 CmdLCD(GOTO_LINE1_POS0);
									 //StrLCD(UART0_BUFFER);
									//LCD_SCROLL(UART0_BUFFER, 0, 0);
									//CmdLCD(GOTO_LINE2_POS0);

									StrLCD("  USER  EDITED");

									delay_ms(2000);

									break;

								}

								else if((response == 'N') || (response == 'n')){

									CmdLCD(CLEAR_LCD);

									StrLCD("USER NOT EXISTED");

									delay_ms(2000);

									break;

								}

								if(!timeout){

									timeout = 6000000;

									if(!display){

										display = 1;

										CmdLCD(CLEAR_LCD);

										StrLCD(" WAITING FOR OS");

										CmdLCD(GOTO_LINE2_POS0);

										StrLCD("   TO RESPOND");

									}

									else{

										display = 0;

										CmdLCD(CLEAR_LCD);

										StrLCD(" PLEASE WAIT...");

									}

								}

							}

							break;

		case '#': return;

		case '4':	return;

	}

}

/*void user(void){
	char response;
	frame(DATA_FRAME, UART1_BUFFER, "LOG");
	Transmit_string_UART0(DATA_FRAME);
	response = Receive_char_UART0();
	if((response == 'Y') || (response == 'y')){
		if(!IN){
			IN = 1;
			CmdLCD(CLEAR_LCD);
			StrLCD("   LOGGED  IN");
			CmdLCD(GOTO_LINE2_POS0 + 4);
			DisplayRTCTime(HOUR, MIN, SEC);
			delay_ms(1000);
		}
		else{
			IN = 0;
			CmdLCD(CLEAR_LCD);
			StrLCD("   LOGGED OUT");
			CmdLCD(GOTO_LINE2_POS0 + 4);
			DisplayRTCTime(HOUR, MIN, SEC);
			delay_ms(1000);
		}
	}
	else if((response == 'N') || (response == 'n')){
		CmdLCD(CLEAR_LCD);
		StrLCD("USER NOT EXISTED");
		delay_ms(1000);
	}
} */
void user(void){

	int timeout = 6000000, display = 0;
	frame(DATA_FRAME, UART1_BUFFER, "LOG");
	Transmit_string_UART0(DATA_FRAME);
	delay_ms(500);       // Syncing Purpose
	if(UART0_Fired){
		UART0_Fired = 0;
		response = UART0_BYTE;
	}
	//response = Receive_char_UART0();
	if((response == 'A') || (response == 'a')){
			CmdLCD(CLEAR_LCD);
			StrLCD(" FILE NOT FOUND");
			delay_ms(1000);
	}
	else if((response == 'I') || (response == 'i')){
			CmdLCD(CLEAR_LCD);
			StrLCD("   LOGGED  IN");
			CmdLCD(GOTO_LINE2_POS0 + 4);
		    DisplayRTCTime(HOUR, MIN, SEC);
			delay_ms(2000);
	}
	else if (response == 'O' || response == 'o'){
			CmdLCD(CLEAR_LCD);
			StrLCD("   LOGGED OUT");
			CmdLCD(GOTO_LINE2_POS0 + 4);
			DisplayRTCTime(HOUR, MIN, SEC);
			delay_ms(2000);
	}
	else if((response == 'N') || (response == 'n')){
		CmdLCD(CLEAR_LCD);
		StrLCD("USER NOT EXISTED");
		delay_ms(2000);
	}
	else if((response == 'S') || (response == 's')){
		CmdLCD(CLEAR_LCD);
		StrLCD("MAXIMUM IN & OUT");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("    REACHED!");
		delay_ms(2000);
	}
	else if((response == 'D') || (response == 'd')){
		CmdLCD(CLEAR_LCD);
		StrLCD("  TOO FAST OUT");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("WAIT 10 SECONDS!");
		delay_ms(2000);
	}
	else if((response == 'B') || (response == 'b')){
		CmdLCD(CLEAR_LCD);
		StrLCD(" TIME VIOLATED!");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("IN_OUT MISMATCHS");
		delay_ms(2000);
		while(1){
			timeout--;
			if(UART1_Fired){
				UART1_Fired = 0;
				CmdLCD(CLEAR_LCD);
				StrLCD(" Edit the time");
				delay_ms(1000);
				EditTime();
				CmdLCD(CLEAR_LCD);
				break;
			}
			if(!timeout){
				timeout = 6000000;
				if(!display){
					CmdLCD(CLEAR_LCD);
					StrLCD(" TAP ADMIN CARD");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("   TO RESOLVE");
				}
				else{
					CmdLCD(CLEAR_LCD);
					delay_ms(500);
				}
			}	
		}
	}
	else if((response == 'C') || (response == 'c')){
		CmdLCD(CLEAR_LCD);
		StrLCD("   TRY  AFTER");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("    09:00:00");
		delay_ms(2000);
	}
}
int string_len(char *ptr){

	int count = 0;

	while((*ptr != '\0') && (*ptr != '\n')){

		count++;

		ptr++;

	}

	return count;

}



void frame(char *frame, char *ID, char *purpose){
	int i = 0;
	int j = 0;
	char ones_place;
	char tens_place;
	
	//ID Field
	frame[i] = '[';
	for(i = 1; ID[i - 1]; i++){
		frame[i] = ID[i - 1];
	}
	frame[i++] = ']';
	
	//Purpose Field
	frame[i++] = '(';
	for(j = 0; purpose[j]; j++){
		frame[i++] = purpose[j];
	}
	frame[i++] = ')';
	
	//Time Field
	frame[i++] = '{';
	ones_place = ((HOUR % 10) + 48);
	tens_place = ((HOUR / 10) + 48);
	frame[i++] = tens_place;
	frame[i++] = ones_place;
	frame[i++] = ':';
	ones_place = ((MIN % 10) + 48);
	tens_place = ((MIN / 10) + 48);
	frame[i++] = tens_place;
	frame[i++] = ones_place;
	frame[i++] = ':';
	ones_place = ((SEC % 10) + 48);
	tens_place = ((SEC / 10) + 48);
	frame[i++] = tens_place;
	frame[i++] = ones_place;
	frame[i++] = '}';
	
	//Null Termination
	frame[i] = '\0';
}
 void Capitalize_String(char *ptr){

	while(*ptr){

		if(islower(*ptr))

			*ptr = (*ptr) - 32;

		ptr++;

	}

}


void LCD_SCROLL(char *str, int row, int dir){

  int i, j;

  int len = 0;

  int start_col;

	

  // Calculate string length 

  while (str[len] != '\0')

		len++;


  // Calculate center start column

  start_col = (LCD - len) / 2;

  

	if (dir == LEFT){

    for (i = LCD; i >= start_col; i--){

			CmdLCD(GOTO_LINE1_POS0);

			for (j = 0; j < LCD; j++){

				if ((j >= i) && ((j - i) < len))

					CharLCD(str[j - i]);

        else

					CharLCD(' ');

      }

            delay_ms(1);

    }

  }

  else{

		for (i = -len; i <= start_col; i++){

			CmdLCD(GOTO_LINE1_POS0);

			for (j = 0; j < LCD; j++){

				if (((j - i) >= 0) && ((j - i) < len))

					CharLCD(str[j - i]);

        else

					CharLCD(' ');

      }

            delay_ms(1);

    }

  }

}
