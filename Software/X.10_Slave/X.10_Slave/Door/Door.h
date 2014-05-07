
#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int status_;

void initDoor ( void );
void changeStatus( int status );	//from slave to door
void toggleDoor( void );
int getStatus( void );
void setStatus( void );