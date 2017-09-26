#pragma once
#include "GameMessage.h"

class RemoveRandUnitMessage : public GameMessage
{
public:

	RemoveRandUnitMessage() :GameMessage(REMOVE_RAND_UNIT) {};
	~RemoveRandUnitMessage() {};

private:

	void process();
};