#pragma once
#include <fstream>
#include <vector>
#include "TableElement.h"

class FileIO
{
private:
	std::streampos endOfFile;

public:
	FileIO();
	~FileIO();

public:
	bool fileExists() const;
	void readAll(std::vector<TableElement*>&);

	void addStorable(const TableElement&);
	void writeAfter(const int, std::vector<TableElement*>&);
};

