
#ifndef ENCODER_H_
#define ENCODER_H_

#define F_CPU 3686400UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sendData();
void initTimer0();
void sendCommand();
char getSendingStatus();
void sendDataBit();

unsigned char sendInfo[17];
unsigned char sendCount;
unsigned char isSending;
unsigned char startSequence[4];

#endif