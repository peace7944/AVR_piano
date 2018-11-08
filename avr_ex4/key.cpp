/*
 * key.cpp
 *
 * Created: 2018-09-11 오후 12:07:31
 *  Author: USER
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "key.h"
#define KEY_OUT PORTD
#define KEY_IN PIND
#define KEY_DDR DDRD
volatile char key_flag;
unsigned char getkey(unsigned char keyin)
{
	unsigned char key;
	key_flag = 0;
	KEY_OUT = ~0x01;
	_delay_us(10);
	key = ~KEY_IN & 0xF0;
	if( key ) {
		_delay_ms(5);
		key = ~KEY_IN & 0xF0;
		if( key ) {
			if( key == 0x10 ) key = KEY_DO;
			else if( key == 0x20 )key = KEY_RE;
			else if( key == 0x40 )key = KEY_MI;
		}
	}
	else {
		KEY_OUT = ~0x02;
		_delay_us(10);
		key = ~KEY_IN & 0xF0;
if( key ) {
	_delay_ms(5);
	key = ~KEY_IN & 0xF0;
	if( key ) {
		if( key == 0x10 ) key = KEY_FA;
		else if( key == 0x20 )key = KEY_SOL;
		else if( key == 0x40 )key = KEY_LA;
	}
}
else {
	KEY_OUT = ~0x04;
	_delay_us(10);
	key = ~KEY_IN & 0xF0;
	if( key ) {
		_delay_ms(5);
		key = ~KEY_IN & 0xF0;
		if( key ) {
			if( key == 0x10 ) key = KEY_SI;
			else if( key == 0x20 )key = KEY_MENU;
			else if( key == 0x40 )key = KEY_POWER;
		}
	}
}
}
if( key && (key != keyin) ) key_flag = 1;
return key;
}
void key_init(void)
{
	KEY_OUT = 0xF0;
	KEY_DDR = 0x0F;
}