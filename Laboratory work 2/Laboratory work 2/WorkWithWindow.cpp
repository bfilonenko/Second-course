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
		if (numberOfButton == 13)
		{
			button = new Button[numberOfButton + 19];
		}
		else
		{
			button = new Button[numberOfButton];
		}


		int firstParameters[7];
		string secondParameters[3];
 
		for (int i = 0; i < numberOfButton; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				fileIn >> firstParameters[j];
			}
			getline(fileIn, secondParameters[0]);
			for (int j = 0; j < 3; ++j)
			{
				getline(fileIn, secondParameters[j]);
			}
			button[i].setInformation(firstParameters[0], firstParameters[1], firstParameters[2], firstParameters[3], firstParameters[4], firstParameters[5], firstParameters[6], secondParameters[0], secondParameters[1], secondParameters[2]);
		}
		if (numberOfButton == 13)
		{
			for (int i = 1; i < 10; ++i)
			{
				button[numberOfButton - 1 + i].setInformation(firstParameters[0] + 49 * i, firstParameters[1], firstParameters[2], firstParameters[3], firstParameters[4], firstParameters[5], firstParameters[6], secondParameters[0], secondParameters[1], secondParameters[2]);
			}
			for (int i = 0; i < 10; ++i)
			{
				button[numberOfButton + 9 + i].setInformation(firstParameters[0] + 49 * i, firstParameters[1] + 25, firstParameters[2], firstParameters[3], firstParameters[4], firstParameters[5], firstParameters[6], secondParameters[0], secondParameters[1], secondParameters[2]);
			}
			numberOfButton += 19;
		}
	}

	fileIn >> needAlgorithm;

	algorithmIsPlaying = false;
	buttonIndexForText = -1;

	if (needAlgorithm)
	{
		if (windowName == "Insertion sort")
		{
			algorithm = new InsertionSort;
		}
	}

	fileIn >> timeForWork;

	fileIn.close();

	if (needOffset && numberOfButton != 0 && needAlgorithm)
	{
		graphic = new Graphic(screanWidth, screanHeight, xCoordinate, yCoordinate, windowName, numberOfButton, button, *algorithm->getStruct());
	}
	else if (needOffset && numberOfButton != 0)
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

			if (graphic->getEvent().type == Event::TextEntered && buttonIndexForText != -1)
			{
				if (graphic->getEvent().text.unicode == 8)
				{
					button[buttonIndexForText].popSymbol();
				}
				else if (buttonIndexForText == 6)
				{
					if ((graphic->getEvent().text.unicode >= 48 && graphic->getEvent().text.unicode <= 57) || (graphic->getEvent().text.unicode >= 65 && graphic->getEvent().text.unicode <= 90) || (graphic->getEvent().text.unicode >= 97 && graphic->getEvent().text.unicode <= 122))
					{
						if (graphic->getEvent().text.unicode >= 65 && graphic->getEvent().text.unicode <= 90)
						{
							button[buttonIndexForText].addSymbol(char(graphic->getEvent().text.unicode + 32));
						}
						else
						{
							button[buttonIndexForText].addSymbol(char(graphic->getEvent().text.unicode));
						}
					}
				}
				else if (graphic->getEvent().text.unicode >= 48 && graphic->getEvent().text.unicode <= 57 && button[buttonIndexForText].getStruct()->name.size() < 2)
				{
					button[buttonIndexForText].addSymbol(char(graphic->getEvent().text.unicode));
				}

				if (button[11].getStruct()->name.size() == 2 && !(button[11].getStruct()->name[0] == '0' || button[11].getStruct()->name[0] == '1' || button[11].getStruct()->name[0] == '2'))
				{
					button[11].getStruct()->name = "20";
				}
			}

			if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Tab) && buttonIndexForText > 10 && buttonIndexForText < 31)
			{
				++buttonIndexForText;
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
				buttonIndexForText = -1;
			}
			else if (i == 3 && button[i].action() && needAlgorithm)
			{
				algorithmIsPlaying = !algorithmIsPlaying;
				buttonIndexForText = -1;
			}
			else if (i == 4 && button[i].action() && needAlgorithm && !graphic->animationIsPlay())
			{
				algorithm->goToBack();
				buttonIndexForText = -1;
			}
			else if (i == 5 && button[i].action() && needAlgorithm && !graphic->animationIsPlay())
			{
				algorithm->goToNext();
				buttonIndexForText = -1;
			}
			else if (i == 6 && button[i].action() && needAlgorithm)
			{
				buttonIndexForText = i;
			}
			else if (i == 7 && button[i].action() && needAlgorithm && button[6].getStruct()->name.size() > 0)
			{
				algorithm->download(button[6].getStruct()->name);
				graphic->upgradeAlgorithm(*algorithm->getStruct());
				buttonIndexForText = -1;
			}
			else if (i == 8 && button[i].action() && needAlgorithm && button[6].getStruct()->name.size() > 0)
			{
				algorithm->save(button[6].getStruct()->name);
				buttonIndexForText = -1;
			}
			else if (i == 9 && button[i].action() && needAlgorithm)
			{
				int length;
				if (button[11].getStruct()->name.size() == 2)
				{
					length = (button[11].getStruct()->name[0] - '0') * 10 + button[11].getStruct()->name[1] - '0';
				}
				else if (button[11].getStruct()->name.size() == 1)
				{
					length = button[11].getStruct()->name[0] - '0';
				}
				else
				{
					length = 0;
				}

				if (length > 1)
				{
					vector<int> newData;

					for (int j = 12; j < 12 + length; ++j)
					{
						int value;
						if (button[j].getStruct()->name.size() == 2)
						{
							value = (button[j].getStruct()->name[0] - '0') * 10 + button[j].getStruct()->name[1] - '0';
						}
						else if (button[j].getStruct()->name.size() == 1)
						{
							value = button[j].getStruct()->name[0] - '0';
						}
						else
						{
							value = 0;
						}

						newData.push_back(value);
					}

					delete algorithm;
					if (windowName == "Insertion sort")
					{
						algorithm = new InsertionSort(newData);
					}
					graphic->upgradeAlgorithm(*algorithm->getStruct());
				}
			}
			else if (i == 10 && button[i].action() && needAlgorithm)
			{
				delete algorithm;
				if (windowName == "Insertion sort")
				{
					algorithm = new InsertionSort;
				}
				graphic->upgradeAlgorithm(*algorithm->getStruct());
			}
			else if (i > 10 && button[i].action() && needAlgorithm)
			{
				buttonIndexForText = i;
			}
			else if (button[i].action() && button[i].getStruct()->needCreateNewWindow)
			{
				string name = "Data/Data for " + button[i].getStruct()->name + ".dat";
				newWindowName.push_back(name);
			}
			button[i].finishAction();
		}

		if (needAlgorithm && algorithmIsPlaying && !graphic->animationIsPlay())
		{
			algorithm->goToNext();
		}

		if (needAlgorithm)
		{
			graphic->draw(button, *algorithm->getStruct());
		}
		else
		{
			graphic->draw(button);
		}
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