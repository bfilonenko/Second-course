#pragma once


#include <iostream>
#include <vector>
#include <string>

#include "Line.h"

using namespace std;


template<typename T>
class List
{
public:
	List() {}
	virtual ~List() {}

	virtual void showAll() = 0;
	virtual void pushBack(T value) = 0;
	virtual void popBack() = 0;
	virtual void pushFront(T value) = 0;
	virtual void popFront() = 0;
	virtual void addElement(T value, int position) = 0;
	virtual void deleteElement(int position) = 0;
	virtual T getElement(int position) = 0;
	virtual int getIndex(T value) = 0;
	virtual void reverse() = 0;
	virtual void clear() = 0;
	virtual void addRandomElements() = 0;
	virtual int getSize() = 0;
	virtual T getElememtMetchingCriterion(bool(*criterion)(T)) = 0;
};

