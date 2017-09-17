#include "UnitManager.h"
typedef std::pair <UnitType, std::map<int, KinematicUnit*>*> mapListPair;
typedef std::pair <int, KinematicUnit*> mapPair;

UnitManager::UnitManager()
{}


UnitManager::~UnitManager()
{
	for (auto i = mUnitMap.begin(); i != mUnitMap.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
			delete j->second;

		i->second->clear();
	}

	mUnitMap.clear();
}


std::map<int, KinematicUnit*>* UnitManager::getUnitMap(UnitType _type)
{
	try
	{
		return mUnitMap[_type];
	}
	catch (std::out_of_range)
	{
		return NULL;
	}
}


KinematicUnit* UnitManager::getUnit(int _ID, UnitType _type = NONE)
{
	if (_type == NONE)
	{
		for (auto i = mUnitMap.begin(); i != mUnitMap.end(); ++i)
		{
			for (auto j = i->second->begin(); j != i->second->end(); ++j)
			{
				if(j->second->getID() == _ID)
					return j->second;
			}
		}
	}
	else
	{
		for (auto i = mUnitMap[_type]->begin(); i != mUnitMap[_type]->end(); ++i)
		{
			if (i->second->getID() == _ID)
				return i->second;
		}
	}

	return NULL;
}


void UnitManager::update(float _dt)
{
	for (auto i = mUnitMap.begin(); i != mUnitMap.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			j->second->update(_dt);
		}
	}
}


void UnitManager::addUnit(UnitType _type, Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f)
{
	int newID = 1;

	for (auto i = mUnitMap.begin(); i != mUnitMap.end(); ++i)
	{
		newID += mUnitMap.size();
	}

	if (mUnitMap.find(_type) == mUnitMap.end())
	{
		mUnitMap.insert(mapListPair(_type, new std::map<int, KinematicUnit*>));
	}

	KinematicUnit* newUnit = new KinematicUnit(newID, pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration);

	mUnitMap[_type]->insert(mapPair(newID, newUnit));
}


bool removeUnit(int _ID)
{

}