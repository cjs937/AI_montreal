#pragma once
#include "Trackable.h"

class KinematicUnit;

class CollisionSystem : public Trackable
{
public:
	static bool checkUnitCollision(KinematicUnit* _unitA, KinematicUnit* _unitB);

};