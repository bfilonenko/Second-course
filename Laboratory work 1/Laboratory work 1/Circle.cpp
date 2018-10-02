#include "Circle.h"


float Circle::norm(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


Circle::Circle()
{
	r = 0.f;
	x0 = 0.f;
	y0 = 0.f;
}


void Circle::coutFigure()
{
	cout << "Circle: (x - (" << x0 << ")) ^ 2 + (y - (" << y0 << ")) ^ 2 = (" << r << ") ^ 2\n";
}

vector<float> Circle::getParameters()
{
	return vector<float>({ r, x0, y0 });
}

vector<pair<float, float> > Circle::getTheIntersection(Figure &figure)
{
	vector<pair<float, float> > result;

	if (typeid(Line) == typeid(figure))
	{
		result = figure.getTheIntersection(*this);
	}
	else
	{
		vector<float> parameters;
		parameters = figure.getParameters();
		float r1 = parameters[0], x1 = parameters[1], y1 = parameters[2];
		parameters.clear();

		Figure *tempLine = new Line(2 * (x1 - x0), 2 * (y1 - y0), -y1 * y1 + y0 * y0 - x1 * x1 + x0 * x0 - r * r + r1 * r1);
		result = tempLine->getTheIntersection(*this);
	}

	return result;
}

Figure *Circle::symmetricalMapping(Figure &figure)
{
	return nullptr;
}

Figure *Circle::getInversion(Figure &figure)
{
	Figure *newFigure;

	if (typeid(Line) == typeid(figure))
	{
		vector<float> parameters;
		parameters = figure.getParameters();
		float a1 = parameters[0], b1 = parameters[1], c1 = parameters[2];
		parameters.clear();

		if (a1 * x0 + b1 * y0 + c1 == 0)
		{
			newFigure = new Line(a1, b1, c1);
		}
		else
		{
			Line *line = new Line(a1, b1, c1);
			Figure *perpendicular = line->getPerpendicular(x0, y0);

			vector<pair<float, float> > intersectionPoint = line->getTheIntersection(*perpendicular);
			float r2 = (r * r) / norm(x0, y0, intersectionPoint[0].first, intersectionPoint[0].second);
			Figure *tempCircle = new Circle(r2, x0, y0);

			vector<pair<float, float> > intersectionPointWithCircle = perpendicular->getTheIntersection(*tempCircle);

			if (norm(intersectionPoint[0].first, intersectionPoint[0].second, intersectionPointWithCircle[0].first, intersectionPointWithCircle[0].second) <
				norm(intersectionPoint[0].first, intersectionPoint[0].second, intersectionPointWithCircle[1].first, intersectionPointWithCircle[1].second))
			{
				newFigure = new Circle(r2 / 2, (x0 + intersectionPointWithCircle[0].first) / 2, (y0 + intersectionPointWithCircle[0].second) / 2);
			}
			else
			{
				newFigure = new Circle(r2 / 2, (x0 + intersectionPointWithCircle[1].first) / 2, (y0 + intersectionPointWithCircle[1].second) / 2);
			}
		}

	}
	else
	{
		vector<float> parameters;
		parameters = figure.getParameters();
		float r1 = parameters[0], x1 = parameters[1], y1 = parameters[2];
		parameters.clear();

		if ((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1) - r1 * r1 < 0.001f)
		{
			Line *perpendicular = new Line(x0, y0, x1, y1);

			float r2 = (r * r) / norm(x0, y0, 2 * x1 - x0, 2 * y1 - y0);
			Figure *tempCircle = new Circle(r2, x0, y0);

			vector<pair<float, float> > intersectionPointWithCircle = perpendicular->getTheIntersection(*tempCircle);

			if (norm(2 * x1 - x0, 2 * y1 - y0, intersectionPointWithCircle[0].first, intersectionPointWithCircle[0].second) <
				norm(2 * x1 - x0, 2 * y1 - y0, intersectionPointWithCircle[1].first, intersectionPointWithCircle[1].second))
			{
				newFigure = perpendicular->getPerpendicular(intersectionPointWithCircle[0].first, intersectionPointWithCircle[0].second);
			}
			else
			{
				newFigure = perpendicular->getPerpendicular(intersectionPointWithCircle[1].first, intersectionPointWithCircle[1].second);
			}
		}
		else
		{
			Line *line = new Line(x0, y0, x1, y1);

			vector<pair<float, float> > intersectionPoint = line->getTheIntersection(figure);

			float r2 = (r * r) / norm(x0, y0, intersectionPoint[0].first, intersectionPoint[0].second), 
				r3 = (r * r) / norm(x0, y0, intersectionPoint[1].first, intersectionPoint[1].second);
			Figure *tempCircle1 = new Circle(r2, x0, y0);
			Figure *tempCircle2 = new Circle(r3, x0, y0);


			vector<pair<float, float> > intersectionPointWithCircle1 = line->getTheIntersection(*tempCircle1);
			vector<pair<float, float> > intersectionPointWithCircle2 = line->getTheIntersection(*tempCircle2);

			float newX1, newY1, newX2, newY2;

			if (norm(intersectionPoint[0].first, intersectionPoint[0].second, intersectionPointWithCircle1[0].first, intersectionPointWithCircle1[0].second) <
				norm(intersectionPoint[0].first, intersectionPoint[0].second, intersectionPointWithCircle1[1].first, intersectionPointWithCircle1[1].second))
			{
				newX1 = intersectionPointWithCircle1[0].first;
				newY1 = intersectionPointWithCircle1[0].second;
			}
			else
			{
				newX1 = intersectionPointWithCircle1[1].first;
				newY1 = intersectionPointWithCircle1[1].second;
			}

			if (norm(intersectionPoint[1].first, intersectionPoint[1].second, intersectionPointWithCircle2[0].first, intersectionPointWithCircle2[0].second) <
				norm(intersectionPoint[1].first, intersectionPoint[1].second, intersectionPointWithCircle2[1].first, intersectionPointWithCircle2[1].second))
			{
				newX2 = intersectionPointWithCircle2[0].first;
				newY2 = intersectionPointWithCircle2[0].second;
			}
			else
			{
				newX2 = intersectionPointWithCircle2[1].first;
				newY2 = intersectionPointWithCircle2[1].second;
			}

			newFigure = new Circle(norm(newX1, newY1, newX2, newY2) / 2, (newX1 + newX2) / 2, (newY1 + newY2) / 2);
		}
	}

	return newFigure;
}