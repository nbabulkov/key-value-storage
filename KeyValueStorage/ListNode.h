#pragma once

template<class T>
struct Node
{
	T data;
	Node<T>* next;

	Node(const T&, Node<T>* = nullptr);
};

template<class T>
Node<T>::Node(const T& _data, Node<T>* _next = nullptr):
	data(_data), next(_next)
{
}