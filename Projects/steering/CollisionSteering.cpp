#include "CollisionSteering.h"
#include "CollisionSystem.h"

CollisionSteering::CollisionSteering(KinematicUnit* _unit): mpUnit(_unit)
{}

CollisionSteering::~CollisionSteering()
{}

Steering* CollisionSteering::getSteering()
{
	return CollisionSystem::checkUnitCollision(mpUnit, this);
}