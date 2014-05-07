
#include "Array_manipulation.h"

void clearArray(unsigned char *arrayRef, int size) {
	int i;
	for(i=0; i<=size; i++)
	arrayRef[i] = 0;
}

void loadShiftLeft(unsigned char *arrayRef, int data, int size) {
	int i;
	for(i = 0; i<(size-1); i++)
		arrayRef[i] = arrayRef[i+1];

	arrayRef[i] = data;
}

char compareArray(unsigned char *arrayRef, unsigned char *arrayRef2, int size) {
	int i;
	for(i = 0; i<size; i++)
	{
		if (arrayRef[i] != arrayRef2[i]) {
			SendString("Det er ikke lig hinanden");
			return 0;
		}			
	}
	return 1;
}