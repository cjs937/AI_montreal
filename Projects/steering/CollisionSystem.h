#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class KinematicUnit;
class Steering;
class TerrainUnit;
class EllipseTerrain;
struct Ray;

const float UNIT_COLLISION_RADIUS = 10.0f;
const float UNIT_RAYCAST_DISTANCE = 70.0f;
const float WALL_AVOID = 50.0f;

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
	//static Steering* checkWallCollision(KinematicUnit* _unit);
	static RayCollision* rayCast(KinematicUnit* _unit);
	static RayCollision* rayIntersectsSegment(Ray* _ray, Vector2D _pointA, Vector2D _pointB);
	static RayCollision* rayIntersectsEllipse(Ray* _ray, Vector2D _center, float _radius);
	static RayCollision* checkWallIntersection(KinematicUnit* _unit, TerrainUnit* _wall);
	static RayCollision* checkEllipseIntersection(KinematicUnit* _unit, EllipseTerrain* _ellipse);
};