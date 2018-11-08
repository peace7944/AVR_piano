/*
 * ex5.cpp
 *
 * Created: 2018-09-18 오후 5:04:34
 *  Author: USER
 */ 
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000  // cpu 클럭 설정
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "MyFunc2.h"

unsigned int msec = 0, rec_time = 0;
bool record_start = false;
int menu_flag = 0, example_menu_flag = 0, array_cnt = 0;
int record_time[100] = {0, }, record_btn[100] = {0, };

ISR(TIMER0_OVF_vect){  // interrupt service routine 분주한 속도 * 250 = 0.001
	msec++;
	
	if(record_start) rec_time++;
	if(menu_flag >= 4) menu_flag = 0;
	if(example_menu_flag >= 4) example_menu_flag = 0;
	
	if(msec > 1000){  // 2초로 바꿔라
		menu_flag++;
		example_menu_flag++;
		msec = 0;
	}
}

int main(){
	lcd_init();
	lcd_clear();
	port_init();
	
	unsigned int key, record_key, power_toggle = 0;
	bool powerOn_toggle = true, powerOff_toggle = true, menu_timer_toggle = true;
	bool record_btn_toggle = true, example_btn_toggle = true, return_btn_toggle = true;
	char str1[20] = "                   ";
	char str2[20] = "                   ";
	int state = PLAY_MODE;
	int r_flag = 0;
	
	//timer init
	TCNT0 = 6;  // TCNT0가 256이 될때 overflow -> 0  1/16mHz = 0.0000000625, 0.0000000625 * 64 = 0.000004 분주한 속도
	TIMSK = 0x01;  // 0b00000001, timer 0 enable
	TCCR0 = 0b00000100;  // 0b00000100, 분주비 = 64
	sei();  // 숫자를 카운트
	
	while (1){
		key = my_getkey();
		
		if(key == sw9) power_toggle = ~power_toggle;
		
		if(power_toggle){
			powerOn(str1,str2,powerOn_toggle);
			powerOn_toggle = false;
			powerOff_toggle = true;
			
			if(state == PLAY_MODE){
				if(key == sw8){
					if(return_btn_toggle){
						state = MENU_MODE;
					}
				}
				else return_btn_toggle = true;
				sprintf(str1,"  PIANO START         ");
				lcd_putsf(0,0,(unsigned char *)str1);
				play_piano(key);
			}
			
			else if(state == MENU_MODE){
				if(menu_timer_toggle){
					msec = 0;
					menu_flag = 0;
					menu_timer_toggle = false;
				}

				sprintf(str1,"    M E N U         ");
				lcd_putsf(0,0,(unsigned char *)str1);
				if(menu_flag == 0){
					sprintf(str2,"1. Recording        ");
					if(key == sw8){
						state = RECORD_MODE;
						record_btn_toggle = false;
						record_start = true;
						lcd_clear();
					}
				}
				else if(menu_flag == 1){
					sprintf(str2,"2. Listening        ");
					if(key == sw8){
						state = LISTEN_MODE;
					}
				}
				else if(menu_flag == 2){
					sprintf(str2,"3. Example          ");
					if(key == sw8){
						example_btn_toggle = false;
						menu_timer_toggle = true;
						state = EXAMPLE_MODE;
					}
				}
				else if(menu_flag == 3){
					sprintf(str2,"4. Return           ");
					if(key == sw8){
						state = PLAY_MODE;
						return_btn_toggle = false;
					}
				}					
				lcd_putsf(0,1,(unsigned char *)str2);				
			}
			
			else if(state == RECORD_MODE){
				sprintf(str1,"  Recording..      ");
				
				if(key==sw8){
					if(record_btn_toggle){
						record_btn_toggle = true;
						record_start = false;
						menu_timer_toggle = true;
						state = MENU_MODE;
					}
				}
				else record_btn_toggle = true;

				if(key != sw9 && key != sw8) record_key = key;
				if(record_key){
					if(r_flag  == 0){
						record_time[array_cnt] = rec_time;
						record_btn[array_cnt] = key;
						rec_time = 0;
						array_cnt++;
						r_flag = 1;
					}
				}
				else{
					if(r_flag == 1){
						record_time[array_cnt] = rec_time;
						record_btn[array_cnt] = key;
						rec_time = 0;
						array_cnt++;
						r_flag = 0;
					}
				}
				play_piano(key);
				lcd_putsf(0,0,(unsigned char *)str1);
			}
			
			else if(state == LISTEN_MODE){
				sprintf(str1,"  Listening..        ");
				lcd_putsf(0,0,(unsigned char *)str1);
				listen_record(array_cnt,record_time,record_btn);
				menu_timer_toggle = true;
				state = MENU_MODE;
			}
			
			else if(state == EXAMPLE_MODE){
				sprintf(str1,"  - Example -         ");
				lcd_putsf(0,0,(unsigned char *)str1);
				
				if(menu_timer_toggle){
					msec = 0;
					example_menu_flag = 0;
					menu_timer_toggle = false;
				}
				
				if(example_menu_flag == 0){
					sprintf(str2,"1. Example 1        ");
					if(key == sw8){
						exam_listening(200,ex1_time,ex1_song);
						state = MENU_MODE;						
					}
				}
				else if(example_menu_flag == 1){
					sprintf(str2,"2. Example 2        ");
					if(key == sw8){
						state = MENU_MODE;							
					}
				}
				else if(example_menu_flag == 2){
					sprintf(str2,"3. Example 3        ");
					if(key == sw8){
						state = MENU_MODE;							
					}
				}
				else if(example_menu_flag == 3){
					sprintf(str2,"4. Return           ");
					if(key == sw8){
						state = MENU_MODE;
					}
				}					
				example_btn_toggle = false;
				lcd_putsf(0,1,(unsigned char *)str2);
			}
			
		}
		else{
			powerOff(str1,str2,powerOff_toggle);
			powerOff_toggle = false;
			powerOn_toggle = true;
		}
	}
}