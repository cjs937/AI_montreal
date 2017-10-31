#pragma once
#include "TerrainUnit.h"

class OvalTerrain : public TerrainUnit
{
public:

	OvalTerrain(Sprite* _sprite, Vector2D _position, Vector2D _radius);
	~OvalTerrain();

	Vector2D* getAllPoints() override;

private:

	Vector2D mRadius;
};