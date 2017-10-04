#include "CollisionSystem.h"
#include "KinematicUnit.h"

bool CollisionSystem::checkUnitCollision(KinematicUnit* _unitA, KinematicUnit* _unitB)
{
	Vector2D relativePosition = Vector2D(_unitA->getPosition().getX() - _unitB->getPosition().getX(), _unitA->getPosition().getY() - _unitB->getPosition().getY());
	Vector2D relativeVelocity = Vector2D(_unitA->getVelocity().getX() - _unitB->getPosition().getX(), _unitA->getVelocity().getY() - _unitB->getVelocity.getY());

	float timeClosestX = -(relativePosition.getX() * relativeVelocity.getX()) / (abs(relativeVelocity.getX()) * abs(relativeVelocity.getX()));
	float timeClosestY = -(relativePosition.getY() * relativeVelocity.getY()) / (abs(relativeVelocity.getY()) * abs(relativeVelocity.getY()));

	Vector2D unitAClosestPos = Vector2D(_unitA->getPosition().getX() + _unitA->getVelocity().getX() * timeClosestX, _unitA->getPosition().getY() + _unitA->getVelocity().getY() * timeClosestY);
	Vector2D unitBClosestPos = Vector2D(_unitB->getPosition().getX() + _unitB->getVelocity().getX() * timeClosestX, _unitB->getPosition().getY() + _unitB->getVelocity().getY() * timeClosestY);

	if (unitAClosestPos == unitBClosestPos)
		return true;

	return false; 
}
