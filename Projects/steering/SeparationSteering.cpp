#include "SeparationSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"

SeparationSteering::SeparationSteering(KinematicUnit* _unit):mpCurrentUnit(_unit)
{}


SeparationSteering::~SeparationSteering()
{}

Steering* SeparationSteering::getSteering()
{
	Steering* newSteering = this;

	std::map<UnitType, std::map<int, KinematicUnit*>*>* unitMap = gpGame->getUnitManager()->getMapList();

	Vector2D direction;
	float distance;
	float separationStrength;
	float separationThreshold = gpGame->getUnitManager()->getSeparationThreshold();
	float separationDecay = gpGame->getUnitManager()->getSeparationDecay();
	float maxAcceleration = gpGame->getUnitManager()->getMaxVelocity();

	for (auto i = unitMap->begin(); i != unitMap->end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			KinematicUnit* currentUnit = j->second;

			direction = currentUnit->getPosition() - mpCurrentUnit->getPosition();

			distance = direction.getLength();

			if (distance < separationThreshold)
			{
				separationStrength = min(separationDecay / (distance * distance), maxAcceleration);

				direction.normalize();

				newSteering->setLinear(newSteering->getLinear() + Vector2D(direction.getX() * separationStrength, direction.getY() * separationStrength));
			}
		}
	}

	return newSteering;
}
