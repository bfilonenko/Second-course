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
	vector<CircleShape> selectedCircle;

	Font font;
	Text *value;
	Text *index;

	Texture pointerTexture;
	Sprite pointerSprite;

	Text countOperation;

	vector<Sprite> arcs;
	
	template<typename T>
	void specialSwap(T &left, T &right)
	{
		Vector2f temp(left.getPosition());
		left.setPosition(right.getPosition());
		right.setPosition(temp);

		swap(left, right);
	}

public:
	AlgorithmDraw();
	AlgorithmDraw(AlgorithmParameter &algorithm);

	void setInformation(AlgorithmParameter &algorithm);

	void draw(RenderWindow &window, AlgorithmParameter &algorithm, bool &animationIsPlaying, Clock &timer);
};