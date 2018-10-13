#pragma once


#include "BaseElement.h"


struct AlgorithmParameter
{
	vector<int> mainIndexes;
	vector<int> indexes;

	int length;
	vector<pair<int, int> > arrayOfValues;

	AlgorithmParameter();
};


class Algorithm
{
protected:
	vector<AlgorithmParameter> story;

public:
	Algorithm() {}
	virtual ~Algorithm() {}

	virtual void goToNext() = 0;
	virtual void goToBack() = 0;

	void save(string &name);
	void download(string &name);

	AlgorithmParameter *getStruct();
};