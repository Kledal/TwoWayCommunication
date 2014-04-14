/* 
 * Created: 14-04-2014
 * Name: Login.c
 * Version: 0.2
 */ 

//default is 0. 0 = not logged in
unsigned char loginStatus = 0;

unsigned char okPw( void ) 
{
	//reads PA1
	unsigned char pwStatus = 0;
	pwStatus = ( PINA & 0b00000010 );		//pwStatus = 1 if PA1 = high.
	return pwStatus;
}
void okLogin( void ) 
{
	//Reads PA2
	loginStatus = ( PINA & 0b00000100 );	//loginStatus = 1 if PA2 = high.
}
int getLoginStatus( void ) 
{
	return loginStatus;
}