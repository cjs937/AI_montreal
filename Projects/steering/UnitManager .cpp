#include "UnitManager.h"
#include "Game.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "GraphicsBuffer.h"
#include "Component.h"
#include "WanderAndFleeComponent.h"
#include "WanderAndSeekComponent.h"
#include "Sprite.h"
#include "TerrainUnit.h"
#include "Vector2D.h"
#include "Boid.h"
#include "EllipseTerrain.h"

typedef std::pair <UnitType, std::map<int, KinematicUnit*>*> mapListPair;
typedef std::pair <int, KinematicUnit*> mapPair;
typedef pair<UnitType, IDType> IDPair;

UnitManager::UnitManager()
{

	mUnitMaxVelocity = DEFAULT_MAX_VEL;
	mUnitMaxRotationVelocity = DEFAULT_MAX_ROTATION;
	mUnitSeparationThreshold = DEFAULT_SEPARATION_THRESHOLD;
	mUnitSeparationDecay = DEFAULT_SEPARATION_DECAY;
	mBoidNeighborRadius = DEFAULT_NEIGHBOR_RADIUS;

	initBuffersAndSprites();

	//first unit id will be 0
	mAvailableIDs.push(0);
}

void UnitManager::initBuffersAndSprites()
{
	mBufferIDs.insert(IDPair(PLAYER, gpGame->getGraphicsBufferManager()->loadBuffer("arrow.bmp")));
	mBufferIDs.insert(IDPair(AI, gpGame->getGraphicsBufferManager()->loadBuffer("enemy-arrow.bmp")));
	mBufferIDs.insert(IDPair(WALL, gpGame->getGraphicsBufferManager()->loadBuffer("wall.bmp")));
	mBufferIDs.insert(IDPair(CIRCLE, gpGame->getGraphicsBufferManager()->loadBuffer("circle.bmp")));


	GraphicsBuffer* pPlayerBuffer = gpGame->getGraphicsBufferManager()->getBuffer(getBufferID(PLAYER));
	if (pPlayerBuffer != NULL)
	{
		gpGame->getSpriteManager()->createAndManageSprite(PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight());
	}

	GraphicsBuffer* pAIBuffer = gpGame->getGraphicsBufferManager()->getBuffer(getBufferID(AI));
	if (pAIBuffer != NULL)
	{
		gpGame->getSpriteManager()->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, pAIBuffer->getWidth(), pAIBuffer->getHeight());
	}

	GraphicsBuffer* wallBuffer = gpGame->getGraphicsBufferManager()->getBuffer(getBufferID(WALL));
	if (wallBuffer != NULL)
	{
		gpGame->getSpriteManager()->createAndManageSprite(WALL_SPRITE_ID, wallBuffer, 0, 0, wallBuffer->getWidth(), wallBuffer->getHeight());
	}

	GraphicsBuffer* circleBuffer = gpGame->getGraphicsBufferManager()->getBuffer(getBufferID(CIRCLE));
	if (circleBuffer != NULL)
	{
		gpGame->getSpriteManager()->createAndManageSprite(CIRCLE_SPRITE_ID, wallBuffer, 0, 0, circleBuffer->getWidth(), circleBuffer->getHeight());
	}
}

IDType UnitManager::getBufferID(UnitType _unitType)
{
	if (mBufferIDs.find(_unitType) == mBufferIDs.end())
		return INVALID_ID;

	return mBufferIDs[_unitType];
}


UnitManager::~UnitManager()
{
	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
			delete j->second;

		i->second->clear();
	}

	mMapList.clear();

	for (int i = 0; i < mTerrain.size(); ++i)
	{
		delete mTerrain[i];

		mTerrain[i] = NULL;
	}
}

std::map<int, KinematicUnit*>* UnitManager::getUnitMap(UnitType _type)
{
	try
	{
		return mMapList[_type];
	}
	catch (std::out_of_range)
	{
		return NULL;
	}
}


KinematicUnit* UnitManager::getUnit(int _ID, UnitType _type)
{
	if (_type == NONE)
	{
		for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
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
		for (auto i = mMapList[_type]->begin(); i != mMapList[_type]->end(); ++i)
		{
			if (i->second->getID() == _ID)
				return i->second;
		}
	}

	return NULL;
}


void UnitManager::update(float _dt)
{
	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			j->second->update(_dt);
		}
	}

	for (int i = 0; i < mTerrain.size(); ++i)
	{
		mTerrain[i]->update(_dt);
	}
}

void UnitManager::draw(GraphicsBuffer* _buffer)
{
	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			j->second->draw(_buffer);
		}
	}

	for (int i = 0; i < mTerrain.size(); ++i)
	{
		mTerrain[i]->draw(_buffer);
	}
}



KinematicUnit* UnitManager::addUnit(UnitType _type, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration)
{
	Sprite* unitSprite = getUnitSprite(_type);

	if (unitSprite == NULL)
	{
		return NULL;
	}

	if (mMapList.find(_type) == mMapList.end())
	{
		mMapList.insert(mapListPair(_type, new std::map<int, KinematicUnit*>));
	}
	else if (_type == PLAYER) // if player map exists return since there should only be one
		return NULL;

	int newID = mAvailableIDs.top();

	mAvailableIDs.pop();

	if (mAvailableIDs.empty())
		mAvailableIDs.push(newID + 1);

	KinematicUnit* newUnit;

	if (_type == BOID)
	{
		newUnit = new Boid(newID, unitSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration);
	}
	else
		newUnit = new KinematicUnit(newID, unitSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration);

	mMapList[_type]->insert(mapPair(newID, newUnit));

	return newUnit;
}

