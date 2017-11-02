#include "InputMessage.h"
#include "InputSystem.h"
#include "Game.h"
#include "GameMessageManager.h"
#include "UnitManager.h"
#include "MessageIncludes.h"
#include "DebugSystem.h"

void InputMessage::process()
{
	GameMessage* newMessage = NULL;
	Vector2D playerPosition = gpGame->getPlayerUnit()->getPosition();

	switch (mKeyCode)
	{
	case ALLEGRO_KEY_I:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new AddBoidsMessage(5, Vector2D(20, 0));
		}
		break;
	}
	case ALLEGRO_KEY_C:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new SetDebugModeMessage(COHESION);
		}
		break; 
	}
	case ALLEGRO_KEY_S:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new SetDebugModeMessage(SEPARATION);
		}
		break;
	}
	case ALLEGRO_KEY_A:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new SetDebugModeMessage(ALIGNMENT);
		}
		break;
	}
	case ALLEGRO_KEY_PAD_PLUS:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new IncreaseDebugValueMessage(1.0f);
		}
		break;
	}
	case ALLEGRO_KEY_MINUS:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new IncreaseDebugValueMessage(-1.0f);
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



//case ALLEGRO_KEY_A:
//{
//	if (mInputType == KEY_DOWN)
//	{
//		newMessage = new AddUnitMessage(SEEKER, Vector2D(playerPosition.getX() + 200, playerPosition.getY() + 200));
//	}
//	break;
//}
//case ALLEGRO_KEY_S:
//{	
//	if(mInputType == KEY_DOWN)
//	{
//		//newMessage = new AddUnitMessage(ARRIVER);
//		newMessage = new AddUnitMessage(WANDER_SEEK, Vector2D(playerPosition.getX() + 200, playerPosition.getY() + 200));
//	}
//	break;
//}
//case ALLEGRO_KEY_D:
//{
//	if (mInputType == KEY_DOWN)
//	{
//		newMessage = new RemoveRandUnitMessage();
//	}
//	break;
//}
//case ALLEGRO_KEY_F:
//{
//	if (mInputType == KEY_DOWN)
//	{
//		newMessage = new AddUnitMessage(WANDER_FLEE, Vector2D(playerPosition.getX() + 100, playerPosition.getY() + 100));
//	}
//	break;	
//}
//case ALLEGRO_KEY_G:
//{
//	if (mInputType == KEY_DOWN)
//	{
//		newMessage = new AddUnitMessage(WANDERER, Vector2D(playerPosition.getX() + 200, playerPosition.getY() + 200));
//	}
//	break;
//}