#include "AddUnitMessage.h"
#include "UnitManager.h"
#include "Game.h"
#include "Component.h"

void AddUnitMessage::process()
{
	Vector2D velocity = Vector2D();

	KinematicUnit* newUnit = gpGame->getUnitManager()->addUnit(mUnitType, mPosition, 1.0f, velocity, 0.0, gpGame->getUnitManager()->getMaxVelocity());

	if (mUnitType == SEEKER)
		newUnit->seek(gpGame->getPlayerUnit()->getPosition());
	else if (mUnitType == ARRIVER)
		newUnit->arrive(gpGame->getPlayerUnit()->getPosition());
	else if (mUnitType == WANDERER)
		newUnit->wander();
	else if (mUnitType == WANDER_FLEE)
	{
		newUnit->wander();

		gpGame->getUnitManager()->addComponent(WANDER_AND_FLEE, newUnit);
	}
	else if (mUnitType == WANDER_SEEK)
	{
		newUnit->wander();

		gpGame->getUnitManager()->addComponent(WANDER_AND_SEEK, newUnit);
	}
}
