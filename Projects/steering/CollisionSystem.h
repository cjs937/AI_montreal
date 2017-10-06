#pragma once
#include "Trackable.h"

class KinematicUnit;
class Steering;
class Vector2D;

const float UNIT_COLLISION_RADIUS = 400.0f;

class CollisionSystem : public Trackable
{
public:
	static Steering* checkUnitCollision(KinematicUnit* _unitA);

private:
	static float dotProduct(Vector2D _vectorA, Vector2D _vectorB);
};