#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Door/Door.h"
#include "Encoder/Encoder.h"
#include "Decoder/Decoder.h"
#include "Array_manipulation/Array_manipulation.h"
#include "Serial/serial.h"

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
		/*
			Ideen med denne alternative "debugging" mainfunktion er
			at s�tte en switch (SW1) til at v�re vores "zero" interrupt og
			s�tte en anden switch (SW2) til at v�re vores data input. S� n�r
			man trykker SW1 ind g�r den ind i vores interrupt i bunden af denne fil.
			Der afl�ser den p� SW2. Hvis SW2 er trykket ind l�ser den 1. Hvis den ikke er
			l�ser den 0.
			Hver gang den har  afl�st et bit skal den udskrive nogle informationer
			til konsollen. Disse informationer kunne v�re:
				- Indholdet af alle arrays
				- Antallet af registerede interrupts
				- Andre variabler
		*/
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
