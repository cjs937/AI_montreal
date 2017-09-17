#pragma once
#include "KinematicUnit.h"
#include <map>

enum UnitType
{
	NONE = 0,
	PLAYER,
	ARRIVER,
	SEEKER
};

class UnitManager
{
private:
	//map of unit maps
	std::map<UnitType, std::map<int, KinematicUnit*>*> mUnitMap;

public:
	UnitManager();
	~UnitManager();

	std::map<UnitType, std::map<int, KinematicUnit*>*>* getMapList() { return &mUnitMap; }
	std::map<int, KinematicUnit*>* getUnitMap(UnitType _type);
	KinematicUnit* getUnit(int _ID, UnitType _type = NONE);

	void update(float _dt);
	void addUnit(UnitType _type, Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	bool removeUnit(int _ID);



};