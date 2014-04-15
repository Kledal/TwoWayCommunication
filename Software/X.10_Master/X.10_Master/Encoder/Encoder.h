#ifndef ENCODER_H_
#define ENCODER_H_

#define F_CPU 3686400UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sendData();
void initTimer0();
void sendCommand();

/*
 Send variables
*/
extern unsigned char sendInfo[17];
extern unsigned char sendCount;
extern unsigned char isSending;

#endif /* ENCODER_H_ */