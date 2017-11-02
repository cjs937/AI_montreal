#include "CollisionSystem.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Steering.h"
#include "Game.h"
#include "Steering.h"
#include "TerrainUnit.h"
#include <vector>
#include "Ray.h"
#include "Utility.h"
#include "KinematicSeekSteering.h"
#include "EllipseTerrain.h"

Steering* CollisionSystem::checkUnitCollision(KinematicUnit* _unit, Steering* _steering)
{
	if (_unit->getID() == 0)
		return NULL;

	RayCollision* wallCheck = rayCast(_unit);

	if (wallCheck != NULL)
	{
		Vector2D normal = wallCheck->position;
		normal.normalize();

		Vector2D target = wallCheck->position + normal * -WALL_AVOID;
		
		Steering* toReturn = (new KinematicSeekSteering(_unit, target))->getSteering();//pSeekSteering->getSteering();

		_steering->setLinear(toReturn->getLinear());

		_steering->setAngular(toReturn->getAngular());

		delete wallCheck;

		delete toReturn;

		std::cout << "Hit\n";

		return _steering;
	}

	//Early return to skip collision avoidance code since it doesn't work :( //////

	_steering = &gNullSteering;

	return _steering;
	////////////////////////////////////////////////////////////////////////////

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

			if (currentTarget->getID() == _unit->getID())// || currentTarget->getID() == 0)
				continue;

			Vector2D currentRelativePosition = currentTarget->getPosition() - _unit->getPosition();//Vector2D(_unitA->getPosition().getX() - _unitB->getPosition().getX(), _unitA->getPosition().getY() - _unitB->getPosition().getY());
			Vector2D currentRelativeVelocity = currentTarget->getVelocity() - _unit->getVelocity();//Vector2D(_unitA->getVelocity().getX() - _unitB->getPosition().getX(), _unitA->getVelocity().getY() - _unitB->getVelocity.getY());
			float relativeSpeed = currentRelativeVelocity.getLength();//magnitude(relativeVelocity);

			if (relativeSpeed == 0)
				continue;

			float collisionTime = Utility::dotProduct(currentRelativePosition, currentRelativeVelocity) / (relativeSpeed * relativeSpeed);

			float currentDistance = relativePosition.getLength();//magnitude(relativePosition);
			float currentSeparation = currentDistance - relativeSpeed * collisionTime;

			if (currentSeparation > 2 * UNIT_COLLISION_RADIUS) //|| currentSeparation < 0)
				continue;

			if (0.0f < collisionTime && collisionTime < shortestTime)
			{
				shortestTime = collisionTime;
				target = currentTarget;
				minSeparation = currentSeparation;
				distance = currentDistance;
				relativePosition = currentRelativePosition;
				relativeVelocity = currentRelativeVelocity;
			}
		}
	}

	if (target == NULL)
	{
		//std::cout << "NONE\n";

		_steering = &gNullSteering;

		return _steering;
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
	//_steering->setAngular(Kinematic::getOrientationFromVelocity(_unit->getOrientation(), _steering->getLinear()));

	return _steering;
}

RayCollision* CollisionSystem::rayCast(KinematicUnit* _unit)
{
	std::vector<TerrainUnit*> terrainVector = gpGame->getUnitManager()->getTerrain();
	RayCollision* collision = NULL;
	TerrainUnit* currentTerrain = NULL;

	for (int i = 0; i < terrainVector.size(); ++i)
	{
		currentTerrain = terrainVector[i];

		if (currentTerrain->getType() == BOX)
			collision = checkWallIntersection(_unit, terrainVector[i]);
		else if (currentTerrain->getType() == ELLIPSE)
			collision = checkEllipseIntersection(_unit, (EllipseTerrain*)terrainVector[i]);
		else
			collision = NULL;

		if (collision != NULL)
		{
			break;
		}
	}

	return collision;
}

RayCollision* CollisionSystem::checkWallIntersection(KinematicUnit* _unit, TerrainUnit* _wall)
{
	RayCollision* collision = NULL;
	Vector2D* wallPoints = _wall->getAllPoints();
	Ray* rayCast = new Ray(_unit->getPosition(), UNIT_RAYCAST_DISTANCE, _unit->getVelocity());

	for (int i = 0; i < 4; ++i)// checks all sides of the wall
	{
		switch (i)
		{
		case 0:
			collision = rayIntersectsSegment(rayCast, wallPoints[0], wallPoints[1]);
			break;
		case 1:
			collision = rayIntersectsSegment(rayCast, wallPoints[0], wallPoints[2]);
			break;
		case 2:
			collision = rayIntersectsSegment(rayCast, wallPoints[3], wallPoints[1]);
			break;
		case 3:
			collision = rayIntersectsSegment(rayCast, wallPoints[3], wallPoints[2]);
			break;
		default:
			collision = NULL;
			break;
		}

		if (collision->hit)
		{
			break;
		}

		delete collision;

		collision = NULL;
	}

	delete[] wallPoints;
	delete rayCast;

	return collision;

}

