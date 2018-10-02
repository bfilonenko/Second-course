#pragma once


#include <vector>
#include <math.h>
#include <iostream>

using namespace std;


class Figure
{
public:
	Figure() {}
	virtual ~Figure() {}

	virtual void coutFigure() = 0;
	virtual vector<float> getParameters() = 0;
	virtual vector<pair<float, float> > getTheIntersection(Figure &figure) = 0;
	virtual Figure *symmetricalMapping(Figure &figure) = 0;
	virtual Figure *getInversion(Figure &figure) = 0;
};