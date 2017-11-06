#include "InputMessage.h"
#include "InputSystem.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "StartPathFindMessage.h"
#include "QuitGameMessage.h"
#include "ChangePathfinderMessage.h"
#include "Pathfinder.h"

void InputMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	GameMessage* newMessage = NULL;

	switch (mKeyCode)
	{
	case ALLEGRO_KEY_D:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new ChangePathfinderMessage(DIJKSTRA);
		}
		
		break;
	}
	case ALLEGRO_KEY_A:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new ChangePathfinderMessage(ASTAR);
		}

		break;
	}
	case MOUSE_BUTTON_ID:
	{
		if (mInputType == KEY_DOWN)
		{
			newMessage = new StartPathfindMessage(InputSystem::getMousePosition());
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
		pGame->getMessageManager()->addMessage(newMessage, 0);
};