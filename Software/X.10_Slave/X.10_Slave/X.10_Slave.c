#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "Door/Door.h"
#include "Encoder/Encoder.h"
#include "Decoder/Decoder.h"
#include "Array_manipulation/Array_manipulation.h"
#include "Serial/serial.h"

/*
 Define main.c functions
*/
void initInterrupts();
void serialStatus();

/*
	IO Mapping:
		- PORT A - Input
			- PA0 - Data input
				-SW1 i debugging mode
		- PORT B - Input
			- PB2 - INT2 (Dør interrupt)
				- SW7
		- PORT C - LED Output
		- PORT D - Input
			- PD3 - INT1 (Zero interrupt)
				- SW0 i debugging mode
*/

int main(void)
{
	// We initiate the system
	initDoor();
	initInterrupts();
	initTimer0();
	InitUART(9600, 8, 1);
	sei();
	
	DDRD = 0x00;
	DDRA = 0x00;
	
	SendString("\n\r--- System Status ---\n\r");
	SendString("\n\rLytter efter startbit sekvens...\n\r");
	
    while(1)
    {
    }
}

void initInterrupts() {
	// this enables interrupt 1. Which triggers on rising & falling.
	// Enables interrupt 0 for the encoder
	GICR |= (1<<INT1) | (1<<INT2);
	
	// For real use: (Interrupt on falling and rising edge)
	MCUCR = 0b00000100;
	
	// For debugging: (Interrupt on falling edge)
	/*MCUCR = 0b00001000;*/
	
	MCUCSR = (0<<ISC2); // Interrupt INT 2 on falling edge
}

/*
 This method is for the zero cross detection.
*/
ISR(INT1_vect) {
	cli();
	if (getSendingStatus() == 1)
		sendDataBit();
		
	if (getListening() == 1)
		readDataBit();	

	sei();
}

void serialStatus() {
	int i;
	
	SendString("\n\r--- System Status ---\n\r");
	SendString("Start array: ");
	for (i=0; i< sizeof(startbit); i++)
		SendInteger(startbit[i]);

	SendString("\n\rAdresse array: ");
	for (i=0; i< sizeof(addressbit); i++)
		SendInteger(addressbit[i]);

	SendString("\n\rKommando array: ");
	for (i=0; i< sizeof(cmdbit); i++) 
		SendInteger(cmdbit[i]);
}