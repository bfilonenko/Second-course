#include "AlgorithmDraw.h"


float AlgorithmDraw::xFromI(float i)
{
	float tempCount = float(count);
	return 35.f + 25.f + i * (50.f + (1210.f - 50.f * tempCount) / (tempCount + 1.f)) + (1210.f - 50.f * tempCount) / (tempCount + 1.f);
}

float AlgorithmDraw::xFromI(int i)
{
	float tempCount = float(count);
	return 35.f + 25.f + float(i) * (50.f + (1210.f - 50.f * tempCount) / (tempCount + 1.f)) + (1210.f - 50.f * tempCount) / (tempCount + 1.f);
}

float AlgorithmDraw::iFromTime(int iLeft, int iRight, Clock &timer)
{
	return iLeft + (1.f * (iRight - iLeft) * (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation)) / 500.f;
}

float AlgorithmDraw::yFromX(float xLeft, float xRight, float x)
{
	return 260.f - sqrt(900.f + 0.25f * (xLeft - xRight) * (xLeft - xRight) - (x - 0.5f * (xLeft + xRight)) * (x - 0.5f * (xLeft + xRight)));
}


AlgorithmDraw::AlgorithmDraw()
{
	count = 0;
	oldOperations = 0;

	circle = nullptr;
	value = nullptr;
	index = nullptr;
}

AlgorithmDraw::AlgorithmDraw(AlgorithmParameter &algorithm)
{
	setInformation(algorithm);
}

void AlgorithmDraw::setInformation(AlgorithmParameter &algorithm)
{
	count = algorithm.length;

	if (circle == nullptr)
	{
		circle = new CircleShape[count];
		value = new Text[count];
		index = new Text[count];
	}
	else
	{
		delete[] circle;
		delete[] value;
		delete[] index;

		circle = new CircleShape[count];
		value = new Text[count];
		index = new Text[count];
	}

	font.loadFromFile("Data/Fonts/Azonix.otf");

	int maxSize = -1;
	for (int i = 0; i < count; ++i)
	{
		maxSize = max(algorithm.arrayOfValues[i].first, maxSize);
	}
	++maxSize;

	for (int i = 0; i < count; ++i)
	{
		circle[i].setRadius(float(25.f * (algorithm.arrayOfValues[i].first + 1.f) / maxSize));
		circle[i].setOrigin(float(25.f * (algorithm.arrayOfValues[i].first + 1.f) / maxSize), float(25.f * (algorithm.arrayOfValues[i].first + 1.f) / maxSize));
		circle[i].setFillColor(Color(109, 209 - (100 * (algorithm.arrayOfValues[i].first + 1)) / maxSize, 255));
		circle[i].setOutlineThickness(1.f);
		circle[i].setOutlineColor(Color(109, 219 - (100 * (algorithm.arrayOfValues[i].first + 1)) / maxSize, 255));
		circle[i].setPosition(xFromI(i), 230.f);

		value[i].setCharacterSize(20);
		value[i].setFillColor(Color::White);
		value[i].setFont(font);
		value[i].setString(to_string(algorithm.arrayOfValues[i].first));
		value[i].setOrigin(value[i].getLocalBounds().width * 0.5f, value[i].getLocalBounds().height * 0.5f);
		value[i].setPosition(xFromI(i), 180.f);

		index[i].setCharacterSize(20);
		index[i].setFillColor(Color::White);
		index[i].setFont(font);
		index[i].setString(to_string(algorithm.arrayOfValues[i].second));
		index[i].setOrigin(index[i].getLocalBounds().width * 0.5f, index[i].getLocalBounds().height * 0.5f);
		index[i].setPosition(xFromI(i), 270.f);
	}

	pointerTexture.loadFromFile("Data/Pictures/Pointer.png");

	pointerSprite.setTexture(pointerTexture);
	pointerSprite.setOrigin(6.f, 11.f);

	countOperation.setFont(font);
	countOperation.setCharacterSize(20);
	countOperation.setFillColor(Color::White);
	countOperation.setPosition(637.f, 400.f);
}

void AlgorithmDraw::upgradeOperations(AlgorithmParameter &algorithmParameter)
{
	oldOperations = algorithmParameter.operations;
}

