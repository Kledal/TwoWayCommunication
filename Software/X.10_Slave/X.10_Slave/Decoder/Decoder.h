/*
 * Decoder.h
 *
 * Created: 14-04-2014 13:36:21
 *  Author: alexander
 */ 


#ifndef DECODER_H_
#define DECODER_H_

#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>

/*
 Listening variables
*/
extern unsigned char isListening;
extern unsigned char isLoadingStartArray;
extern unsigned char isLoadingAddressArray;
extern unsigned char isLoadingCmdArray;
extern unsigned char messageReady;
extern unsigned char arraySizeCounter;

extern unsigned char startbit[4];
extern unsigned char addressbit[8];
extern unsigned char cmdbit[4];

extern unsigned char startbits[4];


void readDataBit();
void runCommand();
void resetCheckValues();
void resetCommunicationArrays();


#endif /* DECODER_H_ */