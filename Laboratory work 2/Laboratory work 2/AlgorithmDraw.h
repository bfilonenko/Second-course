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

	Font font;
	Text *value;
	Text *index;

	vector<CircleShape> selectedCircle;
	vector<Text> selectedValue;
	vector<Text> selectedIndex;


	Texture pointerTexture;
	Sprite pointerSprite;

	Text countOperation;
		
	template<typename T>
	void specialSwap(T &left, T &right)
	{
		Vector2f temp(left.getPosition());
		left.setPosition(right.getPosition());
		right.setPosition(temp);

		swap(left, right);
	}

	float xFromI(float i);

	float xFromI(int i);

	float iFromTime(int iLeft, int iRight, Clock &timer);

	float yFromX(float xLeft, float xRight, float x);

public:
	AlgorithmDraw();
	AlgorithmDraw(AlgorithmParameter &algorithm);

	void setInformation(AlgorithmParameter &algorithm);

	void upgradeOperations(AlgorithmParameter &algorithmParameter);

	void draw(RenderWindow &window, AlgorithmParameter &algorithm, bool &animationIsPlaying, Clock &timer);
};