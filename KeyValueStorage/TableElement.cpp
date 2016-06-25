#include "TableElement.h"

TableElement::TableElement():
	size(0), pData(nullptr), pKey(nullptr)
{
}

TableElement::TableElement(char* key, char* data, const int size)
{
	this->pKey = key;
	this->pData = data;
	this->size = size;
}

bool TableElement::operator==(const TableElement& other)
{
	for (int i = 0; i < KEYSIZE; ++i)
	{
		if (pKey[i] != other.pKey[i])
		{
			return false;
		}
	}
	return true;
}

bool TableElement::operator!=(const TableElement& other)
{
	return !(*this == other);
}