RayCollision* CollisionSystem::checkEllipseIntersection(KinematicUnit* _unit, EllipseTerrain* _ellipse)
{
	RayCollision* collision = NULL;
	Ray* rayCast = new Ray(_unit->getPosition(), UNIT_RAYCAST_DISTANCE, _unit->getVelocity());

	collision = rayIntersectsEllipse(rayCast, _ellipse->getPosition(), _ellipse->getRadius());

	if (!collision->hit)
	{
		delete collision;

		collision = NULL;
	}

	delete rayCast;

	return collision;
}
/*https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect*/
RayCollision* CollisionSystem::rayIntersectsSegment(Ray* _ray, Vector2D _pointA, Vector2D _pointB)
{
	bool hit = false;
	Vector2D collisionPoint = Vector2D();
	//Ray = p + tr
	//Wall(a, b) = a + t'd  
	//d = (b - a)

	Vector2D wall_d = _pointB - _pointA;

	float rXd = Utility::crossProduct(_ray->getDirection(), wall_d);

	if (rXd == 0)
		hit = false;
	else
	{
		//t = (a - p) x d / (r x d)
		float t_ray = Utility::crossProduct((_pointA - _ray->getSourcePoint()), wall_d) / rXd;

		//t' = (a - p) x r / ( r x d)
		float t_wall = Utility::crossProduct((_pointA - _ray->getSourcePoint()), _ray->getDirection()) / Utility::crossProduct(_ray->getDirection(), wall_d);

		//hit if r x s != 0 && 0 <= t <= 1 && 0 <= t' <= 1
		hit = (Utility::crossProduct(_ray->getDirection(), wall_d) != 0.0f && 0.0f <= t_ray && t_ray <= 1.0f && 0.0f <= t_wall && t_wall <= 1.0f);

		collisionPoint = hit ? _ray->getPointAlongRay(t_ray) :
			Vector2D();
	}

	return new RayCollision(hit, collisionPoint);
}


/*https://math.stackexchange.com/questions/275529/check-if-line-intersects-with-circles-perimeter*/
RayCollision* CollisionSystem::rayIntersectsEllipse(Ray* _ray, Vector2D _center, float _radius)
{
	//Ray = p + tr

	//convert center to local (0,0)
	Vector2D local_p = Vector2D(_ray->getSourcePoint().getX() - _center.getX(), _ray->getSourcePoint().getY() - _center.getY());
	Vector2D local_r = Vector2D(_ray->getDirection().getX() - _center.getX(), _ray->getDirection().getY() - _center.getY());
	Vector2D center_to_ray = _ray->getSourcePoint() - _center;

	//Quadratic formula to check for and find point of collision 
	//https://www.khanacademy.org/math/algebra/quadratics/solving-quadratics-using-the-quadratic-formula/a/discriminant-review//
	
	float a = Utility::dotProduct(_ray->getDirection(), _ray->getDirection());//Utility::square(local_r.getX() - local_p.getX()) + Utility::square(local_r.getY() - local_p.getY());
	float b = 2 * Utility::dotProduct(center_to_ray, _ray->getDirection());//( ( local_p.getX() * ( local_r.getX() - local_p.getX() ) ) + ( local_p.getY() * (local_r.getY() - local_p.getY() ) ) );
	float c = Utility::dotProduct(center_to_ray, center_to_ray) - Utility::square(_radius);//Utility::square(local_p.getX()) + Utility::square(local_p.getY()) - Utility::square(_radius);

	float discriminant = Utility::square(b) - (4 * a * c);

	if (discriminant < 0)
		return new RayCollision(false, Vector2D());

	discriminant = sqrt(discriminant);

	float t1 = (-b + discriminant) / (2 * a);
	float t2 = (-b - discriminant) / (2 * a);

	bool hit = (0 <= t1 && t1 <= 1 || 0 <= t2 && t2 <= 1);

	Vector2D collisionPoint = hit ? _ray->getPointAlongRay(t1) :
		Vector2D();

	return new RayCollision(hit, collisionPoint);

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
