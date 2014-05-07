#include "../Decoder/Decoder.h"
#include "../Encoder/Encoder.h"
#include "../Door/Door.h"
#include "../Array_manipulation/Array_manipulation.h"
#include "../Serial/serial.h"

// Listening variables
unsigned char isListening = 1;
unsigned char isLoadingStartArray = 1;
unsigned char isLoadingAddressArray = 0;
unsigned char isLoadingCmdArray = 0;
unsigned char arraySizeCounter = 0;

// Loading arrays
unsigned char startbit[4] = {0,0,0,0};
unsigned char addressbit[8] = {0,0,0,0,0,0,0,0};
unsigned char cmdbit[4] = {0,0,0,0};
unsigned char startbits[4] = {1, 1, 1, 0};
	
// Command arrays
unsigned char aabenArray[4] = {0, 1, 0, 1};
unsigned char lukArray[4] = {0, 0, 1, 1};
unsigned char statusArray[4] = {1, 1, 1, 1};

// Sequence arrays for sending status to master
unsigned char aabenStatus[4] = {1, 0, 1, 0};
unsigned char lukketStatus[4] = {0, 1, 0, 1};

// Address for master unit
unsigned char masterAddress[8] = {0, 0, 1, 1, 1, 1, 0, 0};

// Properties for this unit
unsigned char myAddressbit[8] = {1, 1, 0, 0, 1, 1, 0, 0};
unsigned char publicAddressbit[8] = {1, 0, 1, 0, 1, 0, 1, 0};

void readDataBit() {
	int i;
	int loadingBit = 0;
	
	// We wait 100*5 us for input on PINA1. If, at any point, we measure 5V, our loadingBit equals 1
// 	for(i=0;i<100;i++) {
// 		loadingBit |= PINA1;
// 		_delay_us(5);
// 	}

	loadingBit = (PINA & 0b00000001);	
	
	if (isLoadingStartArray) {
		loadShiftLeft(startbit, loadingBit, 4);
	}
	
	if (isLoadingAddressArray) {
		loadShiftLeft(addressbit, loadingBit, 8);
		arraySizeCounter++;
	}		
	
	if (isLoadingCmdArray) {
		loadShiftLeft(cmdbit, loadingBit, 4);
		arraySizeCounter++;
	}	
		
	// We check to see if we need to switch to address array
	checkArrayStatus();
}

void checkArrayStatus() {
	if (isLoadingStartArray) {
		if ((compareArray(startbit, startbits, 4)) == 1) {
			isLoadingStartArray = 0;
			isLoadingAddressArray = 1;
			SendString("\n\rStartbit sekvens detecteret. Laeser adresse og kommando...\n\r");
			return;
		}	
	}	
	
	if (isLoadingAddressArray) {
		if (arraySizeCounter == sizeof(addressbit)) {
			isLoadingAddressArray = 0;
			isLoadingCmdArray = 1;
			arraySizeCounter = 0;
			return;
		}			
	}
	
	if(isLoadingCmdArray) {	
		if (arraySizeCounter == sizeof(cmdbit)) {
			isLoadingCmdArray = 0;
			arraySizeCounter = 0;
			checkSendMessage();
		}
	}	
}

void runCommand() {
	if (compareArray(cmdbit, aabenArray, 4))
		changeStatus(1);
		
	if (compareArray(cmdbit, lukArray, 4))
		changeStatus(0);

	if (compareArray(cmdbit, statusArray, 4)) {
		isListening = 0;
		if (getStatus() == 1)
			sendCommand(masterAddress, aabenStatus);
		if (getStatus() == 0)
			sendCommand(masterAddress, lukketStatus);
		SendString("\n\rSender doer status til master...\n\r");
	}
}

void resetListening() {
	clearArray(startbit, 4);
	clearArray(addressbit, 8);
	clearArray(cmdbit, 4);
	isLoadingStartArray = 1;
	SendString("\n\rLytter efter startbit sekvens...\n\r");
}

char getListening() {
	return isListening;
}

void checkSendMessage() {
	if ((compareArray(addressbit, myAddressbit, 8) == 1) || (compareArray(addressbit, publicAddressbit, 8) == 1)) {
		SendString("\n\rKommandoen er til denne enhed\n\r");
		runCommand();
	} else {
		SendString("\n\rKommandoen er ikke til denne enhed\n\r");
	}
	resetListening();
}