#include "WorkWithWindow.h"


WorkWithWindow::WorkWithWindow(string &fileName)
{
	ifstream fileIn(fileName);

	bool needOffset;
	fileIn >> needOffset;


	if (needOffset)
	{
		fileIn >> xCoordinate >> yCoordinate;
	}
	else
	{
		xCoordinate = -1;
		yCoordinate = -1;
	}
	fileIn >> screanWidth >> screanHeight >> numberOfButton;
	
	if (numberOfButton != 0)
	{
		button = new Button[numberOfButton];
	}

	getline(fileIn, windowName);
	getline(fileIn, windowName);

	fileIn >> timeForWork;

	fileIn.close();

	if (needOffset)
	{
		graphic = new DrawingAllWindowElements(screanWidth, screanHeight, xCoordinate, yCoordinate, windowName);
	}
	else
	{
		graphic = new DrawingAllWindowElements(screanWidth, screanHeight, windowName);
	}
}

bool WorkWithWindow::isOpen()
{
	return graphic->isOpen();
}

void WorkWithWindow::work()
{
	if (graphic->getTime() - timer >= timeForWork)
	{
		timer += timeForWork;

		if (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				graphic->close();
			}
		}

		graphic->draw();
	}
}