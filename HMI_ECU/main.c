/*
 * main.c
 *
 *  Created on: Oct 6, 2019
 *      Author: Heba_Mostafa
 */
#include"lcd.h"
#include"uart.h"
#include"keypad.h"
#define M2_READY 0x10
//set pass for the first time
void get_pass();
void main_screen();
void init_proccess( bool ack){
	LCD_clearScreen();

		if(ack=='0'){

			LCD_displayString("ERORR");
			_delay_ms(3000);
			LCD_clearScreen();
			UART_sendByte(0x55); // MC2 is ready
			while(UART_recieveByte() != 0x50){} // wait until MC2 is ready
		    UART_sendByte(0);

			get_pass();
		}
		else{

			LCD_displayString("SUCCESSFULLY DONE");
			_delay_ms(3000);
			 main_screen();
			UART_sendByte(0x55); // MC2 is ready
						while(UART_recieveByte() != 0x50){} // wait until MC2 is ready
					    UART_sendByte(1);
		}
}
void main_screen(){
	LCD_clearScreen();
				LCD_displayString("+:open");
				LCD_displayStringRowColumn(1,0,"-:Change Pass");
}
bool confirm_pass(){
			uint8 count=0;
				uint8 i=0;
					bool ack=0;
					uint8 pass[5];
			count=0;
					LCD_clearScreen();
					_delay_ms(2000); /* Press time */
					LCD_displayString("confirm pass:");
						while(KeyPad_getPressedKey()!=13){
							i=KeyPad_getPressedKey();
							pass[count]=i;
							count++;
							LCD_displayCharacter('*');
							//LCD_intgerToString(i);
							_delay_ms(1500); /* Press time */
						}
						pass[count]='#';
						UART_sendByte(0x22); // MC2 is ready
						while(UART_recieveByte() != 0x20){}
						UART_sendString(pass);
						LCD_clearScreen();
						while(UART_recieveByte() != 0x30){}
						UART_sendByte(0x33); // MC2 is read
						ack= UART_recieveByte();
						LCD_clearScreen();

						return ack;
		}

void get_action(){
	uint8 i=KeyPad_getPressedKey();
	bool state=0;
	if(i=='+'){


 	state=confirm_pass();
 	UART_sendByte(0x66); // MC2 is ready
 						while(UART_recieveByte() != 0x60){} // wait until MC2 is ready
 					    UART_sendByte(1);

		if(state==49){
		LCD_displayString("DOOR IS OPENNING");
		_delay_ms(4000);
		LCD_displayString("DOOR IS CLOSING");
		}
	}
	else if(i=='-')
	{
		state=confirm_pass();
		UART_sendByte(0x66); // MC2 is ready
			while(UART_recieveByte() != 0x60){} // wait until MC2 is ready
		    UART_sendByte(0);
		if(state==49){
			get_pass();
			//LCD_displayString("DONE");
		}
			}
}




void get_pass(){
	//counter to count nums from keypad
	uint8 count=0;
	uint8 i=0;
		bool ack=0;
		uint8 pass[5];
		LCD_displayString("enter pass:");
		_delay_ms(3000);
		while(KeyPad_getPressedKey()!=13){
			i=KeyPad_getPressedKey();

			pass[count]=i;
			count++;
			LCD_displayCharacter('*');
			//LCD_intgerToString(i);
			_delay_ms(1500); /* Press time */

		}

		pass[count]='#';
		UART_sendByte(0x11); // MC2 is ready
			while(UART_recieveByte() != M2_READY){} // wait until MC2 is ready
			UART_sendString(pass);
			//UART_sendByte(pass[0]);
		///////////////////may need to get ack
			ack=confirm_pass();
			init_proccess(ack);
}

int main(void){
	DDRD|=(1<<2);
	PORTD&=~(1<<2);
	LCD_init();
	UART_init();
	/*UART_sendByte(0x11); // MC2 is ready
	while(UART_recieveByte() != M2_READY){} // wait until MC2 is ready
		UART_sendString("I am Micro1#"); // send the required string to MC2*/
	 get_pass();
	while(1){
		get_action();
	}


	return 0;
}
