#pragma once


#include <iostream>
#include <vector>
#include <string>

#include "Line.h"

using namespace std;


template<typename T>
ostream &operator << (ostream &os, const vector<T> &vector)
{
	os << "Vector{ ";
	for (int i = 0; i < vector.size() - 1; ++i)
	{
		os << vector[i] << ", ";
	}
	if (vector.size() > 1)
	{
		os << vector[vector.size() - 1] << ' ';
	}
	os << '}';
	return os;
}

template<typename T>
istream &operator >> (istream &is, vector<T> &vec)
{
	vec.clear();
	int length;
	is >> length;
	vec = vector<T>(length, T());
	for (int i = 0; i < length; ++i)
	{
		is >> vec[i];
	}
	return is;
}


template<typename T>
T getRandomElement(T value);



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

template<>
int getRandomElement(int value)
{
	return rand() % 100;
}
template<>
double getRandomElement(double value)
{
	return double((rand() % 100));
}
template<>
Line getRandomElement(Line value)
{
	return Line((float)(rand() % 100 - 50), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50));
}
template<>
Circle getRandomElement(Circle value)
{
	return Circle((float)(rand() % 100 + 1), (float)(rand() % 100 - 50), (float)(rand() % 100 - 50));
}
template<>
string getRandomElement(string value)
{
	string temp;
	int countOfSymbol = rand() % 100 + 1;
	for (int j = 0; j < countOfSymbol; ++j)
	{
		temp.push_back((char)(rand() % 256));
	}
	return temp;
}
template<typename T>
vector<T> getRandomElement(vector<T> value)
{
	vector<T> temp;
	int countOfElement = rand() % 100 + 1;
	for (int j = 0; j < countOfElement; ++j)
	{
		T *newTemp = new T;
		temp.push_back(getRandomElement(*newTemp));
	}
	return temp;
}


//template<typename T>
//T getRandomElement(T value)
//{
//	T temp;
//	int countOfElement = rand() % 100 + 1;
//	for (int j = 0; j < countOfElement; ++j)
//	{
//		typename T::value_type *newTemp = new typename T::value_type;
//		temp.push_back(getRandomElement(*newTemp));
//	}
//	return temp;
//}
