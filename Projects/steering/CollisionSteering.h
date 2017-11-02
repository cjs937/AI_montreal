#pragma once
#include "Steering.h"

class KinematicUnit;

class CollisionSteering : public Steering
{
public:
	CollisionSteering(KinematicUnit* _unit);

	~CollisionSteering();

	Steering* getSteering() override;

private:

	KinematicUnit* mpUnit;
};