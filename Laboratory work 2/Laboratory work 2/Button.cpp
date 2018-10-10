#include "Button.h"


Button::Button()
{
	button.xCoordinate = 0;
	button.yCoordinate = 0;
	button.buttonWidth = 0;
	button.buttonHeight = 0;
	button.buttonName = "";
	button.fontName = "";
	button.pictureName = "";
}

Button::Button(int xCoordinate, int yCoordinate, int buttonWidth, int buttonHeight, string &buttonName, string &fontName, string &pictureName)
{
	button.xCoordinate = xCoordinate;
	button.yCoordinate = yCoordinate;
	button.buttonWidth = buttonWidth;
	button.buttonHeight = buttonHeight;
	button.buttonName = buttonName;
	button.fontName = fontName;
	button.pictureName = pictureName;
}

