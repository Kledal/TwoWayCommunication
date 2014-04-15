#define F_CPU 3686400UL
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
 Properties for this unit
*/
unsigned char myAddressbit[8] = {1, 1, 0, 0, 1, 1, 0, 0};
unsigned char publicAddressbit[8] = {1, 0, 1, 0, 1, 0, 1, 0};

int main(void)
{
	initInterrupts();
	initTimer0();
	sei();
	
    while(1)
    {
		if ((messageReady == 1) && ((compareArray(addressbit, myAddressbit) == 1) || (compareArray(addressbit, publicAddressbit) == 1)))  {
			runCommand();
			resetCommunicationArrays();
			resetCheckValues();
		}
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
	sendData();
	if (isSending) {
		unsigned char bit = sendInfo[sendCount];
		//we need to check against string, because that is what we are receiving over
		if (bit == '1')
			sendData();

		sendCount++;
		if (sendCount > sizeof(sendInfo))
			isSending = 0;
	}
	if (isListening)
		readDataBit();
}