#include "TerrainUnit.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"

TerrainUnit::TerrainUnit(Sprite* _sprite, Vector2D _position):mpSprite(_sprite),mPosition(_position)
{}

TerrainUnit::~TerrainUnit()
{}

void TerrainUnit::update(float _dt) 
{}

void TerrainUnit::draw(GraphicsBuffer* _buffer)
{
	mpSprite->draw(*_buffer, mPosition.getX(), mPosition.getY());

}

Vector2D* TerrainUnit::getAllPoints() // topLeft = 0, topRight, bottomLeft, bottomRight
{
	float width = mpSprite->getWidth();
	float height = mpSprite->getHeight();

	Vector2D topLeft = Vector2D(mPosition.getX(), mPosition.getY()); //(0,0)
	Vector2D topRight = Vector2D(mPosition.getX() + width, topLeft.getY());
	Vector2D bottomLeft = Vector2D(topLeft.getX(), mPosition.getY() + height);
	Vector2D bottomRight = Vector2D(topRight.getX(), bottomLeft.getY());

	return new Vector2D[4]{ topLeft, topRight, bottomLeft, bottomRight };
}