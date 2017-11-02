#include "IncreaseDebugValueMessage.h"
#include "Game.h"
#include "DebugSystem.h"

IncreaseDebugValueMessage::IncreaseDebugValueMessage(float _increaseBy): GameMessage(INC_DEBUG_VALUE), mIncreaseBy(_increaseBy)
{}

IncreaseDebugValueMessage::~IncreaseDebugValueMessage()
{}

void IncreaseDebugValueMessage::process()
{
	gpGame->getDebugSystem()->increaseCurrentValue(mIncreaseBy);
}