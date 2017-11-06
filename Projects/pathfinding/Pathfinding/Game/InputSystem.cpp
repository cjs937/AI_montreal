#include <sstream>

#include "InputSystem.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "InputMessage.h"

InputSystem::InputSystem()
{
	if (!al_install_keyboard())
	{
		printf("Keyboard not installed!\n");
	}

	for (int i = 1; i < ALLEGRO_KEY_MAX; ++i)
	{
		//allegro keycodes jump from 107 to 215 here so this takes that into account
		if (i == ALLEGRO_KEY_UNKNOWN + 1)
			i = ALLEGRO_KEY_MODIFIERS;

		mkeyStates.insert(std::pair<int, bool>(i, false));
	}

	mMouseDown = false;
}

void InputSystem::update()
{
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_MOUSE_STATE mouseState;

	al_get_keyboard_state(&keyState);

	for (int i = 1; i < ALLEGRO_KEY_MAX; ++i)
	{
		if (i == ALLEGRO_KEY_UNKNOWN + 1)
			i = ALLEGRO_KEY_MODIFIERS;

		if (al_key_down(&keyState, i))
		{
			if (!mkeyStates[i])
			{
				mkeyStates[i] = true;

				fireEvent(KEY_DOWN, i);
			}
			else
			{
				fireEvent(KEY_HOLD, i);
			}
		}
		else if (mkeyStates[i])
		{
			mkeyStates[i] = false;

			fireEvent(KEY_UP, i);
		}
	}

	al_get_mouse_state(&mouseState);

	if(al_mouse_button_down(&mouseState, 1))
	{
		if (!mMouseDown)
		{
			mMouseDown = true;

			fireEvent(KEY_DOWN, MOUSE_BUTTON_ID);
		}
		else
		{
			fireEvent(KEY_HOLD, MOUSE_BUTTON_ID);
		}
	}
	else if (mMouseDown)
	{
		mMouseDown = false;

		fireEvent(KEY_UP, MOUSE_BUTTON_ID);
	}
}

Vector2D InputSystem::getMousePosition()
{
	ALLEGRO_MOUSE_STATE mouseState;

	al_get_mouse_state(&mouseState);

	return Vector2D(mouseState.x, mouseState.y);
}

void InputSystem::fireEvent(InputType _type, int _keyCode)
{
	//Game::getEventSystem()->dispatchEvent(_type);

	InputMessage* msg = new InputMessage(_type, _keyCode);

	static_cast<GameApp*>(gpGame)->getMessageManager()->addMessage(msg, 0.0f);
}