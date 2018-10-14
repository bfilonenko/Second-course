#include "AlgorithmDraw.h"


AlgorithmDraw::AlgorithmDraw()
{
	count = 0;
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
		circle[i].setPosition(float(35.f + 25.f + (50.f + 210.f / (count + 1.f)) * i), 230.f);

		value[i].setCharacterSize(20);
		value[i].setFillColor(Color::White);
		value[i].setFont(font);
		value[i].setString(to_string(algorithm.arrayOfValues[i].first));
		value[i].setOrigin(value[i].getLocalBounds().width * 0.5f, value[i].getLocalBounds().height * 0.5f);
		value[i].setPosition(float(35.f + 25.f + (50.f + 210.f / (count + 1.f)) * i), 180.f);

		index[i].setCharacterSize(20);
		index[i].setFillColor(Color::White);
		index[i].setFont(font);
		index[i].setString(to_string(algorithm.arrayOfValues[i].second));
		index[i].setOrigin(index[i].getLocalBounds().width * 0.5f, index[i].getLocalBounds().height * 0.5f);
		index[i].setPosition(float(35.f + 25.f + (50.f + 210.f / (count + 1.f)) * i), 270.f);
	}

	pointerTexture.loadFromFile("Data/Pictures/Pointer.png");
	
	pointerSprite.setTexture(pointerTexture);
	pointerSprite.setOrigin(6.f, 11.f);
}

void AlgorithmDraw::draw(RenderWindow &window, AlgorithmParameter &algorithm)
{
	for (int i = 0; i < count; ++i)
	{
		window.draw(circle[i]);
		window.draw(value[i]);
		window.draw(index[i]);
	}

	for (int i = 0; i < algorithm.mainIndexes.size(); ++i)
	{
		pointerSprite.setPosition(float(35.f + 25.f + (50.f + 210.f / (count + 1.f)) * algorithm.mainIndexes[i]), 220.f);
		window.draw(pointerSprite);
	}
}