#pragma once

const int KEYSIZE = sizeof(int);

struct TableElement
{
	int size;
	char* pData;
	char* pKey;

public:
	TableElement();
	TableElement(char*, char* = nullptr, const int = 0);
	bool operator== (const TableElement&);
	bool operator!= (const TableElement&);
};