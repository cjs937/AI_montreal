#include "EllipseTerrain.h"
#include "allegro5\allegro_primitives.h"
#include "Color.h"

EllipseTerrain::EllipseTerrain(Sprite* _sprite, Vector2D _position, float _radius) : TerrainUnit(_sprite, _position, ELLIPSE), mRadius(_radius)
{}

EllipseTerrain::~EllipseTerrain() {}

void EllipseTerrain::draw(GraphicsBuffer* _buffer)
{
	Color drawColor = Color(WHITE);

	al_draw_circle(getPosition().getX(), getPosition().getY(), mRadius, drawColor.color, 5.0f);
}

Vector2D* EllipseTerrain::getAllPoints()
{
	return NULL;
}