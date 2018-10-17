#pragma once


#include "Algorithm.h"


class QuickSort : public Algorithm
{
	using Algorithm::story;

	vector<pair<int, int> > stack;

	bool finish;
	bool needSwap;

public:
	QuickSort();
	QuickSort(vector<int> &values);
	~QuickSort();

	void goToNext();
};