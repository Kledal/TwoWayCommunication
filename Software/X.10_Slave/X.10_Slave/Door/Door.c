/* Created: 14-04-2014
 * Name: Door.c
 * Version 0.1
 */

#include "../Door/Door.h"

int status_= 1; //Status_ = 0: closed, status_ = 1: open

void initDoor ( void )
{
	DDRC = 0xFF;		//PORTC set as output
	PORTC = 0xFF;		//Turn off all LEDS
}

void changeStatus( int status )	//from slave to door
{
// 	SendString("\n\rStatus variabel: ");
// 	SendInteger(status);
// 	SendString("\n\rStatus_ variabel: ");
// 	SendInteger(status_);
// 	SendString("\n\r");
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
		SendString("\n\rDoren lukker...\n\r");
		int i = 0;
		for (i; i<8; i++)
		{
			mask = ( 0b11111110 << i);
			PORTC = PINC & mask;
			_delay_ms(375);
		}
		SendString("\n\rDoren er lukket\n\r");
		setStatus();			//Changes status_ to the correct value
	}
	else						//opening
	{
		SendString("\n\rDoren aabner...\n\r");
		_delay_ms(375);
		int i = 0;
		for (i; i<8; i++)
		{
			mask = ( 0b10000000 >> i);
			PORTC = PINC | mask;
			_delay_ms(375);
		}
		SendString("\n\rDoren er aaben\n\r");
		setStatus();			//Changes status_ to the correct value
	}
}

int getStatus( void )
{			
	return status_;
}

void setStatus( void )
{
		//SendString("\n\rStatus_ aendres...\n\r");
		if( PINC ) {
			//SendString("\n\rSaettes til 1\n\r");
			status_ = 1;
		}
		else {
			//SendString("\n\rSaettes til 0\n\r");
			status_ = 0;
		}
}

ISR(INT2_vect)		//INT2 = PB2
{
	if(status_ == 0)
	{
		PORTC = 0b11000000;		//simulates a person forcing the door open.
		setStatus();
	}
	
}