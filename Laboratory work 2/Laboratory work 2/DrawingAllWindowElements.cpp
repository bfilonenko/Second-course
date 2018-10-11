#include "DrawingAllWindowElements.h"


void DrawingAllWindowElements::createNewWindow(int width, int height, string &name)
{
	window = new RenderWindow(VideoMode(width, height), name);// , Style::None);
}

void DrawingAllWindowElements::draw()
{
	window->display();
	window->clear();
}

bool DrawingAllWindowElements::pollEvent()
{
	return window->pollEvent(event);
}

Event DrawingAllWindowElements::getEvent()
{
	return event;
}

bool DrawingAllWindowElements::isOpen()
{
	return window->isOpen();
}

void DrawingAllWindowElements::close()
{
	window->close();
}

long DrawingAllWindowElements::getTime()
{
	return timer.getElapsedTime().asMilliseconds();
}