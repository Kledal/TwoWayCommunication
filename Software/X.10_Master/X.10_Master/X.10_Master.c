/*
 * X.c
 *
 * Created: 14-04-2014 13:23:30
 *  Author: Projekt gruppe 2
 */ 


#include <avr/io.h>

/*
 Mode info
 0 = trasmit
 1 = receive
*/
int mode;
int startbit[4];
int addressbit[4];
int cmdbit[4];

int main(void)
{
    while(1)
    {
         
    }
}
void sendCommand(int address[4], int cmd[4])
{
	
}

ISR (USART_RXC_vect)
{
	char modtaget_tegn;
	modtaget_tegn = UDR;
}