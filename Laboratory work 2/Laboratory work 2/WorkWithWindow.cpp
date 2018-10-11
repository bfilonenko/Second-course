#include "WorkWithWindow.h"


WorkWithWindow::WorkWithWindow(string &fileName)
{
	ifstream fileIn(fileName);

	getline(fileIn, windowName);

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

		int firstParameters[5];
		string secondParameters[3];
 
		for (int i = 0; i < numberOfButton; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				fileIn >> firstParameters[j];
			}
			getline(fileIn, secondParameters[0]);
			for (int j = 0; j < 3; ++j)
			{
				getline(fileIn, secondParameters[j]);
			}
			button[i].setInformation(firstParameters[0], firstParameters[1], firstParameters[2], firstParameters[3], firstParameters[4], secondParameters[0], secondParameters[1], secondParameters[2]);
		}
	}

	

	fileIn >> timeForWork;

	fileIn.close();

	if (needOffset && numberOfButton != 0)
	{
		graphic = new DrawingAllWindowElements(screanWidth, screanHeight, xCoordinate, yCoordinate, windowName, numberOfButton, button);
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

		for (int i = 0; i < numberOfButton; ++i)
		{
			button->work(graphic->getMousePosition(), Mouse::isButtonPressed(Mouse::Left));
		}

		graphic->draw(button);
	}
}