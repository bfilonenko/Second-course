#pragma once


#include "Algorithm.h"


class SelectionSort : public Algorithm
{
	using Algorithm::story;

public:
	SelectionSort();
	SelectionSort(vector<int> &values);
	~SelectionSort();

	void goToNext();
};