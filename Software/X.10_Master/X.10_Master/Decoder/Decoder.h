#ifndef DECODER_H_
#define DECODER_H_

#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>

/*
 Listening variables
*/
unsigned char isListening;
unsigned char isLoadingStartArray;
unsigned char isLoadingAddressArray;
unsigned char isLoadingCmdArray;
unsigned char messageReady;
unsigned char arraySizeCounter;

unsigned char startbit[4];
unsigned char addressbit[8];
unsigned char cmdbit[4];

unsigned char startbits[4];

// Serial Master-to-PC variable
extern char endByte;
int max_zero_cross;
int zero_cross;

void readDataBit();
void runCommand();
void resetCheckValues();
void resetCommunicationArrays();


#endif /* DECODER_H_ */