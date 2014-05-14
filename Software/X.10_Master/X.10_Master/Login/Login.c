/* 
 * Created: 14-04-2014
 * Name: Login.c
 * Version: 0.2
 */ 
#include "Login.h"

//default is 0. 0 = not logged in
unsigned char loginStatus = 0;
unsigned char pwStatus = 0;

unsigned char okPw( void ) 
{
	//reads PA1
	pwStatus = ( PINA & 0b00000010 );		//pwStatus = 1 if PA1 = high.
	return pwStatus;
}
unsigned char okLogin( void ) 
{
	//Reads PA2
	loginStatus = ( PINA & 0b00000100 );	//loginStatus = 1 if PA2 = high.
	return loginStatus;
}
unsigned char getLoginStatus( void ) 
{
	return loginStatus;
}
int getPwStatus( void ) {
	return (int)pwStatus;
}