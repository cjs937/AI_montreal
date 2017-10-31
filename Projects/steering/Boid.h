#pragma once
#include "KinematicUnit.h"

class Sprite;

class Boid : public KinematicUnit
{
public:
	Boid(int _ID, Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	~Boid();


};