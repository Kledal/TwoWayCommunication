/* Created: 14-04-2014
 * Name: Door.c
 * Version 0.1
 */

#include "../Door/Door.h"

unsigned char status_= 0; //Status = 0: closed, status = 1: open

void initDoor ( void )
{
	DDRC = 0xFF;		//PORTC set as output
	PORTC = 0xFF;		//Turn off all LEDS
}

void changeStatus( unsigned char status )	//from slave to door
{
	if (status != status_)
	{
		toggleDoor();
	}
	
}

void toggleDoor( void )
{
	unsigned char mask;
	
	if (status_ == 1)		//closing
	{
		
		int i = 0;
		for (i; i<8; i++)
		{
			mask = ( 0b11111110 << i);
			PORTC = PINC & mask;
			_delay_ms(375);
		}
	
		getStatus();			//Changes status_ to the correct value
	}
	else						//opening
	{
		_delay_ms(375);
		int i = 0;
		for (i; i<8; i++)
		{
			mask = ( 0b10000000 >> i);
			PORTC = PINC | mask;
			_delay_ms(375);
		}
		
		getStatus();			//Changes status_ to the correct value
	}
}

unsigned char getStatus( void )
{
	if( PINC )
		status_ = 1;
	else
		status_ = 0;
		
	return status_;
}

ISR(INT2_vect)		//INT2 = PB2
{
// 	toggleDoor();
// 	getStatus();
	 // Lasse og Lars kode
	if(status_ == 0)
	{
		PORTC = 0b11000000;		//simulates a person forcing the door open.
	}
	
}