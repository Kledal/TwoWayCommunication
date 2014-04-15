/* Created: 14-04-2014
 * Name: Door.h
 * Version 0.1
 */

#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void initDoor ( void );

void changeStatus( unsigned char status );	//from slave to door

void toggleDoor( void );

unsigned char getStatus( void );