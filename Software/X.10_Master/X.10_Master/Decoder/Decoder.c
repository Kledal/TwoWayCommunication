/*
 * Decoder.c
 *
 * Created: 14-04-2014 13:36:13
 *  Author: alexander
 */ 

#include "Decoder.h"
#include "../Array_manipulation/Array_manipulation.h"
#include <avr/io.h>

unsigned char isListening = 0;
unsigned char isLoadingStartArray = 0;
unsigned char isLoadingAddressArray = 0;
unsigned char isLoadingCmdArray = 0;
unsigned char messageReady = 0;
unsigned char arraySizeCounter = 0;

unsigned char startbit[4] = "";
unsigned char addressbit[8] = "";
unsigned char cmdbit[4] = "";
unsigned char startbits[4] = {1, 1, 1, 0};

unsigned char readDataBit() {
	char loadingBit = PINA1;
	
	if (isLoadingStartArray) {
		loadShiftLeft(startbit, loadingBit);
	}
	
	//Now we check to see if we need to switch to address array
	if ((compareArray(startbit, startbits)) == 1) {
		isLoadingStartArray = 0;
		isLoadingAddressArray = 1;
	}
	
	if (isLoadingAddressArray) {
		loadShiftLeft(addressbit, loadingBit);
		arraySizeCounter++;
		
		if (arraySizeCounter == sizeof(addressbit)) {
			isLoadingAddressArray = 0;
			isLoadingCmdArray = 1;
			arraySizeCounter = 0;
		}
	}
	
	if (isLoadingCmdArray) {
		loadShiftLeft(cmdbit, loadingBit);
		arraySizeCounter++;
		
		if (arraySizeCounter == sizeof(cmdbit)) {
			isLoadingCmdArray = 0;
			arraySizeCounter = 0;
			messageReady = 1;
		}
	}		
}

void runCommand() {
	
}

void resetCheckValues() {
	isLoadingStartArray = 1;
	messageReady = 0;
}

void resetCommunicationArrays() {
	clearArray(startbit);
	clearArray(addressbit);
	clearArray(cmdbit);
}