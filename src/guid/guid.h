#ifndef GUID_H_ 
#define GUID_H_ 

struct Guid
{
	char *value;
};

int newGuid(struct Guid *guid);
char convertToHex(int value);

#endif
