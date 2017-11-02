#pragma once
#include "DebugSystem.h"
#include "GameMessage.h"

class IncreaseDebugValueMessage : public GameMessage
{
public:
	IncreaseDebugValueMessage(float _increaseBy);
	~IncreaseDebugValueMessage();

	void process();

private:

	float mIncreaseBy;
};