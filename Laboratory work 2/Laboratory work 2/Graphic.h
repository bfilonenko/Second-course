#pragma once


#include "ButtonDraw.h"
#include "AlgorithmDraw.h"
#include <Windows.h>


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

	bool needAlgorithm;
	AlgorithmDraw *algorithm;

	bool animationIsPlaying;

	void createNewWindow(int width, int height, string &name);

public:
	Graphic(int screanWidth, int screanHeight, string &windowName) : screanWidth(screanWidth), screanHeight(screanHeight), windowName(windowName)
	{
		createNewWindow(screanWidth, screanHeight, windowName);
		numberOfButton = 0;

		animationIsPlaying = false;
	}
	Graphic(int screanWidth, int screanHeight, int xCoordinate, int yCoordinate, string &windowName) : screanWidth(screanWidth), screanHeight(screanHeight), xCoordinate(xCoordinate), yCoordinate(yCoordinate), windowName(windowName)
	{
		createNewWindow(screanWidth, screanHeight, windowName);
		window->setPosition(Vector2i(xCoordinate, yCoordinate));
		numberOfButton = 0;

		animationIsPlaying = false;
	}
	Graphic(int screanWidth, int screanHeight, int xCoordinate, int yCoordinate, string &windowName, int numberOfButton, Button *buttonParameter) : screanWidth(screanWidth), screanHeight(screanHeight), xCoordinate(xCoordinate), yCoordinate(yCoordinate), windowName(windowName), numberOfButton(numberOfButton)
	{
		createNewWindow(screanWidth, screanHeight, windowName);
		window->setPosition(Vector2i(xCoordinate, yCoordinate));

		button = new ButtonDraw[numberOfButton];
		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].setInformation(*buttonParameter[i].getStruct());
		}

		animationIsPlaying = false;
	}
	Graphic(int screanWidth, int screanHeight, int xCoordinate, int yCoordinate, string &windowName, int numberOfButton, Button *buttonParameter, AlgorithmParameter &algorithmParameter) : screanWidth(screanWidth), screanHeight(screanHeight), xCoordinate(xCoordinate), yCoordinate(yCoordinate), windowName(windowName), numberOfButton(numberOfButton)
	{
		createNewWindow(screanWidth, screanHeight, windowName);
		window->setPosition(Vector2i(xCoordinate, yCoordinate));

		button = new ButtonDraw[numberOfButton];
		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].setInformation(*buttonParameter[i].getStruct());
		}

		needAlgorithm = true;
		algorithm = new AlgorithmDraw(algorithmParameter);

		animationIsPlaying = false;
	}

	~Graphic();

	void setCoordinate(int xCoordinate, int yCoordinate);


	void draw();

	void draw(Button *buttonParameter);

	void draw(Button *buttonParameter, AlgorithmParameter &algorithmParameter);


	bool pollEvent();

	Event getEvent();

	bool isOpen();

	void close();

	void minimize();

	long getTime();

	Vector2int getMousePosition();

	Vector2int getGlobalMousePosition();

	bool hasFocus();

	bool animationIsPlay();

	void upgradeAlgorithm(AlgorithmParameter &algorithmParameter);
};