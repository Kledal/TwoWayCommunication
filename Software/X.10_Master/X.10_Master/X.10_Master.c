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
void sendReadyCommand();

/*
	IO Mapping (STK-500):
		- PORT A - Input
			- PA0 - Data input
			- PA1 - okPw
			- PA2 - okLogin
		- PORT B - Output
			- PB3 - Data output
		- PORT D - Input
			- PD3 - INT1 (Zero interrupt)
	IO Mapping (DE2):
		- GPIO_1[0] - okLogin
		- GPIO_1[1] - okPw
		- GPIO_1[12] - Ground
*/

int main(void)
{
	InitUART(9600, 8, 1);
	initInterrupts();
	initTimer0();
	sei();

    while(1)
    {
    	while(!okPw()) {}
		while(!okLogin()) {}
    }
}

void sendReadyCommand() {
	SendString("R");
	SendChar(endByte);
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
	if (isSending) {
		unsigned char bit = sendInfo[sendCount];
		//we need to check against string, because that is what we are receiving over
		if (bit == '1')
			sendData();
			
		sendCount++;
		if (sendCount > sizeof(sendInfo))
		{
			isSending = 0;
			if (changeStatus) {
				isListening = 1;
				changeStatus = 0;
			}else{ // we are not changing status, send K back to tell we are done sending.
				//sendReadyCommand();
			}
		}
	}
	if (isListening)
		readDataBit();

	sei();
}
