#pragma once


#include <list>
#include "LinkedList.h"


template<typename T>
class List
{
public:
	List() {}
	virtual ~List() {}

	virtual void showAll() {}
	virtual void pushBack(T value) {}
	virtual void popBack() {}
	virtual void pushFront(T value) {}
	virtual void popFront() {}
	virtual void addElement(T value, int position) {}
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


template<typename T>
class ListOnDynamicArray : public List<T>
{
	T *dymamicArray;
	int length;

public:
	ListOnDynamicArray();

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
};


template<typename T>
ListOnDynamicArray<T>::ListOnDynamicArray()
{
	dymamicArray = new T[0];
	length = 0;
}

template<typename T>
void ListOnDynamicArray<T>::showAll()
{
	for (int i = 0; i < length; ++i)
	{
		cout << dymamicArray[i] << ' ';
	}
	cout << '\n';
}

template<typename T>
void ListOnDynamicArray<T>::pushBack(T value)
{
	T *newArray = new T[length + 1];

	for (int i = 0; i < length; ++i)
	{
		newArray[i] = dymamicArray[i];
	}
	newArray[length] = value;
	
	delete[] dymamicArray;

	dymamicArray = newArray;
	++length;
}

template<typename T>
void ListOnDynamicArray<T>::popBack()
{
	if (length != 0)
	{
		T *newArray = new T[length - 1];

		for (int i = 0; i < length - 1; ++i)
		{
			newArray[i] = dymamicArray[i];
		}

		delete[] dymamicArray;

		dymamicArray = newArray;
		--length;
	}
}

template<typename T>
void ListOnDynamicArray<T>::pushFront(T value)
{
	T *newArray = new T[length + 1];

	for (int i = 0; i < length; ++i)
	{
		newArray[i + 1] = dymamicArray[i];
	}
	newArray[0] = value;

	delete[] dymamicArray;

	dymamicArray = newArray;
	++length;
}

template<typename T>
void ListOnDynamicArray<T>::popFront()
{
	if (length != 0)
	{
		T *newArray = new T[length - 1];

		for (int i = 0; i < length - 1; ++i)
		{
			newArray[i] = dymamicArray[i + 1];
		}

		delete[] dymamicArray;

		dymamicArray = newArray;
		--length;
	}
}

template<typename T>
void ListOnDynamicArray<T>::addElement(T value, int position)
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
		T *newArray = new T[length + 1];

		for (int i = 0; i < position; ++i)
		{
			newArray[i] = dymamicArray[i];
		}
		newArray[position] = value;
		for (int i = position; i < length; ++i)
		{
			newArray[i + 1] = dymamicArray[i];
		}
		delete[] dymamicArray;

		dymamicArray = newArray;
		++length;
	}
}

template<typename T>
void ListOnDynamicArray<T>::deleteElement(int position)
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
		T *newArray = new T[length - 1];

		for (int i = 0; i < position; ++i)
		{
			newArray[i] = dymamicArray[i];
		}
		for (int i = position; i < length - 1; ++i)
		{
			newArray[i] = dymamicArray[i + 1];
		}
		delete[] dymamicArray;

		dymamicArray = newArray;
		--length;
	}
}

template<typename T>
T ListOnDynamicArray<T>::getElement(int position)
{
	if (position < 0 || position >= length)
	{
		return -1;
	}
	else
	{
		return dymamicArray[position];
	}
}

template<typename T>
int ListOnDynamicArray<T>::getIndex(T value)
{
	for (int i = 0; i < length; ++i)
	{
		if (dymamicArray[i] == value)
		{
			return i;
		}
	}

	return -1;
}

template<typename T>
void ListOnDynamicArray<T>::reverse()
{
	for (int i = 0; i < length / 2; ++i)
	{
		swap(dymamicArray[i], dymamicArray[length - 1 - i]);
	}
}

template<typename T>
void ListOnDynamicArray<T>::clear()
{
	delete[] dymamicArray;
	dymamicArray = new T[0];
	length = 0;
}

template<typename T>
void ListOnDynamicArray<T>::addRandomElements()
{
	int count = rand() % 100 + 1;

	T *newArray = new T[length + count];

	for (int i = 0; i < length; ++i)
	{
		newArray[i] = dymamicArray[i];
	}

	for (int i = length; i < length + count; ++i)
	{
		newArray[i] = (T)(rand() % 100);
	}

	delete[] dymamicArray;

	dymamicArray = newArray;
	length += count;
}

template<typename T>
int ListOnDynamicArray<T>::getSize()
{
	return length;
}


template<typename T>
class ListOnLibraryFunction : public List<T>
{
	list<T> list;

public:
	ListOnLibraryFunction();

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
};


template<typename T>
ListOnLibraryFunction<T>::ListOnLibraryFunction() {}

template<typename T>
void ListOnLibraryFunction<T>::showAll()
{
	for (auto i = list.begin(); i != list.end(); ++i)
	{
		cout << *i << ' ';
	}
	cout << '\n';
}

template<typename T>
void ListOnLibraryFunction<T>::pushBack(T value)
{
	list.push_back(value);
}

template<typename T>
void ListOnLibraryFunction<T>::popBack()
{
	list.pop_back();
}

template<typename T>
void ListOnLibraryFunction<T>::pushFront(T value)
{
	list.push_front(value);
}

template<typename T>
void ListOnLibraryFunction<T>::popFront()
{
	list.pop_front();
}

template<typename T>
void ListOnLibraryFunction<T>::addElement(T value, int position)
{
	if (position < 0 || position > list.size())
	{
		return;
	}
	else if (position == 0)
	{
		pushFront(value);
	}
	else if (position == list.size())
	{
		pushBack(value);
	}
	else
	{
		auto i = list.begin();
		for (int j = 0; j < position; ++j)
		{
			++i;
		}
		list.insert(i, value);
	}
}

template<typename T>
void ListOnLibraryFunction<T>::deleteElement(int position)
{
	if (position < 0 || position >= list.size())
	{
		return;
	}
	else if (position == 0)
	{
		popFront();
	}
	else if (position == list.size() - 1)
	{
		popBack();
	}
	else
	{
		auto i = list.begin();
		for (int j = 0; j < position; ++j)
		{
			++i;
		}
		list.erase(i);
	}
}

template<typename T>
T ListOnLibraryFunction<T>::getElement(int position)
{
	if (position < 0 || position >= list.size())
	{
		return -1;
	}
	else
	{
		auto i = list.begin();
		for (int j = 0; j < position; ++j)
		{
			++i;
		}
		return *i;
	}
}

template<typename T>
int ListOnLibraryFunction<T>::getIndex(T value)
{
	int index = 0;

	for (auto i = list.begin(); i != list.end(); ++i)
	{
		if (*i == value)
		{
			return index;
		}
		++index;
	}
	return -1;
}

template<typename T>
void ListOnLibraryFunction<T>::reverse()
{
	list.reverse();
}

template<typename T>
void ListOnLibraryFunction<T>::clear()
{
	list.clear();
}

template<typename T>
void ListOnLibraryFunction<T>::addRandomElements()
{
	int count = rand() % 100 + 1;

	for (int i = 0; i < count; ++i)
	{
		T temp = (T)(rand() % 100);
		pushBack(temp);
	}
}

template<typename T>
int ListOnLibraryFunction<T>::getSize()
{
	return list.size();
}
