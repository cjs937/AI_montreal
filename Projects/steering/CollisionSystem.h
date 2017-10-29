#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class KinematicUnit;
class Steering;
class TerrainUnit;
struct Ray;

const float UNIT_COLLISION_RADIUS = 10.0f;
const float UNIT_RAYCAST_DISTANCE = 70.0f;
const float WALL_AVOID = 10.0f;

struct RayCollision : public Trackable
{
	RayCollision(bool _hit, Vector2D _position) : hit(_hit), position(_position)
	{}
	~RayCollision()
	{}

	bool hit;
	Vector2D position;
};

class CollisionSystem : public Trackable
{
public:
	static Steering* checkUnitCollision(KinematicUnit* _unit, Steering* _steering);
	
	
	//static RayCollision rayCast(Vector2D _position, Vector2D _rayVector);
private:
	static float dotProduct(Vector2D _vectorA, Vector2D _vectorB);
	static float crossProduct(Vector2D _vectorA, Vector2D _vectorB);
	//static Steering* checkWallCollision(KinematicUnit* _unit);
	static RayCollision* rayCast(KinematicUnit* _unit);
	static Vector2D leftPerp(Vector2D _vector);
	static RayCollision* rayIntersectsSegment(Ray* _ray, Vector2D _pointA, Vector2D _pointB);
	static RayCollision* checkRayIntersection(KinematicUnit* _unit, TerrainUnit* _wall);
};