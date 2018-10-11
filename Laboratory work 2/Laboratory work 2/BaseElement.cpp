#include "BaseElement.h"


bool inArea(int width, int height, int xCoordinate, int yCoordinate, int x, int y)
{
	return (x >= xCoordinate - width / 2) && (x <= xCoordinate + width / 2) && (y > yCoordinate - height / 2) && (y < yCoordinate + height / 2);
}

bool inArea(int width, int height, int xCoordinate, int yCoordinate, Vector2int position)
{
	return inArea(width, height, xCoordinate, yCoordinate, position.x, position.y);
}