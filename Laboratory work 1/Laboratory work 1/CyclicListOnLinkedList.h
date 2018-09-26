#pragma once


#include "ListOnLinkedList.h"

template<typename T>
class CyclicListOnLinckedList : public ListOnLinkedList<T>
{
	Node<T> *head = nullptr;
	int length;

	Node<T> *getNode(int position);

public:
	void pushBack(T value);
	void popBack();
	void pushFront(T value);
	void popFront();
	void reverse();
};

template<typename T>
Node<T> *CyclicListOnLinckedList<T>::getNode(int position)
{
	Node<T> *node = head;
	for (int i = 0; i < position; ++i)
	{
		node = node->next;
	}
	return node;
}


template<typename T>
void CyclicListOnLinckedList<T>::pushBack(T value)
{
	Node<T>  *newNode = new Node<T>(value);
	if (length == 0)
	{
		head = newNode;
		head->next = head;
	}
	else
	{
		Node<T> *node = getNode(length - 1);

		node->next = newNode;
		newNode->next = head;
	}
	++length;
}

template<typename T>
void CyclicListOnLinckedList<T>::popBack()
{
	if (length != 0)
	{
		Node<T> *node = getNode(length - 2);
		Node<T> *oldNode = node->next;

		node->next = head;
		delete oldNode;
		--length;
	}
}

template<typename T>
void CyclicListOnLinckedList<T>::pushFront(T value)
{
	Node<T> *newNode = new Node<T>(value);
	if (length == 0)
	{
		head = newNode;
		head->next = head;
	}
	else
	{
		Node<T> *node = getNode(length - 1);
		node->next = newNode;
		newNode->next = head;
		head = newNode;
	}
	++length;
}

template<typename T>
void CyclicListOnLinckedList<T>::popFront()
{
	if (length != 0)
	{
		Node<T> *node = getNode(length - 1);
		Node<T> *oldNode = head;
		node->next = head->next;
		head = head->next;
		delete oldNode;
		--length;
	}
}

template<typename T>
void CyclicListOnLinckedList<T>::reverse()
{
	Node<T> *nodeLast = head;
	Node<T> *nodeNow = head;
	Node<T> *nodeNext = head->next;
	nodeLast->next = nullptr;
	Node<T> *tail = nodeLast;
	nodeNow = nodeNext;
	nodeNext = nodeNext->next;
	for (int i = 1; i < length - 1; ++i)
	{
		nodeNow->next = nodeLast;
		nodeLast = nodeNow;
		nodeNow = nodeNext;
		nodeNext = nodeNext->next;
	}
	nodeNow->next = nodeLast;
	head = nodeNow;
	tail->next = head;
}
