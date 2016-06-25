// Author: Nikolay Babulkov FN-45088
// Informatics, FMI
// SDP Course Project

#include <iostream>
#include "HashTableTest.h"
#include "KeyValueStore.h"
#include "HelpFunctions.h"


void testHashTable()
{
	int chainsCount = 157,
		entries = 2000;

	HashTableTest t(chainsCount, entries);
	std::cout << "Tests completed successfully " << (t.runTests() ? "True" : "False") << std::endl;
}

int main()
{
	testHashTable();
	
/*

	KeyValueStore k;
	int size = 4;

	for (int i = 0; i < size; ++i)
	{
		char* searchKey = new char[KEYSIZE];
		memcpy(searchKey, &i, KEYSIZE);
		
		char* data;
		int dataSize;
		k.load(searchKey, data, dataSize);
	}

	for (int i = 0; i < size; ++i)
	{
		char* delKey = new char[KEYSIZE];
		memcpy(delKey, &i, KEYSIZE);

		k.erase(delKey);
	}

	for (int i = 0; i < size; ++i)
	{
		int dataSize = 4;
		char* data = new char[dataSize];
		for (int j = 0; j < size; ++j)
		{
			data[j] = 'a' + (j + i * 4) % (255 - 'a');
		}

		k.store(data, dataSize);
	}
*/

	return 0;
}