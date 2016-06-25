#pragma once
#include "List.h"
#include "TableElement.h"
#include "HashingFunction.h"

class HashTable
{
private:
	int tableSize;
	List<TableElement>* pTable;
	HashingFunction hash;

public:
	HashTable(int size);
	~HashTable();

public:
	void addEntry(const TableElement&);
	TableElement* search(char*);
	int erase(char*);

	int getSize() const;
	void printInfo() const;
	void printTable() const;
};
