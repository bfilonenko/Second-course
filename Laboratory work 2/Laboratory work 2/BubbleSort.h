#pragma once


#include "Algorithm.h"


class BubbleSort : public Algorithm
{
	using Algorithm::story;

public:
	BubbleSort();
	BubbleSort(vector<int> &values);
	~BubbleSort();

	void goToNext();
};