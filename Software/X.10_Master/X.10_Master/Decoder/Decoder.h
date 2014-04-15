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
unsigned char isLoadingCheckArray = 0;
unsigned char isLoadingAddressArray = 0;
unsigned char isLoadingCmdArray = 0;
unsigned char messageReady = 0;
unsigned char arraySizeCounter = 0;
unsigned char startCheckArray[4] =""; //For listening mode. Checking incoming bits vs. startbit array

unsigned char readDataBit();
void runCommand();
void resetCheckValues();


#endif /* DECODER_H_ */