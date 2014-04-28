
#ifndef DECODER_H_
#define DECODER_H_

#define F_CPU 3686400UL
#include <util/delay.h>
#include <avr/io.h>

unsigned char isListening;
unsigned char isLoadingStartArray;
unsigned char isLoadingAddressArray;
unsigned char isLoadingCmdArray;
unsigned char arraySizeCounter;

unsigned char startbit[4];
unsigned char addressbit[8];
unsigned char cmdbit[4];
unsigned char startbits[4];

void readDataBit();
void runCommand();
void resetListening();
char getListening();
void checkSendMessage();
void loadStartArray();
void loadAddressArray();
void loadCommandArray();
void checkArrayStatus();

#endif