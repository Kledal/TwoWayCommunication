/*
 * Decoder.c
 *
 * Created: 14-04-2014 13:36:13
 *  Author: alexander
 */ 

#include "Decoder.h"

unsigned char readDataBit() {
	if (isLoadingCheckArray) {
		// Pseudo: If theres a 120 kHz signal. Add '1' to startCheckArray. Else add '0'
	}
	
	//Now we check to see if we need to switch to address array
	if (memcmp(startbits, startCheckArray, sizeof(startbits)) == 0) {
		isLoadingCheckArray = 0;
		isLoadingAddressArray = 1;
	}
	
	if (isLoadingAddressArray) {
		// Pseudo: If theres a 120 kHz signal. Add '1' to addressbit. Else add '0'
		arraySizeCounter++;
		
		if (arraySizeCounter == sizeof(addressbit)) {
			isLoadingAddressArray = 0;
			isLoadingCmdArray = 1;
			arraySizeCounter = 0;
		}
	}
	
	if (isLoadingCmdArray) {
		// Pseudo: If theres a 120 kHz signal. Add '1' to addressbit. Else add '0'
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
	isLoadingCheckArray = 1;
	messageReady = 0;
	startCheckArray[4] ="";
}