#pragma once


#include "Button.h"
#include "Graphic.h"


class WorkWithWindow
{
	int xCoordinate;
	int yCoordinate;
	int screanWidth;
	int screanHeight;
	string windowName;

	int numberOfButton;
	Button *button;

	long timeForWork;
	long timer;

	Graphic *graphic;

	vector<string> newWindowName;
	
public:
	WorkWithWindow(string &fileName);		//Parameter for window in "name.dat"

	bool isOpen();

	void work();

	vector<string> getNewWindowName();

	void cleanNewWindowName();
};