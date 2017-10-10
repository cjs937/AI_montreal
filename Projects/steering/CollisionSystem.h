#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class KinematicUnit;
class Steering;
class TerrainUnit;

const float UNIT_COLLISION_RADIUS = 70.0f;
const float UNIT_RAYCAST_DISTANCE = 70.0f;
const float WALL_AVOID = 10.0f;

struct RayCollision : public Trackable
{
	RayCollision(Vector2D _position, Vector2D _normal);
	~RayCollision();

	Vector2D position;
	Vector2D normal;
};

class CollisionSystem : public Trackable
{
public:
	static Steering* checkUnitCollision(KinematicUnit* _unit, Steering* _steering);
	
	
	//static RayCollision rayCast(Vector2D _position, Vector2D _rayVector);
private:
	static float dotProduct(Vector2D _vectorA, Vector2D _vectorB);
	//static Steering* checkWallCollision(KinematicUnit* _unit);
	static RayCollision* rayCast(KinematicUnit* _unit);
	static Vector2D leftPerp(Vector2D _vector);
	static bool rayIntersectsSegment(Vector2D _rayOrigin, Vector2D _rayVector, Vector2D _pointA, Vector2D _pointB);
	static bool checkRayIntersection(KinematicUnit* _unit, TerrainUnit* _wall);
};