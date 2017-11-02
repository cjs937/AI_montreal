#include "Utility.h"
#include "Game.h"
#include "GraphicsSystem.h"

float Utility::crossProduct(Vector2D _vectorA, Vector2D _vectorB)
{
	return ((_vectorA.getX() * _vectorB.getY()) - (_vectorA.getY() * _vectorB.getX()));
}


float Utility::dotProduct(Vector2D _vectorA, Vector2D _vectorB)
{
	return (_vectorA.getX() * _vectorB.getX()) + (_vectorA.getY() * _vectorB.getY());
}

float Utility::vectorDistance(Vector2D _vectorA, Vector2D _vectorB)
{
	//sqrt((x2 - x1)^2 + (y2 - y1)^2))

	float xDist = (_vectorB.getX() - _vectorA.getX());
	xDist *= xDist;

	float yDist = ((_vectorB.getY() - _vectorA.getY()));
	yDist *= yDist;

	return sqrt(xDist + yDist);
}

Vector2D Utility::getScreenCenter()
{
	float halfX = gpGame->getGraphicsSystem()->getWidth() / 2;
	float halfY = gpGame->getGraphicsSystem()->getHeight() / 2;

	return Vector2D(halfX, halfY);
}

float Utility::square(float _value)
{
	return _value * _value;
}