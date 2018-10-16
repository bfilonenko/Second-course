#pragma once


#include "Button.h"
#include "Graphic.h"
#include "InsertionSort.h"


class WorkWithWindow
{
	int xCoordinate;
	int yCoordinate;
	bool needOffsetWindow;
	int xOffset;
	int yOffset;

	int screanWidth;
	int screanHeight;
	string windowName;

	int numberOfButton;
	Button *button;

	bool needAlgorithm;
	bool algorithmIsPlaying;

	Algorithm *algorithm;

	int buttonIndexForText;

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