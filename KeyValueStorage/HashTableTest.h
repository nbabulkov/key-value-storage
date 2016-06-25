#pragma once
#include "HashTable.h"

class HashTableTest
{
private:
	int entries;
	HashTable h;

public:
	HashTableTest(const int, const int);
	~HashTableTest();

public:
	bool runTests();

private:
	void fill();
	bool search();
	bool erase();
};

