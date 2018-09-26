#pragma once


#include "ListOnLinkedList.h"

template<typename T>
class CyclicListOnLinckedList : public ListOnLinkedList<T>
{
	//Node<T> *head = nullptr;
	//int length;

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
	Node<T> *node = this->head;
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
	if (this->length == 0)
	{
		this->head = newNode;
		this->head->next = this->head;
	}
	else
	{
		Node<T> *node = getNode(this->length - 1);

		node->next = newNode;
		newNode->next = this->head;
	}
	++this->length;
}

template<typename T>
void CyclicListOnLinckedList<T>::popBack()
{
	if (this->length != 0)
	{
		Node<T> *node = getNode(this->length - 2);
		Node<T> *oldNode = node->next;

		node->next = this->head;
		delete oldNode;
		--this->length;
	}
}

template<typename T>
void CyclicListOnLinckedList<T>::pushFront(T value)
{
	Node<T> *newNode = new Node<T>(value);
	if (this->length == 0)
	{
		this->head = newNode;
		this->head->next = this->head;
	}
	else
	{
		Node<T> *node = getNode(this->length - 1);
		node->next = newNode;
		newNode->next = this->head;
		this->head = newNode;
	}
	++this->length;
}

template<typename T>
void CyclicListOnLinckedList<T>::popFront()
{
	if (this->length != 0)
	{
		Node<T> *node = getNode(this->length - 1);
		Node<T> *oldNode = this->head;
		node->next = this->head->next;
		this->head = this->head->next;
		delete oldNode;
		--this->length;
	}
}

template<typename T>
void CyclicListOnLinckedList<T>::reverse()
{
	Node<T> *nodeLast = this->head;
	Node<T> *nodeNow = this->head;
	Node<T> *nodeNext = this->head->next;
	nodeLast->next = nullptr;
	Node<T> *tail = nodeLast;
	nodeNow = nodeNext;
	nodeNext = nodeNext->next;
	for (int i = 1; i < this->length - 1; ++i)
	{
		nodeNow->next = nodeLast;
		nodeLast = nodeNow;
		nodeNow = nodeNext;
		nodeNext = nodeNext->next;
	}
	nodeNow->next = nodeLast;
	this->head = nodeNow;
	tail->next = this->head;
}
