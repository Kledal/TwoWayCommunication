/*
 * Encoder.c
 *
 * Created: 14-04-2014 13:35:47
 *  Author: alexander
 */ 

#include "Encoder.h"

//sendData function doing 10 ms 120kHz
void sendData(void) {
	TIMSK = (1<<TOIE0);			//enable Timer0 overflow interrupt
	_delay_ms(1);				//1 ms delay
	TIMSK = (0<<TOIE0);			//disable Timer0 overflow interrupt
}

void initTimer0 (void)
{
 TCNT0 = 240;					//start counting on 240: 255-15=240
 TCCR0 = 0b00000001;			//no prescaler, normal mode, internal clock
 
 //enable Port X as output
}

ISR (TIMER0_OVF_vect)
{
	//toggler ben XXX
}