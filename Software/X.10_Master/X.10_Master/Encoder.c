/*
 * Encoder.c
 *
 * Created: 14-04-2014 13:35:47
 *  Author: alexander
 */ 

//sendData skal smide 120 kHz ud på ben XXX i 10 ms. 
void sendData(void) {
	//enable ISR for timer 0
	//delay 10 ms
	//disable ISR for timer 0
}

void initTimer0 (void)
{
 TCNT0 = 240;					//start med at tælle på 255: 255-15=240
 TCCR0 = 0b00000001;			//prescalar 1, normal mode
}

ISR (TIMER0_OVF_vect)
{
	//toggler ben XXX
	TIFR = 0b00000001;
}