void AlgorithmDraw::draw(RenderWindow &window, AlgorithmParameter &algorithm, bool &animationIsPlaying, Clock &timer)
{
	if (!animationIsPlaying || (toNext && algorithm.indexForHighlight.size() == 0) || (!toNext && algorithm.next->indexForHighlight.size() == 0))
	{
		for (int i = 0; i < count; ++i)
		{
			window.draw(circle[i]);
			window.draw(value[i]);
			window.draw(index[i]);
		}
	}
	else if (animationIsPlaying && toNext && algorithm.indexForHighlight.size() > 0)
	{
		for (int i = 0; i < count; ++i)
		{
			if (i != algorithm.indexForHighlight[0] && i != algorithm.indexForHighlight[1])
			{
				window.draw(circle[i]);
				window.draw(value[i]);
				window.draw(index[i]);
			}
		}
	}
	else if (animationIsPlaying && !toNext && algorithm.next->indexForHighlight.size() > 0)
	{
		for (int i = 0; i < count; ++i)
		{
			if (i != algorithm.next->indexForHighlight[0] && i != algorithm.next->indexForHighlight[1])
			{
				window.draw(circle[i]);
				window.draw(value[i]);
				window.draw(index[i]);
			}
		}
	}


	if (oldOperations < algorithm.operations)
	{
		oldOperations = algorithm.operations;

		animationIsPlaying = true;
		toNext = true;

		startTimeOfAnimation = timer.getElapsedTime().asMilliseconds();

		if (algorithm.indexForHighlight.size() > 0)
		{
			specialSwap(circle[algorithm.indexForHighlight[0]], circle[algorithm.indexForHighlight[1]]);
			specialSwap(value[algorithm.indexForHighlight[0]], value[algorithm.indexForHighlight[1]]);
			specialSwap(index[algorithm.indexForHighlight[0]], index[algorithm.indexForHighlight[1]]);

			selectedCircle.push_back(circle[algorithm.indexForHighlight[0]]);
			selectedCircle[0].setFillColor(Color(255, 63, 63));
			selectedCircle[0].setOutlineColor(Color(255, 107, 107));
			selectedCircle[0].setPosition(xFromI(algorithm.indexForHighlight[1]), 230.f);
			window.draw(selectedCircle[0]);

			selectedValue.push_back(value[algorithm.indexForHighlight[0]]);
			selectedValue[0].setPosition(xFromI(algorithm.indexForHighlight[1]), 180.f);
			window.draw(selectedValue[0]);

			selectedIndex.push_back(index[algorithm.indexForHighlight[0]]);
			selectedIndex[0].setPosition(xFromI(algorithm.indexForHighlight[1]), 270.f);
			window.draw(selectedIndex[0]);


			selectedCircle.push_back(circle[algorithm.indexForHighlight[1]]);
			selectedCircle[1].setFillColor(Color(255, 63, 63));
			selectedCircle[1].setOutlineColor(Color(255, 107, 107));
			selectedCircle[1].setPosition(xFromI(algorithm.indexForHighlight[0]), 230.f);
			window.draw(selectedCircle[1]);

			selectedValue.push_back(value[algorithm.indexForHighlight[1]]);
			selectedValue[1].setPosition(xFromI(algorithm.indexForHighlight[0]), 180.f);
			window.draw(selectedValue[1]);

			selectedIndex.push_back(index[algorithm.indexForHighlight[1]]);
			selectedIndex[1].setPosition(xFromI(algorithm.indexForHighlight[0]), 270.f);
			window.draw(selectedIndex[1]);
		}
	
		if (algorithm.oldPositionOfMainIndex.size() > 0)
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(xFromI(algorithm.oldPositionOfMainIndex[i]), 220.f);
				window.draw(pointerSprite);
			}
		}
		else
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(xFromI(algorithm.mainIndexes[i]), 220.f);
				window.draw(pointerSprite);
			}
		}
	}
	else if (oldOperations == algorithm.operations)
	{
		if (animationIsPlaying && toNext)
		{
			if (algorithm.indexForHighlight.size() > 0)
			{
				selectedCircle[0].setPosition(xFromI(iFromTime(algorithm.indexForHighlight[1], algorithm.indexForHighlight[0], timer)), yFromX(xFromI(algorithm.indexForHighlight[1]), xFromI(algorithm.indexForHighlight[0]), xFromI(iFromTime(algorithm.indexForHighlight[1], algorithm.indexForHighlight[0], timer))));
				window.draw(selectedCircle[0]);

				selectedValue[0].setPosition(xFromI(iFromTime(algorithm.indexForHighlight[1], algorithm.indexForHighlight[0], timer)), -50 + yFromX(xFromI(algorithm.indexForHighlight[1]), xFromI(algorithm.indexForHighlight[0]), xFromI(iFromTime(algorithm.indexForHighlight[1], algorithm.indexForHighlight[0], timer))));
				window.draw(selectedValue[0]);

				selectedIndex[0].setPosition(xFromI(iFromTime(algorithm.indexForHighlight[1], algorithm.indexForHighlight[0], timer)), 40 + yFromX(xFromI(algorithm.indexForHighlight[1]), xFromI(algorithm.indexForHighlight[0]), xFromI(iFromTime(algorithm.indexForHighlight[1], algorithm.indexForHighlight[0], timer))));
				window.draw(selectedIndex[0]);


				selectedCircle[1].setPosition(xFromI(iFromTime(algorithm.indexForHighlight[0], algorithm.indexForHighlight[1], timer)), 460 - yFromX(xFromI(algorithm.indexForHighlight[1]), xFromI(algorithm.indexForHighlight[0]), xFromI(iFromTime(algorithm.indexForHighlight[0], algorithm.indexForHighlight[1], timer))));
				window.draw(selectedCircle[1]);

				selectedValue[1].setPosition(xFromI(iFromTime(algorithm.indexForHighlight[0], algorithm.indexForHighlight[1], timer)), -50 + 460 - yFromX(xFromI(algorithm.indexForHighlight[1]), xFromI(algorithm.indexForHighlight[0]), xFromI(iFromTime(algorithm.indexForHighlight[0], algorithm.indexForHighlight[1], timer))));
				window.draw(selectedValue[1]);

				selectedIndex[1].setPosition(xFromI(iFromTime(algorithm.indexForHighlight[0], algorithm.indexForHighlight[1], timer)), 40 + 460 - yFromX(xFromI(algorithm.indexForHighlight[1]), xFromI(algorithm.indexForHighlight[0]), xFromI(iFromTime(algorithm.indexForHighlight[0], algorithm.indexForHighlight[1], timer))));
				window.draw(selectedIndex[1]);

				if (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation > 500)
				{
					animationIsPlaying = false;

					selectedCircle.clear();
					selectedValue.clear();
					selectedIndex.clear();
				}
			}

			if (algorithm.oldPositionOfMainIndex.size() > 0)
			{
				for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
				{
					pointerSprite.setPosition(xFromI(iFromTime(algorithm.oldPositionOfMainIndex[i], algorithm.mainIndexes[i], timer)), 220.f);
					window.draw(pointerSprite);
				}

				if (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation > 500)
				{
					animationIsPlaying = false;
				}
			}
			else
			{
				for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
				{
					pointerSprite.setPosition(xFromI(algorithm.mainIndexes[i]), 220.f);
					window.draw(pointerSprite);
				}
			}
		}
		else if (animationIsPlaying)
		{
			if (algorithm.next->indexForHighlight.size() > 0)
			{
				selectedCircle[0].setPosition(xFromI(iFromTime(algorithm.next->indexForHighlight[1], algorithm.next->indexForHighlight[0], timer)), 460 - yFromX(xFromI(algorithm.next->indexForHighlight[1]), xFromI(algorithm.next->indexForHighlight[0]), xFromI(iFromTime(algorithm.next->indexForHighlight[1], algorithm.next->indexForHighlight[0], timer))));
				window.draw(selectedCircle[0]);

				selectedValue[0].setPosition(xFromI(iFromTime(algorithm.next->indexForHighlight[1], algorithm.next->indexForHighlight[0], timer)), -50 + 460 - yFromX(xFromI(algorithm.next->indexForHighlight[1]), xFromI(algorithm.next->indexForHighlight[0]), xFromI(iFromTime(algorithm.next->indexForHighlight[1], algorithm.next->indexForHighlight[0], timer))));
				window.draw(selectedValue[0]);

				selectedIndex[0].setPosition(xFromI(iFromTime(algorithm.next->indexForHighlight[1], algorithm.next->indexForHighlight[0], timer)), 40 + 460 - yFromX(xFromI(algorithm.next->indexForHighlight[1]), xFromI(algorithm.next->indexForHighlight[0]), xFromI(iFromTime(algorithm.next->indexForHighlight[1], algorithm.next->indexForHighlight[0], timer))));
				window.draw(selectedIndex[0]);


				selectedCircle[1].setPosition(xFromI(iFromTime(algorithm.next->indexForHighlight[0], algorithm.next->indexForHighlight[1], timer)), yFromX(xFromI(algorithm.next->indexForHighlight[1]), xFromI(algorithm.next->indexForHighlight[0]), xFromI(iFromTime(algorithm.next->indexForHighlight[0], algorithm.next->indexForHighlight[1], timer))));
				window.draw(selectedCircle[1]);

				selectedValue[1].setPosition(xFromI(iFromTime(algorithm.next->indexForHighlight[0], algorithm.next->indexForHighlight[1], timer)), -50 + yFromX(xFromI(algorithm.next->indexForHighlight[1]), xFromI(algorithm.next->indexForHighlight[0]), xFromI(iFromTime(algorithm.next->indexForHighlight[0], algorithm.next->indexForHighlight[1], timer))));
				window.draw(selectedValue[1]);

				selectedIndex[1].setPosition(xFromI(iFromTime(algorithm.next->indexForHighlight[0], algorithm.next->indexForHighlight[1], timer)), 40 + yFromX(xFromI(algorithm.next->indexForHighlight[1]), xFromI(algorithm.next->indexForHighlight[0]), xFromI(iFromTime(algorithm.next->indexForHighlight[0], algorithm.next->indexForHighlight[1], timer))));
				window.draw(selectedIndex[1]);

				if (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation > 500)
				{
					animationIsPlaying = false;

					selectedCircle.clear();
					selectedValue.clear();
					selectedIndex.clear();
				}
			}

			if (algorithm.next->oldPositionOfMainIndex.size() > 0)
			{
				for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
				{
					pointerSprite.setPosition(xFromI(iFromTime(algorithm.next->mainIndexes[i], algorithm.mainIndexes[i], timer)), 220.f);
					window.draw(pointerSprite);
				}

				if (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation > 500)
				{
					animationIsPlaying = false;
				}
			}
			else
			{
				for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
				{
					pointerSprite.setPosition(xFromI(algorithm.mainIndexes[i]), 220.f);
					window.draw(pointerSprite);
				}
			}
		}
		else
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(xFromI(algorithm.mainIndexes[i]), 220.f);
				window.draw(pointerSprite);
			}
		}
	}
	else
	{
		oldOperations = algorithm.operations;

		animationIsPlaying = true;
		toNext = false;

		startTimeOfAnimation = timer.getElapsedTime().asMilliseconds();

		if (algorithm.next->indexForHighlight.size() > 0)
		{
			specialSwap(circle[algorithm.next->indexForHighlight[0]], circle[algorithm.next->indexForHighlight[1]]);
			specialSwap(value[algorithm.next->indexForHighlight[0]], value[algorithm.next->indexForHighlight[1]]);
			specialSwap(index[algorithm.next->indexForHighlight[0]], index[algorithm.next->indexForHighlight[1]]);

			selectedCircle.push_back(circle[algorithm.next->indexForHighlight[0]]);
			selectedCircle[0].setFillColor(Color(255, 63, 63));
			selectedCircle[0].setOutlineColor(Color(255, 107, 107));
			selectedCircle[0].setPosition(xFromI(algorithm.next->indexForHighlight[1]), 230.f);
			window.draw(selectedCircle[0]);
			
			selectedValue.push_back(value[algorithm.next->indexForHighlight[0]]);
			selectedValue[0].setPosition(xFromI(algorithm.next->indexForHighlight[1]), 180.f);
			window.draw(selectedValue[0]);

			selectedIndex.push_back(index[algorithm.next->indexForHighlight[0]]);
			selectedIndex[0].setPosition(xFromI(algorithm.next->indexForHighlight[1]), 270.f);
			window.draw(selectedIndex[0]);

			
			selectedCircle.push_back(circle[algorithm.next->indexForHighlight[1]]);
			selectedCircle[1].setFillColor(Color(255, 63, 63));
			selectedCircle[1].setOutlineColor(Color(255, 107, 107));
			selectedCircle[1].setPosition(xFromI(algorithm.next->indexForHighlight[0]), 230.f);
			window.draw(selectedCircle[1]);

			selectedValue.push_back(value[algorithm.next->indexForHighlight[1]]);
			selectedValue[1].setPosition(xFromI(algorithm.next->indexForHighlight[0]), 180.f);
			window.draw(selectedValue[1]);

			selectedIndex.push_back(index[algorithm.next->indexForHighlight[1]]);
			selectedIndex[1].setPosition(xFromI(algorithm.next->indexForHighlight[0]), 270.f);
			window.draw(selectedIndex[1]);
		}

		if (algorithm.next->oldPositionOfMainIndex.size() > 0)
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(xFromI(algorithm.next->mainIndexes[i]), 220.f);
				window.draw(pointerSprite);
			}
		}
		else
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(xFromI(algorithm.mainIndexes[i]), 220.f);
				window.draw(pointerSprite);
			}
		}
	}

	countOperation.setString(to_string(oldOperations));
	countOperation.setOrigin(countOperation.getLocalBounds().width * 0.5f, countOperation.getLocalBounds().height * 0.5f);
	window.draw(countOperation);
}