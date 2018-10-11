#include "Button.h"


Button::Button()
{
	button.xCoordinate = 0;
	button.yCoordinate = 0;
	button.width = 0;
	button.height = 0;
	button.characterSize = 0;
	button.name = "";
	button.fontName = "";
	button.pictureName = "";
	button.buttonIsPressed = false;
	button.needHighlight = false;
	button.mouseButtonIsPressed = false;
	button.needDoAction = false;
}

Button::Button(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string &name, string &fontName, string &pictureName)
{
	setInformation(xCoordinate, yCoordinate, width, height, characterSize, name, fontName, pictureName);
}

void Button::setInformation(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string &name, string &fontName, string &pictureName)
{
	button.xCoordinate = xCoordinate;
	button.yCoordinate = yCoordinate;
	button.width = width;
	button.height = height;
	button.characterSize = characterSize;
	button.name = name;
	button.fontName = fontName;
	button.pictureName = pictureName;
	button.buttonIsPressed = false;
	button.needHighlight = false;
	button.mouseButtonIsPressed = false;
	button.needDoAction = false;
}

void Button::work(Vector2int mousePosition, bool isPressed)
{
	if (inArea(button.width, button.height, button.xCoordinate, button.yCoordinate, mousePosition))
	{
		button.needHighlight = true;

	}
	else
	{
		button.needHighlight = false;
	}
}

ButtonParameter *Button::setStruct()
{
	return &button;
}