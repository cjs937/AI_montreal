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
	GameMessage* newMessage = NULL;

	switch (mKeyCode)
	{
	case ALLEGRO_KEY_A:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new AddUnitMessage(SEEKER);
		}
		break;
	}
	case ALLEGRO_KEY_S:
	{	
		if(mInputType == KEY_DOWN)
		{
			newMessage = new AddUnitMessage(ARRIVER);
		}
		break;
	}
	case ALLEGRO_KEY_D:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new RemoveRandUnitMessage();
		}
		break;
	}
	case ALLEGRO_KEY_G:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new AddUnitMessage(WANDERER);
		}
		break;
	}
	case MOUSE_BUTTON_ID:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new PlayerMoveToMessage(gpGame->getInputSystem()->getMousePosition());
		}

		break;
	}
	case ALLEGRO_KEY_ESCAPE:
	{
		newMessage = new QuitGameMessage();

		break;
	}
	default:
		break;
	}

	if(newMessage != NULL)
		gpGame->getMessageManager()->addMessage(newMessage, 0);
};