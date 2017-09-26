#include "AddUnitMessage.h"
#include "UnitManager.h"
#include "Game.h"

void AddUnitMessage::process()
{
	Vector2D position = Vector2D();//new Vector2D( _type == SEEKER ? gpGame->getPlayerUnit()->getPosition().getX + 200.0f
	Vector2D velocity = Vector2D();

	if (mUnitType == SEEKER)
		position.setX(gpGame->getPlayerUnit()->getPosition().getX() + 200.0f);
	else if (mUnitType == ARRIVER)
		position.setX(gpGame->getPlayerUnit()->getPosition().getX() + 100.0f);

	KinematicUnit* newUnit = gpGame->getUnitManager()->addUnit(mUnitType, position, 1.0f, velocity, 0.0, 200.0f, 15.0f);

	if (mUnitType == SEEKER)
		newUnit->dynamicSeek(gpGame->getPlayerUnit());
	else if (mUnitType == ARRIVER)
		newUnit->dynamicArrive(gpGame->getPlayerUnit());
}
