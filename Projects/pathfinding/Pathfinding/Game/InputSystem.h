#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <map>
#include <Trackable.h>
#include <Vector2D.h>
#include "allegro5\allegro.h"

const int MOUSE_BUTTON_ID = 300;

enum InputType;

class InputSystem : public Trackable
{
private:

	//int is the keycode, bool is wether it is pressed
	std::map<int, bool> mkeyStates;
	bool mMouseDown;

	void fireEvent(InputType _type, int _keyCode);


public:

	InputSystem();

	void update();
	static Vector2D getMousePosition();

};

#endif