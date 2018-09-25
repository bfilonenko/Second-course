#pragma once


#include "LinkedList.h"


template<typename T>
class List
{
public:
	List() {}
	virtual ~List() {}

	virtual void showAll() {}
	virtual void pushBack(T number) {}
	virtual void popBack() {}
	virtual void pushFront(T number) {}
	virtual void popFront() {}
	virtual void addElement(T number, int position) {}
	virtual void deleteElement(int position) {}
	virtual T getElement(int position) { T *temp = new T; return *temp; }
	virtual int getIndex(T value) { int temp = 0; return temp; }
	virtual void reverse() {}
	virtual void clear() {}
	virtual void addRandomElements() {}
	virtual int getSize() { int temp = 0; return temp; }
};


template<typename T>
class ListOnLinkedList: public List<T>
{
	Node<T> *head = nullptr;
	Node<T> *tail = nullptr;
	int length;
	Node<T> *getNode(int position);

public:
	ListOnLinkedList();

	void showAll();
	void pushBack(T value);
	void popBack();
	void pushFront(T number);
	void popFront();
	void addElement(T number, int position);
	void deleteElement(int position);
	T getElement(int position);
	int getIndex(T value);
	void reverse();
	void clear();
	void addRandomElements();
	int getSize();
};


template<typename T>
Node<T> *ListOnLinkedList<T>::getNode(int position)
{
	Node<T> *node = head;
	for (int i = 0; i < position; ++i)
	{
		node = node->next;
	}
	return node;
}

template<typename T>
ListOnLinkedList<T>::ListOnLinkedList()
{
	length = 0;
}

template<typename T>
void ListOnLinkedList<T>::showAll()
{
	Node<T> *node = head;
	for (int i = 0; i < length; ++i)
	{
		cout << node->value << ' ';
		node = node->next;
	}
	cout << '\n';
}

template<typename T>
void ListOnLinkedList<T>::pushBack(T value)
{
	Node<T>  *newNode = new Node<T>(value);
	if (length == 0)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
	++length;
}

template<typename T>
void ListOnLinkedList<T>::popBack()
{
	if (length != 0)
	{
		Node<T> *node = getNode(length - 1);
		tail = node;
		node = node->next;
		tail->next = nullptr;
		delete node;
		--length;
	}
}

template<typename T>
void ListOnLinkedList<T>::pushFront(T number)
{
	Node<T> *newNode = new Node<T>(number);
	if (length == 0)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode->next = head;
		head = newNode;
	}
	++length;
}

template<typename T>
void ListOnLinkedList<T>::popFront()
{
	if (length != 0)
	{
		Node<T> *node = head;
		head = head->next;
		delete node;
		--length;
	}
}

template<typename T>
void ListOnLinkedList<T>::addElement(T number, int position)
{
	if (position < 0 || position > length)
	{
		return;
	}
	else if (position == 0)
	{
		pushFront(number);
	}
	else if (position == length)
	{
		pushBack(number);
	}
	else
	{
		Node<T> *node = getNode(position - 1);
		Node<T> *newNode = new Node<T>(number);
		newNode->next = node->next;
		node->next = newNode;
		++length;
	}
}

template<typename T>
void ListOnLinkedList<T>::deleteElement(int position)
{
	if (position < 0 || position >= length)
	{
		return;
	}
	else if (position == 0)
	{
		popFront();
	}
	else if (position == length - 1)
	{
		popBack();
	}
	else
	{
		Node<T> *node = getNode(position - 1);
		Node<T> *newNode;
		newNode = node->next;
		node->next = node->next->next;
		delete newNode;
		--length;
	}
}

template<typename T>
T ListOnLinkedList<T>::getElement(int position)
{
	if (position < 0 || position >= length)
	{
		return -1;
	}
	else
	{
		Node<T> *node = getNode(position);
		return node->value;
	}
}

template<typename T>
int ListOnLinkedList<T>::getIndex(T value)
{
	int index = 0;
	
	Node<T> *node = head;
	while (node->value != value)
	{
		if (node->next == nullptr)
		{
			return -1;
		}
		node = node->next;
		++index;
	}
	return index;
}

template<typename T>
void ListOnLinkedList<T>::reverse()
{
	Node<T> *nodeLast = head;
	Node<T> *nodeNow = head;
	Node<T> *nodeNext = head->next;
	nodeLast->next = nullptr;
	tail = nodeLast;
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
}

template<typename T>
void ListOnLinkedList<T>::clear()
{
	while (length > 0)
	{
		popFront();
	}
}

template<typename T>
void ListOnLinkedList<T>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		T temp = (T)(rand() % 100);
		pushBack(temp);
	}
}

template<typename T>
int ListOnLinkedList<T>::getSize()
{
	return length;
}