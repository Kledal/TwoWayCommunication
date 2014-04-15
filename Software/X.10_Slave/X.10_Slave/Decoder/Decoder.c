#include "Decoder.h"
#include "Encoder.h"
#include "Door.h"
#include "../Array_manipulation/Array_manipulation.h"

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
unsigned char aabenArray[4] = {0, 1, 0, 1};
unsigned char lukArray[4] = {0, 1, 1, 1};
unsigned char statusArray[4] = {1, 1, 1, 1};
	
unsigned char aabenStatus[4] = {1, 0, 1, 0};
unsigned char lukketStatus[4] = {0, 1, 0, 1};
	
unsigned char masterAddress[8] = {0, 0, 1, 1, 1, 1, 0, 0}

void readDataBit() {
	int i;
	char loadingBit = 0;
	
	for(i=0;i<100;i++) {
		char loadingBit |= PINA1;
		_delay_us(1);
	}		
	
	if (isLoadingStartArray) {
		loadShiftLeft(startbit, loadingBit);
	}
	
	//Now we check to see if we need to switch to address array
	if ((compareArray(startbit, startbits)) == 1) {
		isLoadingStartArray = 0;
		isLoadingAddressArray = 1;
		return;
	}
	
	if (isLoadingAddressArray) {
		loadShiftLeft(addressbit, loadingBit);
		arraySizeCounter++;
		
		if (arraySizeCounter == sizeof(addressbit)) {
			isLoadingAddressArray = 0;
			isLoadingCmdArray = 1;
			arraySizeCounter = 0;
			return;
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
	if (compareArray(cmdbit, aabenArray)) {
		changeStatus(1);
	}
	if (compareArray(cmdbit, lukArray)) {
		changeStatus(0);
	}
	if (compareArray(cmdbit, statusArray)) {
		if (status_ == 1)
			sendCommand(masterAddress, aabenStatus);
		if (status_ == 0)
			sendCommand(masterAddress, lukketStatus);
	}
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