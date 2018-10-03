#pragma once


#include "BaseList.h"


template<typename T>
struct Node
{
	T value;
	Node *next = nullptr;
	Node(T value) : value(value) {}
};


template<typename T>
class ListOnLinkedList : public List<T>
{
protected:
	Node<T> *head = nullptr;
	Node<T> *tail = nullptr;
	int length;

	Node<T> *getNode(int position);

public:
	ListOnLinkedList();

	void showAll();
	void pushBack(T value);
	void popBack();
	void pushFront(T value);
	void popFront();
	void addElement(T value, int position);
	void deleteElement(int position);
	T getElement(int position);
	int getIndex(T value);
	void reverse();
	void clear();
	void addRandomElements();
	int getSize();
	T getElememtMetchingCriterion(bool(*criterion)(T));
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

template<>
void ListOnLinkedList<int>::showAll()
{
	Node<int> *node = head;
	for (int i = 0; i < length; ++i)
	{
		cout << node->value << ' ';
		node = node->next;
	}
	cout << '\n';
}
template<>
void ListOnLinkedList<double>::showAll()
{
	Node<double> *node = head;
	for (int i = 0; i < length; ++i)
	{
		cout << node->value << ' ';
		node = node->next;
	}
	cout << '\n';
}
template<>
void ListOnLinkedList<Line>::showAll()
{
	Node<Line> *node = head;
	for (int i = 0; i < length; ++i)
	{
		cout << node->value << ' ';
		node = node->next;
	}
	cout << '\n';
}
template<>
void ListOnLinkedList<Circle>::showAll()
{
	Node<Circle> *node = head;
	for (int i = 0; i < length; ++i)
	{
		cout << node->value << ' ';
		node = node->next;
	}
	cout << '\n';
}
template<>
void ListOnLinkedList<string>::showAll()
{
	Node<string> *node = head;
	for (int i = 0; i < length; ++i)
	{
		cout << node->value << ' ';
		node = node->next;
	}
	cout << '\n';
}
template<typename T>
void ListOnLinkedList<T>::showAll()
{
	Node<T> *node = head;
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < node->value.size(); ++j)
		{
			cout << node->value[i] << ' ';
		}
		cout << '\n';
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
		Node<T> *node = getNode(length - 2);
		tail = node;
		node = node->next;
		tail->next = nullptr;
		delete node;
		--length;
	}
}

template<typename T>
void ListOnLinkedList<T>::pushFront(T value)
{
	Node<T> *newNode = new Node<T>(value);
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
void ListOnLinkedList<T>::addElement(T value, int position)
{
	if (position < 0 || position > length)
	{
		return;
	}
	else if (position == 0)
	{
		pushFront(value);
	}
	else if (position == length)
	{
		pushBack(value);
	}
	else
	{
		Node<T> *node = getNode(position - 1);
		Node<T> *newNode = new Node<T>(value);
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
		return T();
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

template<>
void ListOnLinkedList<int>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		int temp  = (rand() % 100);
				
		pushBack(temp);
	}
}
template<>
void ListOnLinkedList<double>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		double temp = double((rand() % 100));

		pushBack(temp);
	}
}
template<>
void ListOnLinkedList<Line>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		Line temp((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50));

		pushBack(temp);
	}
}
template<>
void ListOnLinkedList<Circle>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		Circle temp((float)(rand() % 100 + 1), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50));

		pushBack(temp);
	}
}
template<>
void ListOnLinkedList<string>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		string temp;
		int countOfSymbol = rand() % 100 + 1;
		for (int j = 0; j < countOfSymbol; ++j)
		{
			temp.push_back((char)(rand() % 256));
		}
		pushBack(temp);
	}
}
template<typename T>
void ListOnLinkedList<T>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		T temp;
		int countOfElement = rand() % 100 + 1;
		for (int j = 0; j < countOfElement; ++j)
		{
			temp.push_back((rand() % 100 - 50));
		}
		pushBack(temp);
	}
}

template<typename T>
int ListOnLinkedList<T>::getSize()
{
	return length;
}

template<typename T>
T ListOnLinkedList<T>::getElememtMetchingCriterion(bool(*criterion)(T))
{
	if (length > 0)
	{
		Node<T> *node = head;
		while (node->next != nullptr)
		{
			if (criterion(node->value))
			{
				return node->value;
			}
			node = node->next;
		}
		if (criterion(node->value))
		{
			return node->value;
		}
	}
	return T();
}
