#pragma once


#include "BaseElement.h"


struct ButtonParameter
{
	int xCoordinate;
	int yCoordinate;

	int width;
	int height;

	int characterSize;

	string name;
	string fontName;
	string pictureName;

	bool buttonIsPressed;
	bool mouseButtonIsPressed;
	bool needHighlight;
	bool needDoAction;
};


class Button
{
	ButtonParameter button;

public:
	Button();
	Button(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string &name, string &fontName, string &pictureName);

	void setInformation(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string &name, string &fontName, string &pictureName);

	void work(Vector2int mousePosition, bool isPressed);

	bool action();

	bool isPressed();

	bool mouseButtonIsPressed();

	void finishAction();

	ButtonParameter *setStruct();
};