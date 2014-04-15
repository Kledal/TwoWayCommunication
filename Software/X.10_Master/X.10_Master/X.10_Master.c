/*
 * X.c
 *
 * Created: 14-04-2014 13:23:30
 *  Author: Projekt gruppe 2
 */


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
 Mode info
 0 = transmit
 1 = receive
*/
unsigned char mode = 0;
// unsigned char startbit[4] = "";
// unsigned char addressbit[8] = "";
// unsigned char cmdbit[4] = "";

/*
 Properties for this unit
*/
unsigned char myAddressbit[8] = {0, 0, 1, 1, 1, 1, 0, 0};
unsigned char publicAddressbit[8] = {1, 0, 1, 0, 1, 0, 1, 0};

/*
 Declare startbits
*/

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

		}
    }
}


void listening()
{
	isListening = 1;

	while(isListening == 1) {
		// If the address matches the address of this unit, or the public address.
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
		if (bit == '1'){
			sendData();
		}
		sendCount++;
		if (sendCount > sizeof(sendInfo))
			isSending = 0;
	}
	if (isListening) {
		readDataBit();
	} // End if (isListening)
}
