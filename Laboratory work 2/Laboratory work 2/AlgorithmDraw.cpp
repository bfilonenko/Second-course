#include "AlgorithmDraw.h"


AlgorithmDraw::AlgorithmDraw()
{
	count = 0;
	oldOperations = 0;
}

AlgorithmDraw::AlgorithmDraw(AlgorithmParameter &algorithm)
{
	setInformation(algorithm);
}

void AlgorithmDraw::setInformation(AlgorithmParameter &algorithm)
{
	count = algorithm.length;

	circle = new CircleShape[count];
	value = new Text[count];
	index = new Text[count];

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
		circle[i].setPosition(float(35.f + 25.f + i * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 230.f);

		value[i].setCharacterSize(20);
		value[i].setFillColor(Color::White);
		value[i].setFont(font);
		value[i].setString(to_string(algorithm.arrayOfValues[i].first));
		value[i].setOrigin(value[i].getLocalBounds().width * 0.5f, value[i].getLocalBounds().height * 0.5f);
		value[i].setPosition(float(35.f + 25.f + i * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 180.f);

		index[i].setCharacterSize(20);
		index[i].setFillColor(Color::White);
		index[i].setFont(font);
		index[i].setString(to_string(algorithm.arrayOfValues[i].second));
		index[i].setOrigin(index[i].getLocalBounds().width * 0.5f, index[i].getLocalBounds().height * 0.5f);
		index[i].setPosition(float(35.f + 25.f + i * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 270.f);
	}

	pointerTexture.loadFromFile("Data/Pictures/Pointer.png");
	
	pointerSprite.setTexture(pointerTexture);
	pointerSprite.setOrigin(6.f, 11.f);

	countOperation.setFont(font);
	countOperation.setCharacterSize(20);
	countOperation.setFillColor(Color::White);
	countOperation.setPosition(637.f, 400.f); 
}

void AlgorithmDraw::draw(RenderWindow &window, AlgorithmParameter &algorithm, bool &animationIsPlaying, Clock &timer)
{
	if (algorithm.indexForHighlight.size() == 0 || !animationIsPlaying || (algorithm.next != nullptr && algorithm.next->indexForHighlight.size() == 0))
	{
		for (int i = 0; i < count; ++i)
		{
			window.draw(circle[i]);
			window.draw(value[i]);
			window.draw(index[i]);
		}
	}
	else if (algorithm.indexForHighlight.size() > 0 && animationIsPlaying)
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

	for (int i = 0; i < arcs.size(); ++i)
	{
		window.draw(arcs[i]);
	}

	if (oldOperations < algorithm.operations)
	{
		oldOperations = algorithm.operations;

		animationIsPlaying = true;
		toNext = true;

		startTimeOfAnimation = timer.getElapsedTime().asMilliseconds();

		if (algorithm.oldPositionOfMainIndex.size() > 0)
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(float(35.f + 25.f + algorithm.oldPositionOfMainIndex[i] * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 220.f);
				window.draw(pointerSprite);
			}
		}
		else if (algorithm.indexForHighlight.size() > 0)
		{
			specialSwap(circle[algorithm.indexForHighlight[0]], circle[algorithm.indexForHighlight[1]]);
			specialSwap(value[algorithm.indexForHighlight[0]], value[algorithm.indexForHighlight[1]]);
			specialSwap(index[algorithm.indexForHighlight[0]], index[algorithm.indexForHighlight[1]]);
			

		}
	}
	else if (oldOperations == algorithm.operations)
	{
		if (animationIsPlaying && toNext)
		{
			if (algorithm.oldPositionOfMainIndex.size() > 0)
			{
				for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
				{
					pointerSprite.setPosition(float(35.f + 25.f + (algorithm.oldPositionOfMainIndex[i] + (1.f * (algorithm.mainIndexes[i] - algorithm.oldPositionOfMainIndex[i]) * (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation)) / 500.f) * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 220.f);
					window.draw(pointerSprite);
				}

				if (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation > 500)
				{
					animationIsPlaying = false;
				}
			}
			else
			{
				animationIsPlaying = false;
			}
		}
		else if (animationIsPlaying)
		{
			if (algorithm.next->oldPositionOfMainIndex.size() > 0)
			{
				for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
				{
					pointerSprite.setPosition(float(35.f + 25.f + (algorithm.next->mainIndexes[i] - (1.f * (algorithm.next->mainIndexes[i] - algorithm.mainIndexes[i]) * (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation)) / 500.f) * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 220.f);
					window.draw(pointerSprite);
				}

				if (timer.getElapsedTime().asMilliseconds() - startTimeOfAnimation > 500)
				{
					animationIsPlaying = false;
				}
			}
			else
			{
				animationIsPlaying = false;
			}
		}
		else
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(float(35.f + 25.f + algorithm.mainIndexes[i] * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 220.f);
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

		if (algorithm.next->oldPositionOfMainIndex.size() > 0)
		{
			for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
			{
				pointerSprite.setPosition(float(35.f + 25.f + algorithm.next->mainIndexes[i] * (50.f + (1210.f - 50.f * count) / (count + 1.f)) + (1210.f - 50.f * count) / (count + 1.f)), 220.f);
				window.draw(pointerSprite);
			}
		}
		else if (algorithm.next->indexForHighlight.size() > 0)
		{
			specialSwap(circle[algorithm.next->indexForHighlight[0]], circle[algorithm.next->indexForHighlight[1]]);
			specialSwap(value[algorithm.next->indexForHighlight[0]], value[algorithm.next->indexForHighlight[1]]);
			specialSwap(index[algorithm.next->indexForHighlight[0]], index[algorithm.next->indexForHighlight[1]]);
		}
	}

	countOperation.setString(to_string(oldOperations));
	countOperation.setOrigin(countOperation.getLocalBounds().width * 0.5f, countOperation.getLocalBounds().height * 0.5f);
	window.draw(countOperation);
}