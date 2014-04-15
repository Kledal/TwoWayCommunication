/*
 * Decoder.c
 *
 * Created: 14-04-2014 13:36:13
 *  Author: alexander
 */ 

#include "Decoder.h"
#include "Array Manipulation/Array_manipulation.h"

unsigned char readDataBit() {
	char loadingBit = PA1;
	
	if (isLoadingCheckArray) {
		loadShiftLeft(startCheckArray, loadingBit);
	}
	
	//Now we check to see if we need to switch to address array
	if ((compareArray(startCheckArray, startbits)) == 1) {
		isLoadingCheckArray = 0;
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
	isLoadingCheckArray = 1;
	messageReady = 0;
	clearArray(startCheckArray);
}