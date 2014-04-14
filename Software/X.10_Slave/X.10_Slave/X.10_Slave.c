/* Created: 14-04-2014
 * Name: X.10_Slave.c
 * Version 0.1
 */ 

#include "Door.h"
#include <avr/io.h>

void changeStatus( int status );	//change this

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

void changeStatus( int status )
{
	
}