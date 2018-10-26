#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "random.h"
#include "guid.h"

char _convert_to_hex(int value)
{
	if (value > 15)
	{
		// error out
	}
	char hex [4];
	sprintf(hex, "%x", value);
	return hex[0];
}

struct Guid *new_guid()
{
	int size = 36;
	struct Guid *guid = (struct Guid *)calloc(1, sizeof(struct Guid));
	char *value = (char *)malloc(sizeof(char) * size + 1);
	if (guid == NULL || value == NULL)
	{
		return NULL;
	}
	int pos, randomNumber;
	char hex;
	for (pos = 0; pos < size; pos++)
	{
		randomNumber = getRandomBetween(0, 15);
		if (pos == 8 || pos == 13 || pos == 18 || pos == 23)
		{
			hex = '-';
		} 
		else if (pos == 14) 
		{
			hex = '4';
		}
		else if (pos == 19)
		{
			randomNumber = randomNumber & (0x3 | 0x8);
			hex = _convert_to_hex(randomNumber);
		}
		else
		{
			hex = _convert_to_hex(randomNumber);
		}
		value[pos] = hex;
	}
	value[size] = 0;
	guid->value = value;
	return guid;
}
