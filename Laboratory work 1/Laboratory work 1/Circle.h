#pragma once


#include "Figure.h"
#include "Line.h"


class Circle : public Figure			//Circle: (x - x0) ^ 2 + (y - y0) ^ 2 = r ^ 2
{
	float r;
	float x0;
	float y0;

	float norm(float x1, float y1, float x2, float y2);
	
public:
	Circle();
	Circle(float r, float x0, float y0) : r(r), x0(x0), y0(y0) {}

	void coutFigure();
	vector<float> getParameters();
	vector<pair<float, float> > getTheIntersection(Figure &figure);
	Figure *symmetricalMapping(Figure &figure);
	Figure *getInversion(Figure &figure);
};