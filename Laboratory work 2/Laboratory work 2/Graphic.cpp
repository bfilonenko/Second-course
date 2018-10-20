#include "Graphic.h"


Graphic::~Graphic()
{
	delete window;

	if (numberOfButton != 0)
	{
		delete[] button;
	}
	
	if (needAlgorithm)
	{
		delete algorithm;
	}
}

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
		button[i].draw(*window, *buttonParameter[i].getStruct());
	}
	draw();
}

void Graphic::draw(Button *buttonParameter, AlgorithmParameter &algorithmParameter)
{
	algorithm->draw(*window, algorithmParameter, animationIsPlaying, timer);
	draw(buttonParameter);
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

bool Graphic::animationIsPlay()
{
	return animationIsPlaying;
}

void Graphic::upgradeAlgorithm(AlgorithmParameter &algorithmParameter)
{
	algorithm->setInformation(algorithmParameter);
	algorithm->upgradeOperations(algorithmParameter);
	animationIsPlaying = false;
}