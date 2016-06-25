#include "HashTableTest.h"
#include "HelpFunctions.h"

const int DATASIZE = 100;

HashTableTest::HashTableTest(const int size, const int entries): h(size)
{
	this->entries = entries;
}

HashTableTest::~HashTableTest()
{
}

bool HashTableTest::runTests()
{
	fill();
	h.printInfo();

	if (!search())
		return false;

	return erase();
}

void HashTableTest::fill()
{
	for (int i = 0; i < entries; ++i)
	{
		int size = DATASIZE + i;
		char* pTestInput = new char[size];
		for (int j = 0 ; j < size; ++j)
			pTestInput[j] = (j % 255);
		char* pKey = intToKey(i);
		TableElement el(pKey, pTestInput, size);

		h.addEntry(el);
	}
}

bool HashTableTest::search()
{
	for (int i = 0; i < entries; ++i)
	{
		int size = DATASIZE + i;
		char* pTestInput = new char[size];
		for (int j = 0; j < size; ++j)
			pTestInput[j] = (j % 255);
		char* pKey = intToKey(i);

		TableElement el1(pKey, pTestInput, size);
		TableElement* el2 = h.search(pKey);
		if (el2 == nullptr &&  el1 != *el2)
			return false;
	}
	return true;
}

bool HashTableTest::erase()
{
	for (int i = 0; i < entries; ++i)
	{
		int size = DATASIZE + i;
		char* pTestInput = new char[size];
		for (int j = 0; j < size; ++j)
			pTestInput[j] = (j % 255);
		char* pKey = intToKey(i);

		TableElement el(pKey, pTestInput, size);

		if (h.erase(pKey) < 0)
			return false;
	}
	return true;
}
