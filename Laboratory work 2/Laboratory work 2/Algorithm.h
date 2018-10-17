#pragma once


#include <algorithm> 
#include "BaseElement.h"


struct AlgorithmParameter
{
	vector<int> oldPositionOfMainIndex;
	vector<int> mainIndexes;
	vector<int> indexForHighlight;
	vector<int> indexes;

	int operations;
	int length;
	vector<pair<int, int> > arrayOfValues;

	AlgorithmParameter *next;

	AlgorithmParameter();
	~AlgorithmParameter();
};


class Algorithm
{
protected:
	vector<AlgorithmParameter> story;

public:
	Algorithm() {}
	virtual ~Algorithm() {}

	virtual void goToNext() = 0;
	void goToBack();

	void save(string &name);
	void download(string &name);

	AlgorithmParameter *getStruct();
};