/*
 * key.h
 *
 * Created: 2018-09-11 오후 12:08:12
 *  Author: USER
 */ 

#ifndef __KEY_H
#define __KEY_H
#define KEY_DO 1
#define KEY_RE 2
#define KEY_MI 3
#define KEY_FA 4
#define KEY_SOL 5
#define KEY_LA 6
#define KEY_SI 7
#define KEY_MENU 8
#define KEY_POWER 9
unsigned char getkey(unsigned char keyin);
void key_init(void);
#endif // __KEY_H