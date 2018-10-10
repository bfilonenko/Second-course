#pragma once


#include "Button.h"
#include "DrawingAllWindowElements.h"


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

	DrawingAllWindowElements *graphic;
	
public:
	WorkWithWindow(string &fileName);		//Parameter for window in "name.dat"

	bool isOpen();

	void work();
};