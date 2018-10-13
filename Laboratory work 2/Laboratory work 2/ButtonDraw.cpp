#include "ButtonDraw.h"

ButtonDraw::ButtonDraw()
{
	needPicture = false;
	needText = false;
}

ButtonDraw::ButtonDraw(ButtonParameter &button)
{
	setInformation(button);
}

void ButtonDraw::setInformation(ButtonParameter &button)
{
	if (button.pictureName == "")
	{
		needPicture = false;
	}
	else
	{
		needPicture = true;

		pictureTexture = new Texture;
		pictureTexture->loadFromFile(button.pictureName);

		pictureSprite = new Sprite;
		pictureSprite->setTexture(*pictureTexture);
		pictureSprite->setOrigin(float(button.width / 2), float(button.height / 2));
		pictureSprite->setPosition(float(button.xCoordinate), float(button.yCoordinate));
	}

	if (button.name == "")
	{
		needText = false;
	}
	else
	{
		needText = true;

		font = new Font;
		font->loadFromFile(button.fontName);

		text = new Text;
		text->setCharacterSize(button.characterSize);
		text->setFont(*font);
		text->setOrigin(float(button.width / 2), float(button.height / 2));
		text->setPosition(float(button.xCoordinate), float(button.yCoordinate));
		text->setString(button.name);
	}
}

void ButtonDraw::draw(RenderWindow &window, ButtonParameter &button)
{
	if (needPicture)
	{
		if (button.needChangeColor)
		{
			if (button.buttonIsPressed && button.needChangeColor)
			{
				pictureSprite->setColor(Color(255, 255, 0));
			}
			else if (button.needHighlight && button.needChangeColor)
			{
				pictureSprite->setColor(Color::White);
			}
			else
			{
				pictureSprite->setColor(Color(128, 128, 128));
			}
		}
		else
		{
			pictureSprite->setColor(Color::White);
		}
		window.draw(*pictureSprite);
	}

	if (needText)
	{
		if (button.needChangeColor)
		{
			if (button.buttonIsPressed)
			{
				text->setFillColor(Color(255, 255, 0));
			}
			else if (button.needHighlight)
			{
				text->setFillColor(Color::White);
			}
			else
			{
				text->setFillColor(Color(128, 128, 128));
			}
		}
		else
		{
			text->setFillColor(Color::White);
		}
		window.draw(*text);
	}
}