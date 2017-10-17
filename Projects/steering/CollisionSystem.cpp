#include "CollisionSystem.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Steering.h"
#include "Game.h"
#include "Steering.h"
#include "TerrainUnit.h"
#include <vector>

RayCollision::RayCollision(Vector2D _position, Vector2D _normal):position(_position), normal(_normal)
{}
RayCollision::~RayCollision() {}


Steering* CollisionSystem::checkUnitCollision(KinematicUnit* _unit, Steering* _steering)
{
	if (_unit->getID() == 0)
		return NULL;

	//RayCollision* wallCheck = rayCast(_unit);

	//if (wallCheck != NULL)
	//{
	//	Vector2D target = wallCheck->position + wallCheck->normal * WALL_AVOID;
	//	_unit->seek(target);

	//	delete wallCheck;

	//	return _unit->getSteering();
	//}

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

			if (currentTarget->getID() == _unit->getID() || currentTarget->getID() == 0)
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

	_steering->setLinear( newRelativePos * -1.0f * _unit->getMaxAcceleration());
	_steering->setAngular(Kinematic::getOrientationFromVelocity(_unit->getOrientation(), _steering->getLinear()));

	return _steering;
}

RayCollision* CollisionSystem::rayCast(KinematicUnit* _unit)
{
	std::vector<TerrainUnit*> terrainVector = gpGame->getUnitManager()->getTerrain();
	TerrainUnit* target = NULL;

	for (int i = 0; i < terrainVector.size(); ++i)
	{
		if (checkRayIntersection(_unit, terrainVector[i]))
		{
			target = terrainVector[i];
			break;
		}
	}

	if (target == NULL)
		return NULL;

	Vector2D collisionNormal = target->getPosition();
	collisionNormal.normalize();

	return new RayCollision(target->getPosition(), collisionNormal);
}

bool CollisionSystem::checkRayIntersection(KinematicUnit* _unit, TerrainUnit* _wall)
{
	Vector2D* wallPoints = _wall->getAllPoints();
	Vector2D rayVector = _unit->getVelocity();
	rayVector.normalize();
	rayVector *= UNIT_RAYCAST_DISTANCE;

	if (rayIntersectsSegment(_unit->getPosition(), rayVector, wallPoints[0], wallPoints[1]))
	{
		delete wallPoints;
		return true;
	}

	if (rayIntersectsSegment(_unit->getPosition(), rayVector, wallPoints[0], wallPoints[2]))
	{
		delete wallPoints;
		return true;
	}

	if (rayIntersectsSegment(_unit->getPosition(), rayVector, wallPoints[3], wallPoints[1]))
	{
		delete wallPoints;
		return true;
	}

	if (rayIntersectsSegment(_unit->getPosition(), rayVector, wallPoints[3], wallPoints[2]))
	{
		delete wallPoints;
		return true;
	}

}

/*http://afloatingpoint.blogspot.ca/2011/04/2d-polygon-raycasting.html*/
bool CollisionSystem::rayIntersectsSegment(Vector2D _rayOrigin, Vector2D _rayVector, Vector2D _pointA, Vector2D _pointB)
{
	Vector2D segment = _pointB - _pointA;
	Vector2D segPerp = leftPerp(segment);
	float perpDot = dotProduct(_rayVector, segPerp);

	if (0.0f <= perpDot && perpDot <= FLT_EPSILON)
	{
		return false;
	}

	Vector2D distance = _pointA - _rayOrigin;

	float t = dotProduct(segPerp, distance) / perpDot;
	float s = dotProduct(leftPerp(_rayVector), distance) / perpDot;

	return t >= 0.0f && s >= 0.0f && s <= 1.0f;

}

Vector2D CollisionSystem::leftPerp(Vector2D _vector)
{
	return Vector2D(_vector.getY(), -_vector.getX());
}


static float magnitude(Vector2D _vector)
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

//Steering* CollisionSystem::checkWallCollision(KinematicUnit* _unit)
//{
//	std::vector<TerrainUnit*> terrainVector = gpGame->getUnitManager()->getTerrain();
//
//	TerrainUnit* target = NULL;
//	TerrainUnit* currentTarget = NULL;
//	float shortestDistance = FLT_MAX;
//
//	for (int i = 0; i < terrainVector.size(); ++i)
//	{
//		currentTarget = terrainVector[i];
//
//		Vector2D currentRelativePosition = currentTarget->getPosition() - _unit->getPosition();
//		float currentDistance = magnitude(currentRelativePosition);
//
//		if (currentDistance < magnitude(_unit->getPosition() + WALL_COLLISION_RADIUS) || currentDistance > shortestDistance)
//			continue;
//
//		target = currentTarget;
//		shortestDistance = currentDistance;
//	}
//
//	if (target == NULL)
//		return NULL;
//
//	Vector2D collisionNorm = target->getPosition();
//	collisionNorm.normalize;
//
//	Steering* newSteering = _unit->getSteering();
//
//	newSteering->setLinear(collisionNorm * WALL_AVOID);
//
//	return newSteering;
//}
