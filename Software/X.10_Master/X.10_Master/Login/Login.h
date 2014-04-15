/*
 * Created: 14-04-2014
 * Name: Login.h
 * Version: 0.2
 */ 


#ifndef LOGIN_H_
#define LOGIN_H_

#include <avr/io.h>

unsigned char okPw( void );
void okLogin( void );
unsigned char getLoginStatus( void );


#endif /* LOGIN_H_ */