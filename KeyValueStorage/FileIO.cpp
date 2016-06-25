#include "FileIO.h"
#include "HelpFunctions.h"

const char* IOPATH = "data.bin";

FileIO::FileIO()
{
	endOfFile = sizeof(int);
}

FileIO::~FileIO()
{
}

///
/// If file exists returns true,
/// if not - creates the file and return false. 
///
bool FileIO::fileExists() const
{
	std::ifstream in;
	in.open(IOPATH, std::ios::in | std::ios::binary);

	bool exists = in.good();
	in.close();

	if (!exists)
	{
		std::ofstream out(IOPATH, std::ios::out | std::ios::binary);
		out.close();
	}

	return exists;
}

///
/// Loads all the elements in the file and 
/// sets the end of file on the proper place.
///
void FileIO::readAll(std::vector<TableElement*>& elements)
{
	std::ifstream in;
	in.open(IOPATH, std::ios::in | std::ios::binary);
	if (in.is_open())
	{
		int end, dataSize;
		char *pData, *pKey;

		in.read(reinterpret_cast<char*>(&end), sizeof(end));

		int sizesSum = sizeof(end);
		while (sizesSum < end)
		{
			in.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));

			pData = new char[dataSize];
			in.read(pData, dataSize);

			pKey = new char[KEYSIZE];
			in.read(pKey, KEYSIZE);

			elements.push_back(new TableElement(pKey, pData, dataSize));
			sizesSum += sizeOfEl(dataSize);
		}
		endOfFile = in.tellg();
	}
	in.close();
}

///
/// Appends the given element to the file and
/// sets the end of file on the proper place.
///
void FileIO::addStorable(const TableElement& el)
{
	std::ofstream out;
	out.open(IOPATH, std::ios::in | std::ios::out | std::ios::binary);
	if (out.good())
	{
		int end = endOfFile;
		end += sizeOfEl(el.size);
		out.write(reinterpret_cast<const char*>(&end), sizeof(end));

		out.seekp(endOfFile, std::ios::beg);
		out.write(reinterpret_cast<const char*>(&el.size), sizeof(el.size));
		out.write(el.pData, el.size);
		out.write(el.pKey, KEYSIZE);
		endOfFile += sizeOfEl(el.size);
	}
	out.close();
}

///
/// Writes over the element with the given index
/// and sets the end of file.
///	Must be called if an elements is ereased.
///
void FileIO::writeAfter(const int idx, std::vector<TableElement*>& elements)
{
	std::streampos posInFile = sizeof(int);
	int size = elements.size();
	for (int i = 0; i < idx; ++i)
	{
		posInFile += sizeOfEl(elements[i]->size);
	}

	std::ofstream out;
	out.open(IOPATH, std::ios::out | std::ios::in | std::ios::binary);
	if (out.good())
	{
		out.seekp(posInFile);
		for (int i = idx; i < size; ++i)
		{
			out.write(reinterpret_cast<const char*>(&elements[i]->size), sizeof(elements[i]->size));
			out.write(elements[i]->pData, elements[i]->size);
			out.write(elements[i]->pKey, KEYSIZE);
		}

		endOfFile = out.tellp();
		out.seekp(0);
		int end = endOfFile;
		out.write(reinterpret_cast<const char*>(&end), sizeof(end));

	}
	out.close();
}
