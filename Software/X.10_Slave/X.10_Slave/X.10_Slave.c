﻿#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Door/Door.h"
#include "Encoder/Encoder.h"
#include "Decoder/Decoder.h"
#include "Array_manipulation/Array_manipulation.h"

/*
 Define main.c functions
*/
void initInterrupts();

/*
 Properties for this unit is now in Decoder
*/

int main(void)
{
	// We initiate the system
	initDoor();
	initInterrupts();
	initTimer0();
	sei();
	
	DDRD = 0x00;
	DDRA = 0x00;
	
    while(1)
    {
		// Slaves always boot into listening mode
		// In this while(1) loop we wait for interrupts
		// The Decoder handles when this unit is allowed to send
    }
}

void initInterrupts() {
	// this enables interrupt 2. Which triggers on rising & falling.
	// Enables interrupt 0 for the encoder
	GICR |= (1<<INT1);
	MCUCR = (1<<ISC10) | (0<<ISC00); // Interrupt on rising and falling edge
}

/*
 This method is for the zero cross detection.
*/
ISR(INT1_vect) {
	if (getSendingStatus() == 1)
		sendDataBit();
		
	if (getListening() == 1)
		readDataBit();	
}