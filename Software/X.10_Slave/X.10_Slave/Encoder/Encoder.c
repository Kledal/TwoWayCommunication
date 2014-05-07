#include "../Encoder/Encoder.h"
#include "../Decoder/Decoder.h"

/*
 Send variables
*/
unsigned char sendInfo[17] = "";
unsigned char sendCount = 0;
unsigned char isSending = 0;
unsigned char startSequence[4] = {1, 1, 1, 0};


//sendData function doing 10 ms 120kHz
void sendData(void) {
	TCCR0 = 0b00011001; // Activate timer0 120kHz signal on PB 3
	_delay_us(1000);
	TCCR0 = 0b00001001;
}

void initTimer0 (void)
{
 	OCR0 = 14;				//start counting on 241: 255-14=241
 	TCCR0 = 0b00001001;		//no prescaler, CTC, internal clock, no toggle OC0
 	DDRB |= (1<<PB3);		// Set Port B3 as output
}

/*
 This command builds the senddata array and resets the pointer.
*/
void sendCommand(char address[8], char cmd[4])
{
	for (int i=0;i<sizeof(startSequence);i++) {
		sendInfo[i] = startSequence[i];
	}
	for (int i=0;i<sizeof(address);i++)
	{
		sendInfo[i + sizeof(startSequence)] = address[i];
	}
	for (int i=0;i<sizeof(cmd);i++)
	{
		sendInfo[i + sizeof(address)] = cmd[i];
	}
	sendCount = 0;
	isSending = 1;
}

char getSendingStatus() {
	return isSending;
}

void sendDataBit() {
	unsigned char bit = sendInfo[sendCount];
	//we need to check against string, because that is what we are receiving over
	if (bit == '1')
		sendData();

	sendCount++;
	if (sendCount > sizeof(sendInfo))
		isSending = 0;
	
	
}