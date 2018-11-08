/*
 * ex1.cpp
 *
 * Created: 2018-09-11 오후 2:18:03
 *  Author: USER
 */ 

#include <avr/io.h>
#define F_CPU 16000000  // cpu 클럭 설정
#include <util/delay.h>
#include "led.h"
#define LED_OUT PORTA
#define LED_DDR DDRA

#define do_ 1915
#define re 1706
#define mi 1519
#define fa 1432
#define sol 1278
#define la 1136
#define si 1014
#define do_high 957

#define sw1 0b01100110
#define sw2 0b01010110
#define sw3 0b00110110
#define sw4 0b01100101
#define sw5 0b01010101
#define sw6 0b00110101
#define sw7 0b01100011
#define sw8 0b01010011
#define sw9 0b00110011


int main(){
	
	DDRB = 0xff;
	DDRD = 0x00;
	PORTD = 0xff;
	
	int state = 0;
	
	while(1){ 
		PORTB = 0xff;
		_delay_us(do_);
		PORTB = 0x00;
		_delay_us(do_);		

	}
}