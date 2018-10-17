#pragma once


#include "Algorithm.h"


class InsertionSort : public Algorithm
{
	using Algorithm::story;

public:
	InsertionSort();
	InsertionSort(vector<int> &values);
	~InsertionSort();

	void goToNext();
};