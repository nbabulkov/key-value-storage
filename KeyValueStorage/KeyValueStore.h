#pragma once
#include "HashTable.h"
#include "FileIO.h"

class KeyValueStore
{
private:
	int nextKey;
	std::vector<TableElement*> elementsOrdered;
	HashTable table;
	FileIO io;

public:
	KeyValueStore();
	~KeyValueStore();

public:
	char* store(char*, const int);
	bool load(char*, char*&, int&);
	bool erase(char*);

private:
	char* assignKey() const;
};

