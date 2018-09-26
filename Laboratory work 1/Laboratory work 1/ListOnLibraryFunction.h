#pragma once


#include <list>
#include "BaseList.h"


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
