/*
 * ex3.cpp
 *
 * Created: 2018-09-11 오후 3:59:21
 *  Author: USER
 */ 
#include <avr/io.h>
#define F_CPU 16000000  // cpu 클럭 설정
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "led.h"
#include "lcd.h"

#define do_ 1915
#define re_ 1706
#define mi_ 1519
#define fa_ 1432
#define sol_ 1278
#define la_ 1136
#define si_ 1014
#define do_high 957

#define sw1 0x1e
#define sw2 0x2e
#define sw3 0x4e
#define sw4 0x1d
#define sw5 0x2d
#define sw6 0x4d
#define sw7 0x1b
#define sw8 0x2b
#define sw9 0x4b

unsigned int my_getkey(){
	unsigned int key = 0, result = 0;
	for(int i=0;i<3;i++){
		if(i==0) PORTD = 0b11111110;
		if(i==1) PORTD = 0b11111101;
		if(i==2) PORTD = 0b11111011;
		
		_delay_us(5);
	
		key = (~PIND & 0xf0);
		if(key){
			result = key | (PORTD & 0x0f);
			return result;
		}		
	}
	return 0;
}

void speaker(int a){
	if(a == 1){
		PORTB = 0xff;
		_delay_us(do_);
		PORTB = 0x00;
		_delay_us(do_);
	}
	else if(a == 2){
		PORTB = 0xff;
		_delay_us(re_);
		PORTB = 0x00;
		_delay_us(re_);
	}
	else if(a == 3){
		PORTB = 0xff;
		_delay_us(mi_);
		PORTB = 0x00;
		_delay_us(mi_);
	}
	else if(a == 4){
		PORTB = 0xff;
		_delay_us(fa_);
		PORTB = 0x00;
		_delay_us(fa_);
	}
	else if(a == 5){
		PORTB = 0xff;
		_delay_us(sol_);
		PORTB = 0x00;
		_delay_us(sol_);
	}
	else if(a == 6){
		PORTB = 0xff;
		_delay_us(la_);
		PORTB = 0x00;
		_delay_us(la_);
	}
	else if(a == 7){
		PORTB = 0xff;
		_delay_us(si_);
		PORTB = 0x00;
		_delay_us(si_);
	}
	else if(a == 8){
		PORTB = 0xff;
		_delay_us(do_high);
		PORTB = 0x00;
		_delay_us(do_high);
	}
}

int main(){

	lcd_init();
	lcd_clear();
	
	DDRA = 0xff;
	DDRD = 0b00001111;
	PORTD = 0b11111111;

	char str[16] = {0,};
	int state = 0, flag = 0;
	
	while(1){	
		//itoa(my_getkey(),str,16);  // 키값 확인용
		//lcd_putsf(0,0,(unsigned char *)str);
		
		state = my_getkey();
		
		switch (state)
		{
			case sw1 :
				PORTA = 0b11111110;
				sprintf(str,"do");
				for(int i=0;i<10;i++){
					speaker(1);
				}		
			break;

			case sw2 :
				PORTA = 0b11111101;
				sprintf(str,"re");
				for(int i=0;i<10;i++){
					speaker(2);
				}				
			break;						
			
			case sw3 :
				PORTA = 0b11111011;
				sprintf(str,"mi");
				for(int i=0;i<10;i++){
					speaker(3);
				}
			break;
			
			case sw4 :
				PORTA = 0b11110111;
				sprintf(str,"fa");
				for(int i=0;i<10;i++){
					speaker(4);
				}
			break;

			case sw5 :
				PORTA = 0b11101111;
				sprintf(str,"sol");
				for(int i=0;i<10;i++){
					speaker(5);
				}
			break;

			case sw6 :
				PORTA = 0b11011111;
				sprintf(str,"la");
				for(int i=0;i<10;i++){
					speaker(6);
				}
			break;

			case sw7 :
				speaker(7);
				PORTA = 0b10111111;
				sprintf(str,"fa");
			break;
			
			case sw8 :
				speaker(8);
				sprintf(str,"fa");
			break;
			
			default:
				
			break;
		}
		lcd_putsf(0,0,(unsigned char *)"    PIANO");
		lcd_putsf(0,1,(unsigned char *)str);		
	}
}