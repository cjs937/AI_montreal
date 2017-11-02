#pragma once
#include "TerrainUnit.h"

class EllipseTerrain : public TerrainUnit
{
public:

	EllipseTerrain(Sprite* _sprite, Vector2D _position, float _radius);
	~EllipseTerrain();

	Vector2D* getAllPoints() override;
	float getRadius() { return mRadius; };

	void draw(GraphicsBuffer* _buffer) override;

private:

	float mRadius;
};