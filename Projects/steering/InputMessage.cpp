#include "InputMessage.h"
#include "InputSystem.h"
#include "Game.h"
#include "UnitManager.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitManager.h"

void InputMessage::process()
{
	switch (mKeyCode)
	{
	case ALLEGRO_KEY_A:
	{
		if (mInputType == KEY_DOWN)
			addUnitByType(SEEKER);
		break;
	}
	case ALLEGRO_KEY_S:
	{	
		if (mInputType == KEY_DOWN)
			addUnitByType(ARRIVER);
		break;
	}
	case ALLEGRO_KEY_D:
	{
		if (mInputType == KEY_DOWN)
			deleteRandomUnit();
		break;
	}
	case MOUSE_BUTTON_ID:
	{
		if (mInputType == KEY_DOWN)
		{
			GameMessage* newMessage = new PlayerMoveToMessage(gpGame->getInputSystem()->getMousePosition());

			gpGame->getMessageManager()->addMessage(newMessage, 0);
		}

		break;
	}
	case ALLEGRO_KEY_ESCAPE:
	{
		gpGame->quit();

		break;
	}
	default:
		break;
	}
};

void InputMessage::addUnitByType(UnitType _type)
{
	Vector2D position = Vector2D();//new Vector2D( _type == SEEKER ? gpGame->getPlayerUnit()->getPosition().getX + 200.0f
	Vector2D velocity = Vector2D();
	if (_type == SEEKER)
		position.setX(gpGame->getPlayerUnit()->getPosition().getX() + 200.0f);
	else if(_type == ARRIVER)
		position.setX(gpGame->getPlayerUnit()->getPosition().getX() + 100.0f);

	KinematicUnit* newUnit = gpGame->getUnitManager()->addUnit(_type, position, 1.0f, velocity, 0.0, 200.0f, 15.0f);

	if (_type == SEEKER)
		newUnit->dynamicSeek(gpGame->getPlayerUnit());
	else if (_type == ARRIVER)
		newUnit->dynamicArrive(gpGame->getPlayerUnit());
}

void InputMessage::deleteRandomUnit()
{
	gpGame->getUnitManager()->removeRandomUnit();
}