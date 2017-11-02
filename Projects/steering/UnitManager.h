#pragma once
#include "KinematicUnit.h"
#include <map>
#include <vector>
#include <stack>
#include "Defines.h"

enum UnitType
{
	NONE = -1,

	PLAYER,
	AI,
	ARRIVER,
	SEEKER,
	WANDERER,
	WANDER_SEEK,
	WANDER_FLEE,
	WALL,
	CIRCLE,
	BOID,
	NUM_TYPES
};

enum ComponentType
{
	WANDER_AND_SEEK,
	WANDER_AND_FLEE
};

const float DEFAULT_MAX_VEL = 100.0f;
const float DEFAULT_MAX_ROTATION = 100.0f;//0.5f;
const float DEFAULT_SEPARATION_THRESHOLD = 40.0f;
const float DEFAULT_SEPARATION_DECAY = 10.0f;
const float DEFAULT_NEIGHBOR_RADIUS = 100.0f;


class Component;
class TerrainUnit;

class UnitManager : public Trackable
{
private:
	//map of unit maps
	std::map<UnitType, std::map<int, KinematicUnit*>*> mMapList;
	std::map<UnitType, IDType> mBufferIDs;
	std::vector<TerrainUnit*> mTerrain;
	std::stack<int> mAvailableIDs;

	void initBuffersAndSprites();
	Sprite* getUnitSprite(UnitType _unitType);
	IDType getBufferID(UnitType _unitType);

	float mUnitMaxVelocity;
	float mUnitMaxRotationVelocity;
	float mUnitSeparationThreshold;
	float mUnitSeparationDecay;
	float mBoidNeighborRadius;

public:
	UnitManager();
	~UnitManager();

	std::map<UnitType, std::map<int, KinematicUnit*>*>* getMapList() { return &mMapList; }
	std::map<int, KinematicUnit*>* getUnitMap(UnitType _type);
	std::vector<TerrainUnit*> getTerrain() { return mTerrain; };
	KinematicUnit* getUnit(int _ID, UnitType _type);

	void update(float _dt);
	void draw(GraphicsBuffer* _buffer);
	void generateBorderWall(int _width, int _height);
	KinematicUnit* addUnit(UnitType _type, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	bool removeUnit(int _ID);
	void removeRandomUnit();
	Component* addComponent(ComponentType _type, KinematicUnit* _unit);
	float getSeparationThreshold() { return mUnitSeparationThreshold; };
	float getSeparationDecay() { return mUnitSeparationDecay; };
	float getMaxVelocity() { return mUnitMaxVelocity; };
	float getMaxRotation() { return mUnitMaxRotationVelocity; };
	float getNeighborRadius() { return mBoidNeighborRadius; };
	void  spawnCircle(Vector2D _position);
	//bool tagExists(int _ID);
};