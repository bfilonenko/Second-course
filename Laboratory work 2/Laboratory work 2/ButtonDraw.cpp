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
		text->setFillColor(Color::White);
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
		window.draw(*pictureSprite);
	}

	if (needText)
	{
		window.draw(*text);
	}
}