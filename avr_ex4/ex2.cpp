/*
 * ex2.cpp
 *
 * Created: 2018-09-11 오후 3:16:55
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

int main(){

	lcd_init();
	lcd_clear();
	
	while(1){
		lcd_putsf(0,0,(unsigned char *)"hellow asshole");
	}
}