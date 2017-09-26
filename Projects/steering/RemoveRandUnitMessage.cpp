#include "RemoveRandUnitMessage.h"
#include "Game.h"
#include "UnitManager.h"

void RemoveRandUnitMessage::process()
{
	gpGame->getUnitManager()->removeRandomUnit();
}