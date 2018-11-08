/*
 * speaker.h
 *
 * Created: 2018-09-11 오후 12:03:38
 *  Author: USER
 */ 
#ifndef __SPEAKER_H
#define __SPEAKER_H
#define DO 1
#define RE 2
#define MI 3
#define FA 4
#define SOL 5
#define LA 6
#define SI 7
void speaker_out(unsigned char scale);
void speaker_init(void);
#endif // __SPEAKER_H