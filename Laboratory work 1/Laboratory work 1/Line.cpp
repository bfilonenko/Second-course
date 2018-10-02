#include "Line.h"



Line::Line()
{
	a = 0.f;
	b = 0.f;
	c = 0.f;
}

Line::Line(float x1, float y1, float x2, float y2)
{
	a = y2 - y1;
	b = x1 - x2;
	c = x1 * (y1 - y2) + y1 * (x2 - x1);
}


void Line::coutFigure()
{
	cout << "Line: (" << a << ") * x + (" << b << ") * y + (" << c << ") = 0\n";
}

vector<float> Line::getParameters()
{
	return vector<float>({ a, b, c });
}

Line *Line::getPerpendicular(float x, float y)
{
	Line *line = new Line(-b, a, b * x - a * y);
	return line;
}

vector<pair<float, float> > Line::getTheIntersection(Figure &figure)
{
	vector<pair<float, float> > result;

	if (typeid(Line) == typeid(figure))
	{
		vector<float> parameters;
		parameters = figure.getParameters();
		float a1 = parameters[0], b1 = parameters[1], c1 = parameters[2];
		parameters.clear();

		if (a * b1 == a1 * b && a * c1 == a1 * c)
		{
			if (a == 0 && b != 0)
			{
				result.push_back({ 0.f, -c / b });
				result.push_back({ 1.f, -c / b });
			}
			else if (a != 0 && b == 0)
			{
				result.push_back({ -c / a, 0.f });
				result.push_back({ -c / a, 1.f });
			}
			else if (a != 0 && b != 0 && c != 0)
			{
				result.push_back({ 0.f, -c / b });
				result.push_back({ -c / a, 0.f });
			}
			else if (a != 0 && b != 0)
			{
				result.push_back({ 0.f, 0.f });
				result.push_back({ 1.f, -a / b });
			}
		}
		else if (a * b1 != a1 * b)
		{
			if ((a != 0 && a1 != 0 && b1 != 0) || (a != 0 && b != 0 && b1 != 0) || (a1 != 0 && b != 0 && b1 != 0))
			{
				float tempX = ((b * c1) / b1 - c) / (a - (b * a1) / b1);
				result.push_back({ tempX, -(a1 * tempX) / b1 - c1 / b1 });
			}
			else if (a != 0 && a1 != 0 && b != 0)
			{
				float tempX = ((b1 * c) / b - c1) / (a1 - (b1 * a) / b);
				result.push_back({ tempX, -(a * tempX) / b - c / b });
			}
		}
		else if ((a == 0 && a1 != 0 && b != 0 && b1 == 0) || (a != 0 && a1 == 0 && b == 0 && b1 != 0))
		{
			result.push_back({ (a == 0 ? -c1 / a1 : -c / a), (a == 0 ? -c / b : -c1 / a1) });
		}
	}
	else
	{
		vector<float> parameters;
		parameters = figure.getParameters();
		float r1 = parameters[0], x1 = parameters[1], y1 = parameters[2];
		parameters.clear();

		if (b != 0)
		{
			float a1 = -a / b, b1 = -c / b;

			float d1 = (a1 * (b1 - y1) - x1) * (a1 * (b1 - y1) - x1) - (x1 * x1 + (b1 - y1) * (b1 - y1) - r1 * r1) * (1 + a1 * a1);
			if (d1 == 0)
			{
				result.push_back({ (x1 - a1 * (b1 - y1)) / (1 + a1 * a1), a1 * ((x1 - a1 * (b1 - y1)) / (1 + a1 * a1)) + b1 });
			}
			else if (d1 > 0)
			{
				float tempX = ((x1 - a1 * (b1 - y1)) + sqrt(d1)) / (1 + a1 * a1);
				result.push_back({ tempX, a1 * tempX + b1 });
				tempX -= (2 * sqrt(d1)) / (1 + a1 * a1);
				result.push_back({ tempX, a1 * tempX + b1 });
			}
		}
		else if (a != 0)
		{
			float temp = r1 * r1 - (c / a + x1) * (c / a + x1);
			if (temp == 0)
			{
				result.push_back({ -c / a, y1 });
			}
			else if (temp > 0)
			{
				result.push_back({ -c / a, sqrt(temp) + y1 });
				result.push_back({ -c / a, -sqrt(temp) + y1 });
			}
		}

	}


	return result;
}

Figure *Line::symmetricalMapping(Figure &figure)
{
	Figure *newFigure;

	if (typeid(Line) == typeid(figure))
	{
		vector<float> parameters;
		parameters = figure.getParameters();
		float a1 = parameters[0], b1 = parameters[1], c1 = parameters[2];
		parameters.clear();

		vector<pair<float, float> > intersectionPoint = getTheIntersection(figure);
		
		if (intersectionPoint.size() == 2)
		{
			newFigure = new Line(*this);
		}
		else if (intersectionPoint.size() == 0)
		{
			newFigure = new Line(a1, b1, 2 * c - c1 * (a == 0 ? b / b1 : a / a1));
		}
		else
		{
			float x2 = intersectionPoint[0].first + (b1 == 0 ? 0 : 1), y2 = (b1 == 0 ? intersectionPoint[0].second + 1 : (-a1 / b1) * (intersectionPoint[0].first + 1) - c1 / b1);
			Figure *perpendicular = getPerpendicular(x2, y2);

			vector<pair<float, float> > intersectionPointPerpendicularAndLine = getTheIntersection(*perpendicular);

			newFigure = new Line(intersectionPoint[0].first, intersectionPoint[0].second, 2 * intersectionPointPerpendicularAndLine[0].first - x2, 2 * intersectionPointPerpendicularAndLine[0].second - y2);
		}
	}
	else
	{
		vector<float> parameters;
		parameters = figure.getParameters();
		float r1 = parameters[0], x1 = parameters[1], y1 = parameters[2];
		parameters.clear();

		Figure *perpendicular = getPerpendicular(x1, y1);
		vector<pair<float, float> > intersectionPoint = getTheIntersection(*perpendicular);

		newFigure = new Circle(r1, 2 * intersectionPoint[0].first - x1, 2 * intersectionPoint[0].second - y1);
	}
	
	return newFigure;
}

Figure *Line::getInversion(Figure &figure)
{
	return nullptr;
}