
#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char status_;

void initDoor ( void );
void changeStatus( unsigned char status );	//from slave to door
void toggleDoor( void );
unsigned char getStatus( void );