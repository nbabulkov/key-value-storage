#pragma once
#include <iostream>
#include "ListIterator.h"

template<class T>
class List
{
private:
	Node<T>* pHead;
	Node<T>* pTail;
	int size;

public:
	typedef ListIterator<T> iterator;
	ListIterator<T>& beg();

public:
	List();
	~List();
	List(const List&);
	const List& operator= (const List&);

private:
	void copy(const List&);
	void clear();

public:
	int getSize() const;
	T& front();
	T& back();
	void remove(ListIterator<T>&);

public:
	void pushBack(const T&);
	void pushFront(const T&);

	void popFront();
	void popBack();
};


///
/// Big 4:
///
template<class T>
List<T>::List()
{
	pHead = nullptr;
	pTail = nullptr;
	size = 0;
}

template<class T>
List<T>::~List()
{
	clear();
}

template<class T>
List<T>::List(const List& l)
{
	copy(l);
}

template<class T>
const List<T>& List<T>::operator=(const List& l)
{
	if (this != &l)
	{
		clear();
		copy(l);
	}
	return *this;
}

///
/// Help Functions:
///
template<class T>
void List<T>::copy(const List<T>& l)
{
	size = 0;
	if (l.pHead)
	{
		for (ListIterator<T> it(l.pHead); !it.AtEnd(); ++it)
		{
			pushBack(*it);
		}
	}
	else
	{
		pHead = pTail = nullptr;
	}
}

template<class T>
void List<T>::clear()
{
	while (size != 0)
	{
		popBack();
	}
}

///
/// Modifiers:
///
template<class T>
void List<T>::pushBack(const T& el)
{
	if (size != 0)
	{
		pTail->next = new Node<T>(el);
		pTail = pTail->next;
	}
	else
	{
		pHead = pTail = new Node<T>(el);
	}
	++size;
}

template<class T>
void List<T>::pushFront(const T& el)
{
	if (size != 0)
	{
		pHead = new Node<T>(el, pHead);
	}
	else
	{
		pHead = pTail = new Node<T>(el);
	}
	++size;
}

template<class T>
void List<T>::popFront()
{
	if (size != 0)
	{
		if (pHead != pTail)
		{
			Node<T>* temp = head;
			pHead = pHead->next;
			delete temp;
		}
		else
		{
			delete pHead;
			pHead = pTail = nullptr;
		}
		--size;
	}
	else
	{
		throw std::exception("Cannot pop from empty list!");
	}
}

template<class T>
void List<T>::popBack()
{
	if (size != 0)
	{
		if (pHead != pTail)
		{
			Node<T>* temp = pHead;
			while (temp->next != pTail)
				temp = temp->next;
			delete pTail;
			pTail = temp;
		}
		else
		{
			delete pHead;
			pHead = pTail = nullptr;
		}
		--size;
	}
	else
	{
		throw std::exception("Cannot pop from empty list!");
	}
}

///
/// Access:
///
template<class T>
inline int List<T>::getSize() const
{
	return size;
}

template<class T>
inline T& List<T>::front()
{
	if(pHead)
		return pHead->data;
	throw std::exception("List is empty!");
}

template<class T>
inline T& List<T>::back()
{
	if(pTail)
		return pTail->data;
	throw std::exception("List is empty!");
}

template<class T>
inline void List<T>::remove(ListIterator<T>& it)
{
	--size;
	it.erase();
}

template<class T>
inline ListIterator<T>& List<T>::beg()
{
	if (pHead)
		return ListIterator<T>(pHead);
	throw std::exception("List is empty!");
}
