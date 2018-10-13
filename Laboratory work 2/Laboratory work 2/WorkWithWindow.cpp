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
	needOffsetWindow = false;
	xOffset = -1;
	yOffset = -1;

	fileIn >> screanWidth >> screanHeight >> numberOfButton;
	
	if (numberOfButton != 0)
	{
		button = new Button[numberOfButton];

		int firstParameters[6];
		string secondParameters[3];
 
		for (int i = 0; i < numberOfButton; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				fileIn >> firstParameters[j];
			}
			getline(fileIn, secondParameters[0]);
			for (int j = 0; j < 3; ++j)
			{
				getline(fileIn, secondParameters[j]);
			}
			button[i].setInformation(firstParameters[0], firstParameters[1], firstParameters[2], firstParameters[3], firstParameters[4], firstParameters[5], secondParameters[0], secondParameters[1], secondParameters[2]);
		}
	}

	

	fileIn >> timeForWork;

	fileIn.close();

	if (needOffset && numberOfButton != 0)
	{
		graphic = new Graphic(screanWidth, screanHeight, xCoordinate, yCoordinate, windowName, numberOfButton, button);
	}
	else
	{
		graphic = new Graphic(screanWidth, screanHeight, windowName);
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

		for (int i = 0; i < numberOfButton && graphic->hasFocus() && !needOffsetWindow; ++i)
		{
			button[i].work(graphic->getMousePosition(), Mouse::isButtonPressed(Mouse::Left));
		}

		//Button 0 for closing window
		//Button 1 for minimizing window
		//Button 2 for moving window
		if (needOffsetWindow)
		{
			button[2].work(graphic->getMousePosition(), Mouse::isButtonPressed(Mouse::Left));
		}
		if (button[2].mouseButtonIsPressed())
		{
			if (!needOffsetWindow)
			{
				needOffsetWindow = true;
				xOffset = graphic->getGlobalMousePosition().x - xCoordinate;
				yOffset = graphic->getGlobalMousePosition().y - yCoordinate;
			}
			else
			{
				xCoordinate = graphic->getGlobalMousePosition().x - xOffset;
				yCoordinate = graphic->getGlobalMousePosition().y - yOffset;

				graphic->setCoordinate(xCoordinate, yCoordinate);
			}
		}
		else if (!button[2].mouseButtonIsPressed() && needOffsetWindow)
		{
			needOffsetWindow = false;
		}
		
		for (int i = 0; i < numberOfButton && graphic->hasFocus(); ++i)
		{
			if (i == 0 && button[i].action())
			{
				graphic->close();
			}
			else if (i == 1 && button[i].action())
			{
				graphic->minimize();
			}
			else if (i > 2 && button[i].action())
			{
				string name = "Data/Data for " + button[i].setStruct()->name + ".dat";
				newWindowName.push_back(name);
				button[i].finishAction();
			}
		}

		graphic->draw(button);
	}
}

vector<string> WorkWithWindow::getNewWindowName()
{
	return newWindowName;
}

void WorkWithWindow::cleanNewWindowName()
{
	newWindowName.clear();
}