#pragma once
#include "GameMessage.h"

enum UnitType;

enum InputType
{
	KEY_DOWN,
	KEY_HOLD,
	KEY_UP
};

class InputMessage : public GameMessage
{
public:

	InputMessage(InputType _type, int _keyCode) :GameMessage(INPUT_MESSAGE), mInputType(_type), mKeyCode(_keyCode) {};
	~InputMessage() {};

	InputType getType() { return mInputType; }
	int getKeyCode() { return mKeyCode; }

private:

	InputType mInputType;

	int mKeyCode;

	void process();
};
