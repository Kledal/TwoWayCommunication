
#include "Array_manipulation.h"

void clearArray(unsigned char *arrayRef) {
	int i;
	for(i=0; i<=sizeof(arrayRef); i++)
	arrayRef[i] = 0;
}

void loadShiftLeft(unsigned char *arrayRef, char data) {
	int i;
	for(i = 0; i<sizeof(arrayRef)-1; i++)
		arrayRef[i] = arrayRef[i+1];
	i = sizeof(arrayRef)-1;
	arrayRef[i] = data;
}

char compareArray(unsigned char *arrayRef, unsigned char *arrayRef2) {
	int i;
	for(i = 0; i<=sizeof(arrayRef); i++)
	{
		if (arrayRef[i] != arrayRef2[i])
			return 0;
	}
	return 1;
}