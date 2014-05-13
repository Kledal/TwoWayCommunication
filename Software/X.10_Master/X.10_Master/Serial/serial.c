/****************************************************
* "uart_int.c":                                     *
* Implementation file for the Meaga32 UART driver.  *
* RX interrupt can be enabled during initialization.*
* The driver does not handle the RX interrupts.     *
*                                                   *
*  STK500 setup:                                    *
*  Header "RS232 spare" connected to RXD/TXD:       *
*  RXD = PORTD, bit0                                *
*  TXD = PORTD, bit1                                *
*                                                   *
* Henning Hargaard, 3/11 2011                       *
*****************************************************/
#include <avr/io.h>
#include <stdlib.h>
#include "serial.h"
#include "../Encoder/Encoder.h"
#include "../Array_manipulation/Array_manipulation.h"

/*
 UART variables
*/
unsigned char uart_data[17] = "";
int uart_count = 0;

// Constants
#define XTAL 3686400

/*************************************************************************
USART initilization.
    Asyncronous mode.
	RX and TX enabled.
	No interrupts enabled.
	Number of Stop Bits = 1.
	No Parity.
	Baud rate = Parameter.
	Data bits = Parameter.
Parameters:
	BaudRate: Wanted Baud Rate.
	Databits: Wanted number of Data Bits.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_int  )
{
unsigned int TempUBRR;

  if ((BaudRate >= 110) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
  {
    // "Normal" clock, no multiprocesser mode (= default)
    UCSRA = 0b00100000;
    // No interrupts enabled
    // Receiver enabled
    // Transmitter enabled
    // No 9 bit operation
    UCSRB = 0b00011000;
    // Enable RX interrupts if wanted
    if (RX_int)
      UCSRB |= 0b10000000;
    // Asynchronous operation, 1 stop bit, no parity
    // Bit7 always has to be 1
    // Bit 2 and bit 1 controlles the number of databits
    UCSRC = 0b10000000 | (DataBit-5)<<1;
    // Set Baud Rate according to the parameter BaudRate:
    // Select Baud Rate (first store "UBRRH--UBRRL" in local 16-bit variable,
    //                   then write the two 8-bit registers seperately):
    TempUBRR = XTAL/(16*BaudRate) - 1;
    // Write upper part of UBRR
    UBRRH = TempUBRR >> 8;
    // Write lower part of UBRR
    UBRRL = TempUBRR;
  }
}


/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   return UCSRA & (1<<7);
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
  // Wait for new character received
  while ( (UCSRA & (1<<7)) == 0 )
  {}
  // Then return it
  return UDR;
}

/*************************************************************************
Awaits transmitter-register ready.
Then it send the character.
Parameter :
	Tegn : Character for sending.
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSRA & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR = Tegn;
}

/*************************************************************************
Sends 0-terminated string.
Parameter:
   Streng: Pointer to the string.
*************************************************************************/
void SendString(char* Streng)
{
  // Repeat untill zero-termination
  while (*Streng != 0)
  {
    // Send the character pointed to by "Streng"
    SendChar(*Streng);
    // Advance the pointer one step
    Streng++;
  }
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
      Tal: The integer to be converted and send.
*************************************************************************/
void SendInteger(int Tal)
{
  char array[7];
  // Convert the integer til an ASCII string (array), radix = 10
  itoa(Tal, array, 10);
  // - then send the string
  SendString(array);
}

/*
 This method is for UART
*/
ISR(USART_RXC_vect)
{
  char modtaget_tegn;
  modtaget_tegn = UDR;

  if (modtaget_tegn != 13) {
    uart_data[uart_count] = modtaget_tegn;
    uart_count++;
  }else{

    int isHandled = 1;

    switch (uart_data[0])
    {
      case 'O':
        SendString("O");
        isHandled = 0;
      break;
      case 'S':
        if (!getLoginStatus()){
          SendString("I");
        }else{
          SendString("L");
        }
        isHandled = 0;
      break;
    }


    if (isHandled) {
      clearArray(sendInfo);
      // Load uart data into sendinfo array.
      int i;
        for(i = 0;i<sizeof(sendInfo);i++) {
        sendInfo[i] = uart_data[i];
        }
      // Output sendinfo to serial.
      SendString(sendInfo);

      uart_count = 0;
      sendCount = 0;
      isSending = 1;
    }
    // Clear uart_data.
    clearArray(uart_data);
  }

}

/**************************************************/
