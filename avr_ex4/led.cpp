#include <avr/io.h>
#define F_CPU 16000000  // cpu 클럭 설정
#include <util/delay.h>
#include "led.h"
#define LED_OUT PORTA
#define LED_DDR DDRA

void led_light(unsigned char scale)
{
	if( scale ) LED_OUT = ~(0x01 << (scale - 1));
	else LED_OUT = 0xFF;
}
void led_init(void)
{
	LED_DDR = 0xFF;
	LED_OUT = 0xFF;
}

int main(){
	
	DDRA = 0xff;
	
	while(1){
		
		PORTA = 0xff;
		_delay_ms(500);
		PORTA = 0x00;
		_delay_ms(500);		
	}
}