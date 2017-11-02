#pragma once
#include "Vector2D.h"


static class Utility
{
public:
	static float dotProduct(Vector2D _vectorA, Vector2D _vectorB);
	static float crossProduct(Vector2D _vectorA, Vector2D _vectorB);
	static float vectorDistance(Vector2D _vectorA, Vector2D _vectorB);
	static Vector2D getScreenCenter();
	static float square(float _value);

private:
	Utility() {};
	~Utility() {};
};