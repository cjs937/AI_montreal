#include "InputMessage.h"
#include "InputSystem.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "AddUnitMessage.h"
#include "RemoveRandUnitMessage.h"
#include "QuitGameMessage.h"
#include "UnitManager.h"

void InputMessage::process()
{
	switch (mKeyCode)
	{
	case ALLEGRO_KEY_A:
	{
		if (mInputType == KEY_DOWN)
		{
			GameMessage* newMessage = new AddUnitMessage(SEEKER);

			gpGame->getMessageManager()->addMessage(newMessage, 0);
		}
		break;
	}
	case ALLEGRO_KEY_S:
	{	
		if(mInputType == KEY_DOWN)
		{
			GameMessage* newMessage = new AddUnitMessage(ARRIVER);

			gpGame->getMessageManager()->addMessage(newMessage, 0);
		}
		break;
	}
	case ALLEGRO_KEY_D:
	{
		if (mInputType == KEY_DOWN)
		{
			GameMessage* newMessage = new RemoveRandUnitMessage();

			gpGame->getMessageManager()->addMessage(newMessage, 0);
		}
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
		GameMessage* newMessage = new QuitGameMessage();

		gpGame->getMessageManager()->addMessage(newMessage, 0);

		break;
	}
	default:
		break;
	}
};