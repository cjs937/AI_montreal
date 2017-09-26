#pragma once
#include "GameMessage.h"

enum UnitType;

class AddUnitMessage : public GameMessage
{
public:

	AddUnitMessage(UnitType _type) :GameMessage(ADD_UNIT),mUnitType(_type){};
	~AddUnitMessage() {};

	AddUnitMessage getType() { return mUnitType; }

private:

	UnitType mUnitType;

	void process();
};