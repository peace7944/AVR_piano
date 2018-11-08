/*
 * speaker.cpp
 *
 * Created: 2018-09-11 오후 12:03:03
 *  Author: USER
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "speaker.h"
#define SPEAKER_OUT PORTB
#define SPEAKER_DDR DDRB
#define SPEAKER PB5
void speaker_out(unsigned char scale)
{
	unsigned int scale_table[8] = { 0, 956, 851, 758, 716, 638, 568, 506 };
	ICR1 = scale_table[scale];
	OCR1A = ICR1 / 2;
}
void timer1_init(void)
{
	TCCR1A = 0x82;
	TCCR1B = 0x1B;
	TCCR1C = 0x00;
	TCNT1 = 0;
	ICR1 = 0;
	OCR1A = 0;
}
void speaker_init(void)
{
	SPEAKER_DDR |= (1 << SPEAKER);
	timer1_init();
}