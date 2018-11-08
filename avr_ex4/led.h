#ifndef __LED_H
#define __LED_H
#define LED_DO 1
#define LED_RE 2
#define LED_MI 3
#define LED_FA 4
#define LED_SOL 5
#define LED_LA 6
#define LED_SI 7
void led_light(unsigned char scale);
void led_init(void);
#endif // __LED_H