#pragma once


#include "Algorithm.h"


class InsertionSort : public Algorithm
{
	using Algorithm::story;

	void forConstructor(int number);

public:
	InsertionSort();

	void goToNext();
};