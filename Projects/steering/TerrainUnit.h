#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class Sprite;
class GraphicsBuffer;

class TerrainUnit : public Trackable
{
public:
	TerrainUnit(Sprite* _sprite, Vector2D _position);
	~TerrainUnit();

	inline Sprite* getSprite() { return mpSprite; };
	inline Vector2D getPosition() { return mPosition; };
	void update(float _dt);
	void draw(GraphicsBuffer* _buffer);
	virtual Vector2D* getAllPoints();
private:
	Sprite* mpSprite;
	Vector2D mPosition;
};