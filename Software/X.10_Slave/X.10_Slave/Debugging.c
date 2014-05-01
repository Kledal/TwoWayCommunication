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
	Debugging strings 
*/
char systemStatus[] = "\n\r--- System Status ---\n\r";
char startArray[] = "Start array:";
char adresseArray[] = "\n\rAdresse array:";
char commandoArray[] = "\n\rKommando array:";

/*
	IO Mapping:
		- PORT A - Input
			- PA1 - Data input
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
	
	SendString(systemStatus);
	
	PORTC = 0b00000001;
	
    while(1)
    {
		/*
			Ideen med denne alternative "debugging" mainfunktion er
			at sætte en switch (SW1) til at være vores "zero" interrupt og
			sætte en anden switch (SW2) til at være vores data input. Så når
			man trykker SW1 ind går den ind i vores interrupt i bunden af denne fil.
			Der aflæser den på SW2. Hvis SW2 er trykket ind læser den 1. Hvis den ikke er
			læser den 0.
			Hver gang den har  aflæst et bit skal den udskrive nogle informationer
			til konsollen. Disse informationer kunne være:
				- Indholdet af alle arrays
				- Antallet af registerede interrupts
				- Andre variabler
		*/
    }
}

void initInterrupts() {
	// this enables interrupt 1. Which triggers on rising & falling.
	// Enables interrupt 0 for the encoder
	GICR |= (1<<INT1) | (1<<INT2);
	MCUCR = 0b00001000; // In debugging mode this only interrupts on falling edge. Normal mode: Interrupt INT 1 on rising and falling edge.
	MCUCSR = (0<<ISC2); // Interrupt INT 2 on falling edge
}

/*
 This method is for the zero cross detection.
*/
ISR(INT1_vect) {
	PORTC = 0b00000011;
	if (getSendingStatus() == 1)
		sendDataBit();
		
	if (getListening() == 1)
		readDataBit();	
	PORTC = 0b00000111;
	serialStatus();
}

void serialStatus() {
	int i;
	
	PORTC = 0b00001111;
	
	SendString(systemStatus);
	SendString(startArray);
	for (i=0; i< sizeof(startbit); i++) {
		SendChar(' ');
		SendInteger(startbit[i]);
		SendChar(',');
	}
	SendString(adresseArray);
	for (i=0; i< sizeof(addressbit); i++) {
		SendChar(' ');
		SendInteger(addressbit[i]);
		SendChar(',');
	}
	SendString(commandoArray);
	for (i=0; i< sizeof(cmdbit); i++) {
		SendChar(' ');
		SendInteger(cmdbit[i]);
		SendChar(',');
	}	
}

