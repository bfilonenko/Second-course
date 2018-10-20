#pragma once


#include <SFML/Graphics.hpp>
#include "Button.h"


using namespace sf;


class ButtonDraw
{
	bool needPicture;
	Texture *pictureTexture;
	Sprite *pictureSprite;

	bool needText;
	Font *font;
	Text *text;

public:
	ButtonDraw();
	ButtonDraw(ButtonParameter &button);

	~ButtonDraw();

	void setInformation(ButtonParameter &button);

	void draw(RenderWindow &window, ButtonParameter &button);
};