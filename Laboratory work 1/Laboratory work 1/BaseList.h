#pragma once


#include <iostream>
#include <vector>
#include <string>


using namespace std;


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

