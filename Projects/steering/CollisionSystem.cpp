#include "CollisionSystem.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Steering.h"
#include "Game.h"
#include "Steering.h"

Steering* CollisionSystem::checkUnitCollision(KinematicUnit* _unit)
{
	if (_unit->getID() == 0)
		return NULL;

	float shortestTime = INFINITY;

	KinematicUnit* target = NULL;
	KinematicUnit* currentTarget = NULL;
	float minSeparation = 0;
	float distance = 0;
	Vector2D relativePosition;
	Vector2D relativeVelocity;

	std::map<UnitType, std::map<int, KinematicUnit*>*>* mapList = gpGame->getUnitManager()->getMapList();

	for (std::map<UnitType, std::map<int, KinematicUnit*>*>::iterator currentMap = mapList->begin(); currentMap != mapList->end(); ++currentMap)
	{
		for (std::map<int, KinematicUnit*>::iterator currentUnit = currentMap->second->begin(); currentUnit != currentMap->second->end(); ++currentUnit) 
		{
			currentTarget = currentUnit->second;

			if (currentTarget->getID() == _unit->getID())
				continue;

			Vector2D currentRelativePosition = currentTarget->getPosition() - _unit->getPosition();//Vector2D(_unitA->getPosition().getX() - _unitB->getPosition().getX(), _unitA->getPosition().getY() - _unitB->getPosition().getY());
			Vector2D currentRelativeVelocity = currentTarget->getVelocity() - _unit->getVelocity();//Vector2D(_unitA->getVelocity().getX() - _unitB->getPosition().getX(), _unitA->getVelocity().getY() - _unitB->getVelocity.getY());
			float relativeSpeed = currentRelativeVelocity.getLength();//magnitude(relativeVelocity);

			float collisionTime = dotProduct(currentRelativePosition, currentRelativeVelocity) / (relativeSpeed * relativeSpeed);

			float currentDistance = relativePosition.getLength();//magnitude(relativePosition);
			float currentSeparation = currentDistance - relativeSpeed * collisionTime;

			if (currentSeparation > 2 * UNIT_COLLISION_RADIUS || 
				!(0.0f < collisionTime && collisionTime < shortestTime))
				continue;

			shortestTime = collisionTime;
			target = currentTarget;
			minSeparation = currentSeparation;
			distance = currentDistance;
			relativePosition = currentRelativePosition;
			relativeVelocity = currentRelativeVelocity;
		}
	}

	if (target == NULL)
	{
		std::cout << "NONE\n";
		return NULL;
	}
	std::cout << _unit->getID() << " " << "collision with " << target->getID() << "\n";

	Vector2D newRelativePos;

	if (minSeparation <= 0 || distance < 2 * UNIT_COLLISION_RADIUS)
	{
		newRelativePos = target->getPosition() - _unit->getPosition();
	}
	else
	{
		newRelativePos = relativePosition + relativeVelocity * shortestTime;
	}

	newRelativePos.normalize();

	_unit->getSteering()->setLinear(newRelativePos * _unit->getMaxAcceleration());

	return _unit->getSteering();
}

float magnitude(Vector2D _vector)
{
	float x = _vector.getX();
	float y = _vector.getY();

	return sqrt((x * x + y * y));
}


float CollisionSystem::dotProduct(Vector2D _vectorA, Vector2D _vectorB)
{
	float toReturn = _vectorA.getX() * _vectorB.getX() + _vectorA.getY() * _vectorB.getY();

	return toReturn;
}