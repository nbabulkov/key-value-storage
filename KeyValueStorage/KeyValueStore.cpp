#include "KeyValueStore.h"
#include "HelpFunctions.h"

const int HASHMOD = 127;

KeyValueStore::KeyValueStore()
	:table(HASHMOD)
{
	nextKey = 0;
	if (io.fileExists())
	{
		io.readAll(elementsOrdered);
		int size = elementsOrdered.size();
		for (int i = 0; i < size; ++i)
		{
			int key = keyToInt(elementsOrdered[i]->pKey);
			if (nextKey <= key)
				nextKey = key + 1;

			table.addEntry(*elementsOrdered[i]);
		}
	}
}

KeyValueStore::~KeyValueStore()
{
}

///
/// Stores the block in the hash table and the file storage.
/// Returns a key to the block.
///
char* KeyValueStore::store(char* pBlock, const int size)
{
	char* pKey = assignKey();
	TableElement* pElement = new TableElement(pKey, pBlock, size);

	elementsOrdered.push_back(pElement);
	table.addEntry(*pElement);
	io.addStorable(*pElement);

	return pKey;
}

///
/// Loads a block on a given key from the hash table.
/// If the element is found returns "true", else returns "false".
///
bool KeyValueStore::load(char* pKey, char*& pBlock, int& size)
{
	TableElement* el = table.search(pKey);
	if (!el)
		return false;

	pBlock = el->pData;
	size = el->size;

	return true;
}

///
/// Erases block with given key from 
/// the hash table and from the file storage
///
bool KeyValueStore::erase(char* pKey)
{
	int idx = table.erase(pKey);

	if (idx < 0)
		return false;

	elementsOrdered.erase(elementsOrdered.begin() + idx);
	io.writeAfter(idx, elementsOrdered);

	return true;
}

///
/// Returns unique key for every call.
///
char* KeyValueStore::assignKey() const
{
	char* pKey = new char[KEYSIZE];
	memcpy(pKey, reinterpret_cast<const char*>(&nextKey), KEYSIZE);
	return pKey;
}
