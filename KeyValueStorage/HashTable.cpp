#include <iostream>
#include <algorithm>
#include "HashTable.h"

HashTable::HashTable(const int size): hash(size)
{
	if (size < 1)
		throw std::invalid_argument("");
	this->tableSize = size;
	this->pTable = new List<TableElement>[tableSize];
}

HashTable::~HashTable()
{
	delete[] pTable;
}

///
/// Returns the count of chains in the hash table
///
int HashTable::getSize() const
{
	return tableSize;
}

///
/// Adds the element in the list coresponding to
/// the hash of the key of the element.
///
void HashTable::addEntry(const TableElement& el)
{
	size_t idx = hash.compute(el.pKey, KEYSIZE);

	pTable[idx].pushBack(el);
}

///
/// Returns the element with the given key.
/// If there isn't such element, returns nullptr.
///
TableElement* HashTable::search(char* pKey)
{
	size_t idx = hash.compute(pKey, KEYSIZE);
	TableElement el(pKey);

	List<TableElement>& chain = pTable[idx];
	List<TableElement>::iterator it;
	for (it = chain.beg(); !it.atEnd(); ++it)
	{
		if (el == *it)
			return &*it;
	}
	return nullptr;
}


///
/// Returns an integer which is the order of input of the element.
///	If the element wasn't erased or there isn't such element, returns -1.
///
int HashTable::erase(char* pKey)
{
	int index = -1;

	size_t idx = hash.compute(pKey, KEYSIZE);
	TableElement el(pKey);

	List<TableElement>& chain = pTable[idx];
	List<TableElement>::iterator it;
	for (it = chain.beg(); !it.atEnd(); ++it)
	{
		if (el == *it)
		{
			memcpy(&index, (*it).pKey, KEYSIZE);
			chain.remove(it);
			break;
		}
	}
	return index;
}

///
/// Prints the maximum and minimum size of chain in the hash table,
/// as long as the average chain size.
///
void HashTable::printInfo() const
{
	int max, min,
		sizeAll = 0;

	max = min = pTable[0].getSize();;
	for (int i = 1; i < tableSize; ++i)
	{
		int size = pTable[i].getSize();
		min = min < size ? min : size;
		max = max > size ? max : size;
		sizeAll += size;
	}

	std::cout << "Max el: " << max << std::endl;
	std::cout << "Min el: " << min << std::endl;
	std::cout << "On average: " << (double) sizeAll / (double) tableSize << std::endl;

//	printTable();
}

void HashTable::printTable() const
{
	std::cout << "Table: " << std::endl;
	for (int i = 0; i < tableSize; ++i)
	{
		if (pTable[i].getSize() == 0)
		{
			std::cout << i << ": " << std::endl;
			List<TableElement>::iterator it;
			for (it = pTable[i].beg(); !it.atEnd(); ++it)
			{
				std::cout << (*it).size << "; ";
			}
		}
	}
}
