#pragma once


#include "InsertionSort.h"
#include <SFML/Graphics.hpp>


using namespace sf;


class AlgorithmDraw
{
	int count;

	CircleShape *circle;
	CircleShape *selectedCircle;

	Font font;
	Text *value;
	Text *index;

	Texture pointerTexture;
	Sprite pointerSprite;

public:
	AlgorithmDraw();
	AlgorithmDraw(AlgorithmParameter &algorithm);

	void setInformation(AlgorithmParameter &algorithm);

	void draw(RenderWindow &window, AlgorithmParameter &algorithm);
};