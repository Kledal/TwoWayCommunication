﻿/*
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

/*
 Mode info
 0 = transmit
 1 = receive
*/
unsigned char mode = 0;
unsigned char startbit[4];
unsigned char addressbit[8];
unsigned char cmdbit[4];

unsigned char startbits[4] = {1, 1, 1, 0};

unsigned char sendInfo[16];
unsigned char sendCount = 0;
unsigned char isSending = 0;

int main(void)
{
	initInterrupts();
	initTimer0();
	
    while(1)
    {	
		// Not logged in, lets check
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
/*
 This command builds the senddata array and resets the pointer.
*/
void sendCommand(char address[8], char cmd[4])
{
	for (int i=0;i<sizeof(startbits);i++) {
		sendInfo[i] = startbits[i];
	}
	for (int i=0;i<sizeof(address);i++)
	{
		sendInfo[i + sizeof(startbits)] = address[i];
	}
	for (int i=0;i<sizeof(cmd);i++)
	{
		sendInfo[i + sizeof(address)] = cmd[i];
	}
	sendCount = 0;
	isSending = 1;
}

void initInterrupts() {
	// this enables interrupt 2. Which triggers on rising & falling.
	// Enables interrupt 0 for the encoder
	GICR |= (1<<INT1);
	MCUCR = (1<<ISC10); // Interrupt on rising and falling edge
}

/*
 This method is for the zero cross detection.
*/
ISR(INT1_vect) { 
	if (isSending) {
		unsigned char bit = sendInfo[sendCount];
		if (bit){
			sendData();
		}
		sendCount++;
		if (sendCount >= sizeof(sendInfo))
			isSending = 0;
	}
}

/*
 This method is for UART
*/
ISR (USART_RXC_vect)
{
	char modtaget_tegn;
	modtaget_tegn = UDR;
}