#pragma once


#include "Algorithm.h"


class QuickSort : public Algorithm
{
	using Algorithm::story;

public:
	QuickSort();
	QuickSort(vector<int> &values);
	~QuickSort();

	void goToNext();
};