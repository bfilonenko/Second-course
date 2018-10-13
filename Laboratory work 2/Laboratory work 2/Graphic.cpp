#include "Graphic.h"


void Graphic::createNewWindow(int width, int height, string &name)
{
	window = new RenderWindow(VideoMode(width, height), name, Style::None);
}

void Graphic::setCoordinate(int xNewCoordinate, int yNewCoordinate)
{
	xCoordinate = xNewCoordinate;
	yCoordinate = yNewCoordinate;
	window->setPosition(Vector2i(xCoordinate, yCoordinate));
}

void Graphic::draw()
{
	window->display();
	window->clear();
}

void Graphic::draw(Button *buttonParameter)
{
	for (int i = 0; i < numberOfButton; ++i)
	{
		button[i].draw(*window, *buttonParameter[i].setStruct());
	}
	draw();
}

bool Graphic::pollEvent()
{
	return window->pollEvent(event);
}

Event Graphic::getEvent()
{
	return event;
}

bool Graphic::isOpen()
{
	return window->isOpen();
}

void Graphic::close()
{
	window->close();
}

void Graphic::minimize()
{
	ShowWindowAsync(window->getSystemHandle(), SW_MINIMIZE);
}

long Graphic::getTime()
{
	return timer.getElapsedTime().asMilliseconds();
}

Vector2int Graphic::getMousePosition()
{
	return Vector2int(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
}

Vector2int Graphic::getGlobalMousePosition()
{
	return Vector2int(Mouse::getPosition().x, Mouse::getPosition().y);
}

bool Graphic::hasFocus()
{
	return window->hasFocus();
}