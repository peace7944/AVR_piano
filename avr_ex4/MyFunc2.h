/*
 * MyFunc2.h
 *
 * Created: 2018-09-18 오후 5:28:36
 *  Author: USER
 */ 


#ifndef MYFUNC2_H_
#define MYFUNC2_H_

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
#define do_2 523

#define re_2 587
#define mi_2 659
#define fa_2 698
#define sol_2 783
#define la_2 880
#define si_2 987
#define do_3 1046

#define re_3 1174
#define mi_3 1318
#define fa_3 1396
#define sol_3 1567
#define la_3 1760
#define si_3 1975

#define PLAY_MODE 0
#define MENU_MODE 1
#define RECORD_MODE 2
#define LISTEN_MODE 3
#define EXAMPLE_MODE 4

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

void MakeSound(int freq){
	if(freq == 0) OCR1A = 0;
	else OCR1A = 8000000 / freq; // 주파수 = 16000000 / (2 * 1(분주비) * OCR1A), OCR1A = 16000000 / (2 * 1) / 주파수
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

void piano_keyboard(unsigned int key){
	char str[20] = "                  ";
	if(key == sw1){
		str[1] = 255;
		lcd_putsf(0,1,(unsigned char *)str);
	}
	else if(key == sw2){
		str[3] = 255;
		lcd_putsf(0,1,(unsigned char *)str);
	}
	else if(key == sw3){
		str[5] = 255;
		lcd_putsf(0,1,(unsigned char *)str);
	}
	else if(key == sw4){
		str[7] = 255;
		lcd_putsf(0,1,(unsigned char *)str);
	}
	else if(key == sw5){
		str[9] = 255;
		lcd_putsf(0,1,(unsigned char *)str);
	}
	else if(key == sw6){
		str[11] = 255;
		lcd_putsf(0,1,(unsigned char *)str);
	}
	else if(key == sw7){
		str[13] = 255;
		lcd_putsf(0,1,(unsigned char *)str);
	}
	else{
		sprintf(str,"                  ");
		lcd_putsf(0,1,(unsigned char *)str);
	}
}

void play_piano(unsigned int key){
	
	if(key == sw1){
		piano_keyboard(key);
		MakeSound(do_);
		PORTA = 0b11111110;
	}
	else if(key == sw2){
		piano_keyboard(key);
		MakeSound(re_);
		PORTA = 0b11111101;
	}
	else if(key == sw3){
		piano_keyboard(key);
		MakeSound(mi_);
		PORTA = 0b11111011;
	}
	else if(key == sw4){
		piano_keyboard(key);
		MakeSound(fa_);
		PORTA = 0b11110111;
	}
	else if(key == sw5){
		piano_keyboard(key);
		MakeSound(sol_);
		PORTA = 0b11101111;
	}
	else if(key == sw6){
		piano_keyboard(key);
		MakeSound(la_);
		PORTA = 0b11011111;
	}
	else if(key == sw7){
		piano_keyboard(key);
		MakeSound(si_);
		PORTA = 0b10111111;
	}
	else{
		piano_keyboard(key);
		OCR1A = 0;
		PORTA = 0xff;
	}	
}

void listen_record(int array_cnt, int* record_time, int* record_btn){
	for(int i=0;i<=array_cnt;i++){
		if(record_btn[i] == sw1){
			piano_keyboard(do_);
			MakeSound(do_);
			PORTA = 0b11111110;
			_delay_ms(record_time[i+1]);
		}
		else if(record_btn[i] == sw2){
			piano_keyboard(re_);
			MakeSound(re_);
			PORTA = 0b11111101;
			_delay_ms(record_time[i+1]);
		}
		else if(record_btn[i] == sw3){
			piano_keyboard(mi_);
			MakeSound(mi_);
			PORTA = 0b11111011;
			_delay_ms(record_time[i+1]);
		}
		else if(record_btn[i] == sw4){
			piano_keyboard(fa_);
			MakeSound(fa_);
			PORTA = 0b11110111;
			_delay_ms(record_time[i+1]);
		}
		else if(record_btn[i] == sw5){
			piano_keyboard(sol_);
			MakeSound(sol_);
			PORTA = 0b11101111;
			_delay_ms(record_time[i+1]);
		}
		else if(record_btn[i] == sw6){
			piano_keyboard(la_);
			MakeSound(la_);
			PORTA = 0b11011111;
			_delay_ms(record_time[i+1]);
		}
		else if(record_btn[i] == sw7){
			piano_keyboard(si_);
			MakeSound(si_);
			PORTA = 0b10111111;
			_delay_ms(record_time[i+1]);
		}
		else{
			piano_keyboard(0);
			OCR1A = 0;
			PORTA = 0xff;
			_delay_ms(record_time[i+1]);
		}
	}	
}

void powerOn(char *str1, char *str2, bool a){
	if(a){
		sprintf(str1,"  PIANO START");
		lcd_putsf(0,0,(unsigned char *)str1);
		sprintf(str2,"   POWER ON!");
		lcd_putsf(0,1,(unsigned char *)str2);
//		_delay_ms(3000);
		sprintf(str2,"                    ");
		lcd_putsf(0,1,(unsigned char *)str2);
	}
}

void powerOff(char *str1, char *str2, bool a){
	if(a){
		sprintf(str1,"  PIANO SYSTEM");
		lcd_putsf(0,0,(unsigned char *)str1);
		sprintf(str2,"   POWER OFF!");
		lcd_putsf(0,1,(unsigned char *)str2);
//		_delay_ms(1000);
		sprintf(str1,"    GOOD BYE    ");
		lcd_putsf(0,0,(unsigned char *)str1);
		lcd_putsf(0,1,(unsigned char *)str2);
//		_delay_ms(1000);
	}
	else{
		sprintf(str1,"                    ");
		lcd_putsf(0,0,(unsigned char *)str1);
		sprintf(str2,"                    ");
		lcd_putsf(0,1,(unsigned char *)str2);	
	}
}

void exam_listening(int array_cnt, int* ex_time, int* ex_song){
	for(int i=0;i<=array_cnt;i++){
		MakeSound(ex_song[i]);
		PORTA = 0b11111101;
		_delay_ms(ex_time[i]);
	}
	OCR1A = 0;
	PORTA = 0xff;
}

int ex1_song[200] = {
	0, sol_, do_2, re_2, 0, re_2, 0, mi_2, 0, mi_2,
	mi_2, 0, 0, do_2, re_2, mi_2, 0, re_2, 0, sol_2, 0, sol_2,

	sol_2, 0, sol_2, la_2, si_2, 0, si_2, 0, do_3, 0, do_3,
	do_3, 0, re_3, 0, mi_3, 0, re_3, 0, do_3, 0, si_2,

	si_2, 0, do_3, 0, si_2, 0, sol_2, 0, sol_2, 0, la_2, 0, la_2,
	la_2, 0, sol_2, 0, fa_2, 0, fa_2, 0, sol_2, 0, sol_2,

	sol_2, 0, do_2, re_2, 0, mi_2, 0, fa_2, 0, fa_2,
	fa_2, 0, sol_2, 0, fa_2, 0, mi_2, 0,

	re_2, 0, sol_, 0, do_2, 0, re_2, 0, re_2, 0, mi_2, 0, mi_2,
	mi_2, 0, do_2, re_2, mi_2, 0, re_2, 0, sol_2, 0, sol_2,

	sol_2, 0, sol_2, la_2, si_2, 0, si_2, 0, do_3, 0, do_3,
	do_3, 0, re_3, 0, mi_3, 0, re_3, 0, do_3, 0, si_2,

	si_2, 0, do_3, 0, si_2, 0, sol_2, 0, sol_2, 0, la_2, 0, la_2,
	la_2, 0, sol_2, 0, fa_2, 0, fa_2, 0, sol_2, 0, sol_2,

	sol_2, 0, do_2, re_2, 0, mi_2, 0, fa_2, 0, la_2, 0,
	do_2, 0, si_, 0, do_2,
0,};

int ex1_time[200] = {
	0, 250, 250, 225, 25, 450, 50, 450, 50, 1000,
	900, 100, 250, 250, 250, 225, 25, 450, 50, 450, 50, 1000,

	1000, 250, 250, 250, 225, 25, 450, 50, 450, 50, 1000,
	450, 50, 450, 50, 300, 33, 300, 33, 300, 33, 2000,

	450, 50, 450, 50, 450, 50, 450, 50, 450, 50, 450, 50, 1000,
	900, 0, 450, 50, 450, 50, 450, 50, 450, 50, 1000,

	1000, 500, 250, 225, 25, 450, 50, 450, 50, 1000,
	900, 100, 450, 50, 450, 50, 1900, 100,

	450, 50, 450, 50, 450, 50, 450, 50, 450, 50, 450, 50, 1000,
	1000, 250, 250, 250, 250, 50, 450, 50, 450, 50, 1000,

	1000, 250, 250, 250, 225, 25, 450, 50, 450, 50, 1000,
	450, 50, 450, 50, 300, 33, 300, 33, 300, 33, 2000,

	450, 50, 450, 50, 450, 50, 450, 50, 450, 50, 450, 50, 1000,
	900, 0, 450, 50, 450, 50, 450, 50, 450, 50, 1000,

	1000, 500, 250, 225, 25, 450, 50, 900, 100, 450, 50,
	900, 100, 900, 100, 2000,
0,};

#endif /* MYFUNC_H_ */



#endif /* MYFUNC2_H_ */