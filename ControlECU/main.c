/*
 * main.c
 *
 *  Created on: Oct 6, 2019
 *      Author: future
 */
#include"external_eeprom.h"
#include"uart.h"
#include"lcd.h"
#define M2_READY 0x10
char confirm(){
		uint8 Str2[3];

		uint8 eeprom_read[2];
	while(UART_recieveByte() != 0x22){}
					UART_sendByte(0x20); // MC2 is ready
					UART_receiveString(Str2); // receive the string
					//Str2[0]=UART_recieveByte();
					//LCD_clearScreen();
					//LCD_intgerToString(Str2[1]);



		EEPROM_readByte(0x0311,&eeprom_read[0]);
		//EEPROM_readByte(0x0315,&eeprom_read[1]);
		UART_sendByte(0x30);
		while(UART_recieveByte() != 0x33){}

		if(eeprom_read[0]==Str2[1] ){
			UART_sendByte('1');
return '1';

		}
		else{
			UART_sendByte('0');
return '0';

		}

}
void get_action(){

			PORTA|=(1<<0);
			PORTA&=~(1<<1);
		_delay_ms(4000);
		PORTA|=(1<<1);
		PORTA&=~(1<<0);


}

void init_proccess(){
	uint8 Str[3];
	//LCD_displayString("please");
	while(UART_recieveByte() != 0x11){}
			UART_sendByte(M2_READY); // MC2 is ready
			UART_receiveString(Str); // receive the string
			//Str[0]=UART_recieveByte();
			LCD_intgerToString(Str[0]);
	EEPROM_writeByte(0x0311,Str[1]);
	//EEPROM_writeByte(0x0315,Str[1]);
	_delay_ms(10);
	confirm();
}

int main(){
	DDRA=0xff;

	EEPROM_init();
	UART_init();
	//LCD_init();
	init_proccess();
	uint8 received=0;
	uint8 received2=0;
	char conf=0;

	while(1){
		uint8 counter=0;
for(;counter<3;counter++){
	while(UART_recieveByte() != 0x55){}
	UART_sendByte(0x50); // MC2 is ready
	received=UART_recieveByte(); // receive the string
	if(received==1){
		conf=confirm();
		if(conf=='1'){
			while(UART_recieveByte() != 0x66){}
			UART_sendByte(0x60); // MC2 is ready
			received2=UART_recieveByte(); // receive the string
			if(received2==1){get_action();}
			else{init_proccess();}

						}

					}
					else{

						init_proccess();
					}


	}

	return 0;
}

