/*
 * Decoder.h
 *
 * Created: 14-04-2014 13:36:21
 *  Author: alexander
 */ 


#ifndef DECODER_H_
#define DECODER_H_

/*
 Listening variables
*/
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


unsigned char readDataBit();
void runCommand();
void resetCheckValues();
void resetCommunicationArrays();


#endif /* DECODER_H_ */