Sprite* UnitManager::getUnitSprite(UnitType _unitType)
{
	IDType spriteID;

	if (_unitType == PLAYER)
	{
		spriteID = PLAYER_ICON_SPRITE_ID;
	}
	else if (_unitType == WALL)
	{
		spriteID = WALL_SPRITE_ID;
	}
	else if (_unitType == CIRCLE)
	{
		spriteID = CIRCLE_SPRITE_ID;
	}
	else
	{
		spriteID = AI_ICON_SPRITE_ID;
	}

	return gpGame->getSpriteManager()->getSprite(spriteID);
}


bool UnitManager::removeUnit(int _ID)
{
	std::map<int, KinematicUnit*>::iterator mapIterator;

	for (auto unitMap = mMapList.begin(); unitMap != mMapList.end(); ++unitMap)
	{
		mapIterator = unitMap->second->find(_ID);

		if(mapIterator == unitMap->second->end())
			continue;
		else
		{
			//push unit's id into available id list so it can be used again
			mAvailableIDs.push(mapIterator->second->getID());

			delete mapIterator->second;
			mapIterator->second = NULL;

			unitMap->second->erase(mapIterator);

			//erases map if it is empty
			if (unitMap->second->size() == 0)
				mMapList.erase(unitMap);

			return true;
		}
	}

	return false;
}

//bool UnitManager::tagExists(int _ID)
//{
//	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
//	{
//		if (i->second->find(_ID) == i->second->end())
//			return true;
//	}
//
//	return false;
//}

void UnitManager::removeRandomUnit()
{
	if (mMapList.size() == 1)
		return;

	UnitType randMap;
	int randNum;

	do
	{
		srand(gpGame->getCurrentTime() + 1);

		//generate random number between 1 and the number of unit types. 0 is ommited so player unit is not deleted
		randNum = (rand() % NUM_TYPES) + 1;

		randMap = static_cast<UnitType>(randNum);
	} while (mMapList.find(randMap) == mMapList.end());

	randNum = rand() % mMapList.at(randMap)->size();

	int i = 0;
	KinematicUnit* toRemove = NULL;

	for (auto mapIterator = mMapList.at(randMap)->begin(); mapIterator != mMapList.at(randMap)->end(); ++mapIterator)
	{
		if (i == randNum)
		{
			toRemove = mapIterator->second;

			break;
		}

		++i;
	}

	if (toRemove == NULL)
	{
		std::cout << "Error removing random unit\n";

		return;
	}

	removeUnit(toRemove->getID());

	if (mMapList.size() == 1)
	{	
		gpGame->quit();
	}
}

Component* UnitManager::addComponent(ComponentType _type, KinematicUnit* _unit)
{
	Component* newComponent = NULL;

	switch (_type)
	{
	case WANDER_AND_FLEE:
	{
		newComponent = new WanderAndFleeComponent(_unit, 300.0f);

		_unit->addComponent(newComponent);
		break;
	}
	case WANDER_AND_SEEK:
	{
		newComponent = new WanderAndSeekComponent(_unit, 300.0f);

		_unit->addComponent(newComponent);
		break;
	}
	default:
		break;
	}

	return newComponent;
}

void UnitManager::spawnCircle(Vector2D _position)
{
	GraphicsBuffer* circleBuffer = gpGame->getGraphicsBufferManager()->getBuffer(getBufferID(CIRCLE));
	float radius = circleBuffer->getWidth() / 2;

	TerrainUnit* circle = new EllipseTerrain(getUnitSprite(CIRCLE), _position, radius);

	mTerrain.push_back(circle);
}

void UnitManager::generateBorderWall(int _width, int _height)
{
	GraphicsBuffer* wallBuffer = gpGame->getGraphicsBufferManager()->getBuffer(getBufferID(WALL));
	int wallWidth = wallBuffer->getWidth();// / 2;
	int wallHeight = wallBuffer->getHeight();// / 2;
	float currentWidth = 0;//wallWidth / 2;
	float currentHeight = 0;//wallHeight / 2;
	bool topOrBottom = true;
	TerrainUnit* newWall = NULL;

	while (currentHeight < _height)
	{
		newWall = new TerrainUnit(getUnitSprite(WALL), Vector2D(currentWidth, currentHeight));

		mTerrain.push_back(newWall);

		if (topOrBottom)
		{
			currentWidth += wallWidth;

			while (currentWidth < _width - wallWidth)
			{
				TerrainUnit* newWall = new TerrainUnit(getUnitSprite(WALL), Vector2D(currentWidth, currentHeight));

				mTerrain.push_back(newWall);

				currentWidth += wallWidth;
			}

			topOrBottom = false;
		}

		currentWidth = _width - wallWidth;

		newWall = new TerrainUnit(getUnitSprite(WALL), Vector2D(currentWidth, currentHeight));

		mTerrain.push_back(newWall);

		currentHeight += wallHeight;
		currentWidth = 0;

		if (currentHeight + wallHeight >= _height)
			topOrBottom = true;
	}
}
