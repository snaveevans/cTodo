#include <stdio.h>
#include <stdlib.h>
#include "random.h"

char convertToHex(int value) {
	if (value > 15) {
		// error out
	}
	char hex [4];
	sprintf(hex, "%x", value);
	return hex[0];
}

char * newGuid() {
	int size = 36;
	char *guid;
	guid = (char *)malloc(sizeof(char)*size);
	int pos, randomNumber;
	char hex;
	for (pos = 0; pos < size; pos++) {
		randomNumber = getRandomBetween(0, 15);
		if (pos == 8 || pos == 13 || pos == 18 || pos == 23) {
			hex = '-';
		} else if (pos == 14) {
			hex = '4';
		} else if (pos == 19) {
			randomNumber = randomNumber & (0x3 | 0x8);
			hex = convertToHex(randomNumber);
		} else {
			hex = convertToHex(randomNumber);
		}
		guid[pos] = hex;
	}
	guid[size] = 0;
	return guid;
}
