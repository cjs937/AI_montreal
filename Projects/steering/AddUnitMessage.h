#pragma once
#include "GameMessage.h"
#include "Vector2D.h"

enum UnitType;

class AddUnitMessage : public GameMessage
{
public:

	AddUnitMessage(UnitType _type, Vector2D _position) :GameMessage(ADD_UNIT),mUnitType(_type), mPosition(_position){};
	~AddUnitMessage() {};

	UnitType getType() { return mUnitType; }

private:

	UnitType mUnitType;
	Vector2D mPosition;

	void process();
};