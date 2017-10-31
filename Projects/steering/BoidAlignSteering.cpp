#include "BoidAlignSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "KinematicUnit.h"
#include "Utility.h"

BoidAlignSteering::BoidAlignSteering(KinematicUnit* _unit) : mpUnit(_unit)
{}

BoidAlignSteering::~BoidAlignSteering()
{}

Steering* BoidAlignSteering::getSteering()
{
	Steering* newSteering = this;
	std::map<UnitType, std::map<int, KinematicUnit*>*>* unitMap = gpGame->getUnitManager()->getMapList();
	float neighborRadius = gpGame->getUnitManager()->getNeighborRadius();
	float numNeighbors = 0;
	Vector2D newLinear = Vector2D();

	for (auto i = unitMap->begin(); i != unitMap->end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			KinematicUnit* currentUnit = j->second;

			if (mpUnit == currentUnit || neighborRadius < Utility::vectorDistance(currentUnit->getPosition(), mpUnit->getPosition()))
				continue;

			Vector2D unitVel = currentUnit->getVelocity();

			newLinear += unitVel;
			//(Vector2D(newSteering->getLinear().getX() + unitVel.getX(), newSteering->getLinear.getY() + unitVel.getY()));

			++numNeighbors;
		}
	}

	if (numNeighbors == 0)
		return newSteering;

	newLinear /= numNeighbors;

	newLinear.normalize();

	newSteering->setLinear(newLinear);

	return newSteering;
}