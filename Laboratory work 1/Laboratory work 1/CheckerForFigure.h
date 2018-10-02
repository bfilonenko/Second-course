#pragma once


#include "Line.h"


void checkerForFigure()
{
	vector<Figure*> figures;

	string help = "Available commands: \n-1 - exit\n0 - show menu\n1 - show all\n2 - show back\n3 - show (index)\n4 - add Line\n5 - add Line(a, b, c)\n\
6 - add Line(x1, y1, x2, y2)\n7 - add Circle\n8 - add Circle(r, x0, y0)\n9 - get the intersection (index1, index2)\n10 - symmetrical mapping (index1(main), index2)\n\
11 - get inversion (index1(main), index2)\n12 - pop back\n";
	cout << help;

	while (true)
	{
		int massage;
		cin >> massage;
		if (massage == -1)
		{
			break;
		}
		else if (massage == 0)
		{
			cout << help;
		}
		else if (massage == 1)
		{
			for (int i = 0; i < figures.size(); ++i)
			{
				cout << i << ' ';
				figures[i]->coutFigure();
			}
		}
		else if (massage == 2)
		{
			figures[figures.size() - 1]->coutFigure();
		}
		else if (massage == 3)
		{
			int index;
			cin >> index;
			figures[index]->coutFigure();
		}
		else if (massage == 4)
		{
			Figure *figure = new Line;
			figures.push_back(figure);
		}
		else if (massage == 5)
		{
			float a, b, c;
			cin >> a >> b >> c;
			Figure *figure = new Line(a, b, c);
			figures.push_back(figure);
		}
		else if (massage == 6)
		{
			float x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			Figure *figure = new Line(x1, y1, x2, y2);
			figures.push_back(figure);
		}
		else if (massage == 7)
		{
			Figure *figure = new Circle;
			figures.push_back(figure);
		}
		else if (massage == 8)
		{
			float r, x0, y0;
			cin >> r >> x0 >> y0;
			Figure *figure = new Circle(r, x0, y0);
			figures.push_back(figure);
		}
		else if (massage == 9)
		{
			int index1, index2;
			cin >> index1 >> index2;
			vector<pair<float, float> > intersection = figures[index1]->getTheIntersection(*figures[index2]);
			for (int i = 0; i < intersection.size(); ++i)
			{
				cout << "x = " << intersection[i].first << " y = " << intersection[i].second << '\n';
			}
		}
		else if (massage == 10)
		{
			int index1, index2;
			cin >> index1 >> index2;
			Figure *figure = figures[index1]->symmetricalMapping(*figures[index2]);
			figures.push_back(figure);
		}
		else if (massage == 11)
		{
			int index1, index2;
			cin >> index1 >> index2;
			Figure *figure = figures[index1]->getInversion(*figures[index2]);
			figures.push_back(figure);
		}
		else if (massage == 12)
		{
			figures.pop_back();
		}

		cout << "**********************************\n";
	}

	/*Figure *line1 = new Line(2.f, -1.f, 0.f);
	line1->coutFigure();

	Figure *line2 = new Line(2.f, -1.f, -8.f);
	line2->coutFigure();

	Figure *line3 = new Line(1.f, -1.f, -1.f);
	line3->coutFigure();

	Figure *circle1 = new Circle(2.f, 2.f, 0.f);
	circle1->coutFigure();

	Figure *circle2 = new Circle(4.f, -2.f, 2.f);
	circle2->coutFigure();

	Figure *circle3 = new Circle(2.f, 6.f, -2.f);
	circle2->coutFigure();


	vector<pair<float, float> >  temp1;

	temp1 = line1->getTheIntersection(*line3);
	for (int i = 0; i < temp1.size(); ++i)
	{
		cout << temp1[i].first << " " << temp1[i].second << '\n';
	}
	cout << '\n';

	temp1.clear();
	temp1 = line1->getTheIntersection(*circle1);
	for (int i = 0; i < temp1.size(); ++i)
	{
		cout << temp1[i].first << " " << temp1[i].second << '\n';
	}
	cout << '\n';

	temp1.clear();
	temp1 = circle1->getTheIntersection(*circle2);
	for (int i = 0; i < temp1.size(); ++i)
	{
		cout << temp1[i].first << " " << temp1[i].second << '\n';
	}
	cout << '\n';

	Figure *figure1 = line1->symmetricalMapping(*line3);
	figure1->coutFigure();
	Figure *figure2 = line1->symmetricalMapping(*circle1);
	figure2->coutFigure();

	Figure *figure3 = circle2->getInversion(*line2);
	figure3->coutFigure();

	Figure *figure4 = circle2->getInversion(*figure3);
	figure4->coutFigure();

	Figure *figure5 = circle2->getInversion(*circle3);
	figure5->coutFigure();

	Figure *figure6 = circle2->getInversion(*figure5);
	figure6->coutFigure();*/
	/*
		vector<float> temp2;
		temp2 = line1->getParameters();

		for (int i = 0; i < temp2.size(); ++i)
		{
			cout << temp2[i] << ' ';
		}
		cout << '\n';

		temp2.clear();
		temp2 = circle1->getParameters();

		for (int i = 0; i < temp2.size(); ++i)
		{
			cout << temp2[i] << ' ';
		}
		cout << '\n';
	*/
}