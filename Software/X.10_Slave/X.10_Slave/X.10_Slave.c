/* Created: 14-04-2014
 * Name: X.10_Slave.c
 * Version 0.2
 */
#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Door/Door.h"

/*
Mode info:
0 = transmit
1 = receive
Default mode = receive
*/
unsigned char mode = 1;

/*
declare comparable arrays
*/
unsigned char startbit[ 4 ] = { 0 };
unsigned char addressbit[ 8 ] = { 0 };
unsigned char cmdbit[ 4 ] = { 0 };

/*
declare startbits
*/
unsigned char startbits[ 4 ] = { 1 1 1 0 };

/*
Transmit variables
*/
unsigned char sendInfo[ 16 ] = { 0 };
unsigned char sendCount = 0;
unsigned char isSending = 0;


//void changeStatus( int status );	//change this

int main(void)
{
	// for mode: transmit = 0, receive = 1
	int mode = 1;				// slave default mode = 1
	int startbit[4] = {1110};	// startbits
	int addressbit[8] = {0};	// !!!!!!! ???? address for master?
	int cmdbit[4] = { 0 };		// commandbits

    while(1)
    {

    }
}
