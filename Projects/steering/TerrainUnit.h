#pragma once
#include "Trackable.h"
#include "Vector2D.h"

enum TerrainType
{
	BOX,
	ELLIPSE
};

class Sprite;
class GraphicsBuffer;

class TerrainUnit : public Trackable
{
public:
	TerrainUnit(Sprite* _sprite, Vector2D _position, TerrainType _type = BOX);
	~TerrainUnit();

	inline Sprite* getSprite() { return mpSprite; };
	inline Vector2D getPosition() { return mPosition; };
	inline TerrainType getType() { return mTerrainType; };
	void update(float _dt);
	virtual void draw(GraphicsBuffer* _buffer);
	virtual Vector2D* getAllPoints();

private:
	TerrainType mTerrainType;
	Sprite* mpSprite;
	Vector2D mPosition;
};