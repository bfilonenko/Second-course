#pragma once


#include <fstream>
#include <string>
#include <iostream>


using namespace std;


struct ButtonParameter
{
	int xCoordinate;
	int yCoordinate;

	int buttonWidth;
	int buttonHeight;

	string buttonName;
	string fontName;
	string pictureName;

	bool buttonIsPressed;
};


class Button
{
	ButtonParameter button;

public:
	Button();
	Button(int xCoordinate, int yCoordinate, int buttonWidth, int buttonHeight, string &buttonName, string &fontName, string &pictureName);
};