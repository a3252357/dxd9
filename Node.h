#pragma once

template <class T>
class Node
{
public:
	Node<T> *next;
	Node<T> *prev;
	T data;
};


