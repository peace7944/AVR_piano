/*
 * ex3_2.cpp
 *
 * Created: 2018-09-12 오전 9:24:14
 *  Author: USER
 */ 
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000  // cpu 클럭 설정
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "led.h"
#include "lcd.h"

#define do_ 261
#define re_ 293
#define mi_ 329
#define fa_ 349
#define sol_ 391
#define la_ 440
#define si_ 493
#define do_high 522

#define sw1 0x1e
#define sw2 0x2e
#define sw3 0x4e
#define sw4 0x1d
#define sw5 0x2d
#define sw6 0x4d
#define sw7 0x1b
#define sw8 0x2b
#define sw9 0x4b

void freqSet(int freq, int delayTime){
	OCR1A = 8000000 / freq;  // 주파수 = 16000000 / (2 * 1(분주비) * OCR1A), OCR1A = 16000000 / (2 * 1) / 주파수
	_delay_ms(delayTime);
}

int main(){
	TCCR1A = 0x40;
	TCCR1B = 0x09;
	DDRB = 0xff;
	while(1){
		freqSet(mi_,300);
		freqSet(sol_,300);
		freqSet(sol_,300);
		freqSet(fa_,300);
		freqSet(sol_,300);
		freqSet(la_,300);
		
		freqSet(mi_,300);
		freqSet(sol_,300);
		freqSet(sol_,300);
		freqSet(fa_,300);
		
		freqSet(sol_,300);
		freqSet(la_,300);				

		freqSet(mi_,300);
		freqSet(sol_,300);
		freqSet(sol_,300);
		freqSet(fa_,300);
		freqSet(sol_,300);
		freqSet(la_,300);

		freqSet(sol_,300);
		freqSet(la_,300);
		
		freqSet(mi_,300);
		freqSet(mi_,300);
		freqSet(re_,300);
		freqSet(si_,300);
		
		freqSet(re_,300);
		freqSet(si_,300);
		
		freqSet(sol_,300);
		freqSet(la_,300);
		freqSet(la_,300);
		freqSet(la_,300);
		freqSet(sol_,300);
		freqSet(la_,300);
		freqSet(si_,300);
		
		freqSet(fa_,300);
		freqSet(sol_,300);
		
		freqSet(mi_,300);
		freqSet(mi_,300);
		freqSet(re_,300);
		freqSet(si_,300);
		
		freqSet(re_,300);
		freqSet(si_,300);
		
		freqSet(la_,300);
		freqSet(sol_,300);
		
		freqSet(la_,300);
		freqSet(la_,300);
		freqSet(sol_,300);
		freqSet(la_,300);
		freqSet(si_,300);
		
		freqSet(sol_,300);
		freqSet(fa_,300);						
	}
}