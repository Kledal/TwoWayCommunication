#include "../Decoder/Decoder.h"
#include "../Encoder/Encoder.h"
#include "../Array_manipulation/Array_manipulation.h"
#include "../Serial/serial.h"

// Listening variables
unsigned char isListening = 0;
unsigned char isLoadingStartArray = 1;
unsigned char isLoadingAddressArray = 0;
unsigned char isLoadingCmdArray = 0;
unsigned char arraySizeCounter = 0;

// Serial Master-to-PC variable
char endByte = 13;

// Number of zero cross without startbit, before quitting listning mode
int max_zero_cross = 50;
int zero_cross = 0;

// Loading arrays
unsigned char startbit[4] = {0,0,0,0};
unsigned char addressbit[8] = {0,0,0,0,0,0,0,0};
unsigned char cmdbit[4] = {0,0,0,0};
unsigned char startbits[4] = {1, 1, 1, 0};

// Properties for this unit (Master)
unsigned char myAddressbit[8] = {0, 0, 1, 1, 1, 1, 0, 0};
unsigned char publicAddressbit[8] = {1, 0, 1, 0, 1, 0, 1, 0};

void readDataBit() {
	
	int loadingBit = 0;
	
	_delay_us(200);

	loadingBit = (PINA & 0b00000001);

	//SendInteger(loadingBit);
	//SendChar( (char)13 );
	
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
	
	if (zero_cross > max_zero_cross && isLoadingStartArray) {
		resetListening();
	}	
	
	// We check to see if we need to switch to address array
	checkArrayStatus();
	zero_cross++;
}

void checkArrayStatus() {
	if (isLoadingStartArray) {
		if ((compareArray(startbit, startbits, 4)) == 1) {
			isLoadingStartArray = 0;
			isLoadingAddressArray = 1;
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
	int i;
	
	SendString("S:");
	for (i=0; i<4; i++)
		SendInteger(cmdbit[i]);
	
	SendChar(endByte);
}

void resetListening() {
	clearArray(startbit, 4);
	clearArray(addressbit, 8);
	clearArray(cmdbit, 4);
	isLoadingStartArray = 1;
	zero_cross = 0;
	isListening = 0;
	
	sendReadyCommand();
}

char getListening() {
	return isListening;
}

void checkSendMessage() {
	if ((compareArray(addressbit, myAddressbit, 8) == 1) || (compareArray(addressbit, publicAddressbit, 8) == 1))
		runCommand();
		
	resetListening();
}