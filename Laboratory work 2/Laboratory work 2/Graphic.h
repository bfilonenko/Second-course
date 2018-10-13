#pragma once


#include "ButtonDraw.h"


class Graphic
{
	int xCoordinate;
	int yCoordinate;
	int screanWidth;
	int screanHeight;
	string windowName;
	RenderWindow *window;

	Clock timer;
	Event event;

	int numberOfButton;
	ButtonDraw *button;

	void createNewWindow(int width, int height, string &name);

public:
	Graphic(int screanWidth, int screanHeight, string &windowName) : screanWidth(screanWidth), screanHeight(screanHeight), windowName(windowName)
	{
		createNewWindow(screanWidth, screanHeight, windowName);
		numberOfButton = 0;
	}
	Graphic(int screanWidth, int screanHeight, int xCoordinate, int yCoordinate, string &windowName) : screanWidth(screanWidth), screanHeight(screanHeight), xCoordinate(xCoordinate), yCoordinate(yCoordinate), windowName(windowName)
	{
		createNewWindow(screanWidth, screanHeight, windowName);
		window->setPosition(Vector2i(xCoordinate, yCoordinate));
		numberOfButton = 0;
	}
	Graphic(int screanWidth, int screanHeight, int xCoordinate, int yCoordinate, string &windowName, int numberOfButton, Button *buttonParameter) : screanWidth(screanWidth), screanHeight(screanHeight), xCoordinate(xCoordinate), yCoordinate(yCoordinate), windowName(windowName), numberOfButton(numberOfButton)
	{
		createNewWindow(screanWidth, screanHeight, windowName);
		window->setPosition(Vector2i(xCoordinate, yCoordinate));

		button = new ButtonDraw[numberOfButton];
		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].setInformation(*buttonParameter[i].setStruct());
		}
	}

	void setCoordinate(int xCoordinate, int yCoordinate);

	void draw();

	void draw(Button *buttonParameter);

	bool pollEvent();

	Event getEvent();

	bool isOpen();

	void close();

	void minimize();

	long getTime();

	Vector2int getMousePosition();

	Vector2int getGlobalMousePosition();

	bool hasFocus();
};