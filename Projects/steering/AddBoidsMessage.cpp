#include "AddBoidsMessage.h"
#include "AddUnitMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"
#include "Utility.h"
#include "InputSystem.h"

AddBoidsMessage::AddBoidsMessage(int _numBoids, Vector2D _offset):GameMessage(ADD_BOIDS), mNumBoids(_numBoids), mOffset(_offset)
{}

AddBoidsMessage::~AddBoidsMessage()
{}

void AddBoidsMessage::process()
{
	Vector2D currentBoidPos = gpGame->getInputSystem()->getMousePosition();

	for (int i = 0; i < mNumBoids; ++i)
	{
		gpGame->getMessageManager()->addMessage(new AddUnitMessage(BOID, currentBoidPos), 0);

		currentBoidPos += mOffset;
	}
}