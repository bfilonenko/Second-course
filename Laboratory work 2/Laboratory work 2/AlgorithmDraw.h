#pragma once


#include "InsertionSort.h"
#include <SFML/Graphics.hpp>


using namespace sf;


class AlgorithmDraw
{
	int count;
	int oldOperations;

	long startTimeOfAnimation;
	bool toNext;

	CircleShape *circle;
	CircleShape *selectedCircle;

	Font font;
	Text *value;
	Text *index;

	Texture pointerTexture;
	Sprite pointerSprite;

	Text countOperation;
	
public:
	AlgorithmDraw();
	AlgorithmDraw(AlgorithmParameter &algorithm);

	void setInformation(AlgorithmParameter &algorithm);

	void draw(RenderWindow &window, AlgorithmParameter &algorithm, bool &animationIsPlaying, Clock &timer);
};