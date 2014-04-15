/*
 * Encoder.c
 *
 * Created: 14-04-2014 13:35:47
 *  Author: alexander
 */ 

#include "Encoder.h"

//sendData function doing 10 ms 120kHz
void sendData(void) {
	TCCR0 = 0b00011001; // Activate timer0 120kHz signal on PB 3
	_delay_us(1000);
	TCCR0 = 0b00001001;
}

void initTimer0 (void)
{
 	OCR0 = 14;				//start counting on 241: 255-14=241
 	TCCR0 = 0b00001001;		//no prescaler, CTC, internal clock, no toggle OC0
 	DDRB |= (1<<PB3);		// Set Port B3 as output
}