/*
 * myFunc.h
 *
 * Created: 2018-09-12 오후 2:07:29
 *  Author: USER
 */ 


#ifndef MYFUNC_H_
#define MYFUNC_H_
#include "led.h"
#include "lcd.h"

#define do_ 261
#define re_ 293
#define mi_ 329
#define fa_ 349
#define sol_ 391
#define la_ 440
#define si_ 493
#define do_2 522

#define re_2 586
#define mi_2 658
#define fa_2 698
#define sol_2 782
#define la_2 880
#define si_2 986
#define do_3 1044





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

void freqSet(int freq, int delayTime){
	OCR1A = 8000000 / freq;  // 주파수 = 16000000 / (2 * 1(분주비) * OCR1A), OCR1A = 16000000 / (2 * 1) / 주파수
	_delay_ms(delayTime);
}

void port_init(){
	//speaker init
	TCCR1A = 0x40;
	TCCR1B = 0x09;
	DDRB = 0xff;
	
	// led init
	DDRA = 0xff;
	PORTA = 0xff;

	// key init
	DDRD = 0b00001111;
	PORTD = 0b11111111;
	_delay_us(20);
}

void record_piano(unsigned int key){
	if(key == sw1){
		freqSet(do_,1);
		PORTA = 0b11111110;
	}
	else if(key == sw2){
		freqSet(re_,1);
		PORTA = 0b11111101;
	}
	else if(key == sw3){
		freqSet(mi_,1);
		PORTA = 0b11111011;
	}
	else if(key == sw4){
		freqSet(fa_,1);
		PORTA = 0b11110111;
	}
	else if(key == sw5){
		freqSet(sol_,1);
		PORTA = 0b11101111;
	}
	else if(key == sw6){
		freqSet(la_,1);
		PORTA = 0b11011111;
	}
	else if(key == sw7){
		freqSet(si_,1);
		PORTA = 0b10111111;
	}
	else{
		OCR1A = 0;
		PORTA = 0xff;
	}	
}

void play_piano(unsigned int key, char *str2){
	
	if(key == sw1){
		str2[1] = 255;
		lcd_putsf(0,1,(unsigned char *)str2);
		freqSet(do_,1);
		PORTA = 0b11111110;
	}
	else if(key == sw2){
		str2[3] = 255;
		lcd_putsf(0,1,(unsigned char *)str2);
		freqSet(re_,1);
		PORTA = 0b11111101;
	}
	else if(key == sw3){
		str2[5] = 255;
		lcd_putsf(0,1,(unsigned char *)str2);
		freqSet(mi_,1);
		PORTA = 0b11111011;
	}
	else if(key == sw4){
		str2[7] = 255;
		lcd_putsf(0,1,(unsigned char *)str2);
		freqSet(fa_,1);
		PORTA = 0b11110111;
	}
	else if(key == sw5){
		str2[9] = 255;
		lcd_putsf(0,1,(unsigned char *)str2);
		freqSet(sol_,1);
		PORTA = 0b11101111;
	}
	else if(key == sw6){
		str2[11] = 255;
		lcd_putsf(0,1,(unsigned char *)str2);
		freqSet(la_,1);
		PORTA = 0b11011111;
	}
	else if(key == sw7){
		str2[13] = 255;
		lcd_putsf(0,1,(unsigned char *)str2);
		freqSet(si_,1);
		PORTA = 0b10111111;
	}
	else{
		sprintf(str2,"                    ");
		lcd_putsf(0,1,(unsigned char *)str2);
		OCR1A = 0;
		PORTA = 0xff;
	}	
}

void powerOn(char *str1, char *str2){
	sprintf(str1,"  PIANO START");
	lcd_putsf(0,0,(unsigned char *)str1);
	sprintf(str2,"   POWER ON!");
	lcd_putsf(0,1,(unsigned char *)str2);
	_delay_ms(3000);
	
	sprintf(str2,"                    ");
	lcd_putsf(0,1,(unsigned char *)str2);
}

void powerOff(char *str1, char *str2, bool a){
	if(a){
		sprintf(str1,"  PIANO SYSTEM");
		lcd_putsf(0,0,(unsigned char *)str1);
		sprintf(str2,"   POWER OFF!");
		lcd_putsf(0,1,(unsigned char *)str2);
		_delay_ms(1000);
		sprintf(str1,"    GOOD BYE    ");
		lcd_putsf(0,0,(unsigned char *)str1);
		lcd_putsf(0,1,(unsigned char *)str2);
		_delay_ms(1000);
	}
	else{
		sprintf(str1,"                    ");
		lcd_putsf(0,0,(unsigned char *)str1);
		sprintf(str2,"                    ");
		lcd_putsf(0,1,(unsigned char *)str2);	
	}
}

unsigned int ex1_song[100] = {0, sol_, do_2, re_2, re_2, mi_2, mi_2, fa_2, fa_2, re_2, mi_2, fa_2, mi_2, la_2, la_2, la_2, si_2, do_3, 0};
int ex1_time[100] = {0, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200};

#endif /* MYFUNC_H_ */