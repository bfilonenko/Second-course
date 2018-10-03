#pragma once


#include "Figure.h"
#include "Circle.h"


class Line : public Figure				//Line: a * x + b * y + c = 0
{
	float a;
	float b;
	float c;
	
public:
	Line();
	Line(float a, float b, float c) : a(a), b(b), c(c) {}
	Line(float x1, float y1, float x2, float y2);
	Line(int value);

	void coutFigure();
	vector<float> getParameters();
	Line *getPerpendicular(float x, float y);
	vector<pair<float, float> > getTheIntersection(Figure &figure);
	Figure *symmetricalMapping(Figure &figure);
	Figure *getInversion(Figure &figure);

	friend const bool operator != (const Line &left, const Line &right);
	friend const bool operator == (const Line &left, const Line &right);
	
	friend ostream &operator << (ostream& os, const Line &figure);
	friend istream &operator >> (istream& is, Line &figure);
};