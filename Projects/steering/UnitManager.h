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
	ARRIVER,
	SEEKER,
	WANDERER,
	WANDER_SEEK,
	WANDER_FLEE,
	WALL,

	NUM_TYPES
};

enum ComponentType
{
	WANDER_AND_SEEK,
	WANDER_AND_FLEE
};

class Component;
class TerrainUnit;

class UnitManager : public Trackable
{
private:
	//map of unit maps
	std::map<UnitType, std::map<int, KinematicUnit*>*> mMapList;
	std::vector<TerrainUnit*> mTerrain;
	std::stack<int> mAvailableIDs;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;
	IDType mWallBufferID;

	Sprite* getUnitSprite(UnitType _unitType);


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
	//bool tagExists(int _ID);
};