#include "HelpFunctions.h"
#include <math.h>
#include <chrono>
#include <cstdlib>

char* intToKey(int num)
{
	char* pKey = new char[KEYSIZE];
	memcpy(pKey, &num, KEYSIZE);
	return pKey;
}

int keyToInt(char* pKey)
{
	int num;
	memcpy(&num, pKey, KEYSIZE);
	return num;
}

int sizeOfEl(const int elSize)
{
	return sizeof(elSize) + elSize + KEYSIZE;
}