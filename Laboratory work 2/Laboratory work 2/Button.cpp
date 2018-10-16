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
	button.needChangeColor = true;
	button.buttonIsPressed = false;
	button.mouseButtonIsPressed = false;
	button.needHighlight = false;
	button.needDoAction = false;
}

Button::Button(int xCoordinate, int yCoordinate, int width, int height, int characterSize, bool needChangeColor, string &name, string &fontName, string &pictureName)
{
	setInformation(xCoordinate, yCoordinate, width, height, characterSize, needChangeColor, name, fontName, pictureName);
}

void Button::setInformation(int xCoordinate, int yCoordinate, int width, int height, int characterSize, bool needChangeColor, string &name, string &fontName, string &pictureName)
{
	button.xCoordinate = xCoordinate;
	button.yCoordinate = yCoordinate;
	button.width = width;
	button.height = height;
	button.characterSize = characterSize;
	button.name = name;
	button.fontName = fontName;
	button.pictureName = pictureName;
	button.needChangeColor = needChangeColor;
	button.buttonIsPressed = false;
	button.mouseButtonIsPressed = false;
	button.needHighlight = false;
	button.needDoAction = false;
}

void Button::work(Vector2int mousePosition, bool isPressed)
{
	if (inArea(button.width, button.height, button.xCoordinate, button.yCoordinate, mousePosition))
	{
		button.needHighlight = true;
		if (isPressed)
		{
			button.buttonIsPressed = true;
			button.mouseButtonIsPressed = true;
		}
		else if (button.mouseButtonIsPressed)
		{
			button.needDoAction = true;
			button.mouseButtonIsPressed = false;
			button.buttonIsPressed = false;
		}
	}
	else
	{
		button.needHighlight = false;
		button.buttonIsPressed = false;

		if (!isPressed)
		{
			button.mouseButtonIsPressed = false;
		}
		else if (button.mouseButtonIsPressed)
		{
			button.needHighlight = true;
		}
	}
}

bool Button::action()
{
	return button.needDoAction;
}

bool Button::isPressed()
{
	return button.buttonIsPressed;
}

bool Button::mouseButtonIsPressed()
{
	return button.mouseButtonIsPressed;
}

void Button::finishAction()
{
	button.needDoAction = false;
}

void Button::addSymbol(char symbol)
{
	if (button.name == " ")
	{
		button.name = symbol;
	}
	else if (button.name.size() < 25)
	{
		button.name += symbol;
	}
}

void Button::popSymbol()
{
	if (button.name != "")
	{
		button.name.erase(button.name.end() - 1);
	}
}

ButtonParameter *Button::getStruct()
{
	return &button;
}