#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Login/Login.h"
#include "Encoder/Encoder.h"
#include "Decoder/Decoder.h"
#include "Serial/serial.h"
#include "Array_manipulation/Array_manipulation.h"

/*
 Define main.c functions
*/
void initInterrupts();

int main(void)
{
	InitUART(9600, 8, 1);
	initInterrupts();
	initTimer0();
	sei();
	
    while(1)
    {
		// Not logged in, lets check -- *** needs to be a while loop in a while loop ***
		// if the DE-2 is outputting
		if (!getLoginStatus()) {

		}
		/*
		 We are logged in, lets process new data.
		*/
		if (getLoginStatus()) {
			SendString("k");	//Communicates to that ATMega is ready to send data
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
	cli();
	sendData();
	
	if (getSendingStatus() == 1)
		sendDataBit();
		
	if (getListening() == 1)
		readDataBit();
}
