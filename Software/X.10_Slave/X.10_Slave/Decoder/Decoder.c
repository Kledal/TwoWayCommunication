#include "../Decoder/Decoder.h"
#include "../Encoder/Encoder.h"
#include "../Door/Door.h"
#include "../Array_manipulation/Array_manipulation.h"

// Listening variables
unsigned char isListening = 0;
unsigned char isLoadingStartArray = 0;
unsigned char isLoadingAddressArray = 0;
unsigned char isLoadingCmdArray = 0;
unsigned char messageReady = 0;
unsigned char arraySizeCounter = 0;

// Loading arrays
unsigned char startbit[4] = "";
unsigned char addressbit[8] = "";
unsigned char cmdbit[4] = "";
unsigned char startbits[4] = {1, 1, 1, 0};
	
// Command arrays
unsigned char aabenArray[4] = {0, 1, 0, 1};
unsigned char lukArray[4] = {0, 1, 1, 1};
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
	char loadingBit = 0;
	
	/*PORTC = 0b11111000;*/
	
	for(i=0;i<100;i++) {
		loadingBit |= PINA1;
		_delay_us(5);
	}
	
	//DEBUG
	if (PINA & (1<<PA1)){
		PORTC = 0b01111111;
	}else{
		PORTC = 0b10000000;
	}
	PORTC = PINA;
	//DEBUG
	
	
	if (isLoadingStartArray) {
		/*PORTC = 0b11110000;*/
		loadShiftLeft(startbit, loadingBit);
		//PORTC &= (startbit[0]<<PC0) | (startbit[1]<<PC1) | (startbit[2]<<PC2) | (startbit[3]<<PC3);
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
		isListening = 0;
		if (getStatus() == 1)
			sendCommand(masterAddress, aabenStatus);
		if (getStatus() == 0)
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

void setListening(char sat) {
	isListening = sat;
}

char getListening() {
	return isListening;
}

void checkSendMessage() {
	if ((messageReady == 1) && ((compareArray(addressbit, myAddressbit) == 1) || (compareArray(addressbit, publicAddressbit) == 1)))  {
		runCommand();
		resetCommunicationArrays();
		resetCheckValues();
	}
}

void setIsLoadingStartArray(char set) {
	isLoadingStartArray = set;
}