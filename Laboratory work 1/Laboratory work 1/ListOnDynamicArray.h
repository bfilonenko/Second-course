#pragma once


#include "BaseList.h"


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

