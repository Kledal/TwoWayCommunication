/*
 * CountInterrupts.c
 *
 * Created: 07-04-2014 13:31:53
 *  Author: alexander
 */ 


#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"

int interrupts = 0;
int counting = 0;

// dont want to declare a .h file.
// so i just declared the function here.
void InitInterrupt();

unsigned char a;

int main(void)
{
	InitInterrupt();
	DDRB = 0xff; // Make PORTB output.
	PORTB = 0b11111111; // Sets all bits.
	
	InitUART(9600, 8, 1);
	
	sei(); //enables interrupts
	
	
    while(1)
	{
		if (counting) {
			_delay_ms(1000);
			counting = 0;
			SendString("Der blev detected ");
			SendInteger(interrupts);
			SendString(" zero detections.");
		}
		PORTB = ~interrupts;
		
    }
}


void InitInterrupt() {
	MCUCR = 1<<ISC00 && 1<<ISC11;  // INT0:Falling edge
	GICR |= 0b11000000;  //enable interrupt 0 AND INT1
}

ISR (USART_RXC_vect)
{
	char modtaget_tegn;
	// Aflæs UART modtage-register
	modtaget_tegn = UDR;
	SendChar(modtaget_tegn);
}

ISR(INT0_vect) { //PORT D ben 2
	//increase countet interrupts
	if (counting == 1)
		interrupts++;
}
ISR(INT1_vect) { //PORT D ben 3
	counting = 1; // start counting
	interrupts = 0; // reset counts
}