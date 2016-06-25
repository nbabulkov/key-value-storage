#pragma once
#include "ListNode.h"

template<class T>
class ListIterator
{
private:
	Node<T>** pBegin;
	Node<T>* pCurrent;

public:
	ListIterator();
	ListIterator(Node<T>*&);
	
public:
	T& operator*();
	ListIterator& operator++();
	ListIterator operator++(int);

	bool operator== (const ListIterator<T>&) const;
	bool operator!= (const ListIterator<T>&) const;
	bool atEnd() const;

public:
	void erase();
};


template<class T>
ListIterator<T>::ListIterator():
	pBegin(nullptr), pCurrent(nullptr)
{
}

template<class T>
ListIterator<T>::ListIterator(Node<T>*& start) :
	pBegin(&start), pCurrent(start)
{
}

template<class T>
T& ListIterator<T>::operator*()
{
	if (pCurrent)
	{
		return pCurrent->data;
	}
	throw std::invalid_argument("Iterator isn't assinged!");
}

template<class T>
inline bool ListIterator<T>::atEnd() const
{
	return !pCurrent;
}

template<class T>
inline bool ListIterator<T>::operator==(const ListIterator<T>& other) const
{
	return *pBegin == *other.pBegin && pCurrent == other.pCurrent;
}

template<class T>
inline bool ListIterator<T>::operator!=(const ListIterator<T>& other) const
{
	return !(*this == other);
}

template<class T>
ListIterator<T>& ListIterator<T>::operator++()
{
	if (pCurrent)
	{
		pCurrent = pCurrent->next;
		return *this;
	}
	throw std::out_of_range("List's end reached!");
}

template<class T>
ListIterator<T> ListIterator<T>::operator++(int)
{
	if (pCurrent)
	{
		ListIterator old(*this);
		operator++();
		return old;
	}
}

template<class T>
inline void ListIterator<T>::erase()
{
	if (*pBegin != nullptr)
	{
		if ((*pBegin)->next != nullptr)
		{
			if (!pCurrent)
			{
				return;
			}
			else if (pCurrent == *pBegin)
			{
				pCurrent = pCurrent->next;
				delete *pBegin;
				*pBegin = pCurrent;
			}
			else
			{
				Node<T>* pPrev = *pBegin;
				while (pPrev->next != pCurrent)
				{
					pPrev = pPrev->next;
				}
				pPrev->next = pCurrent->next;
				delete[] pCurrent;
				pCurrent = pPrev->next;
			}
		}
		else
		{
			delete *pBegin;
			*pBegin = pCurrent= nullptr;
		}
	}
	else
	{
		throw std::invalid_argument("Iterator isn't assinged!");
	}
}