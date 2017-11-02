#include "SetDebugModeMessage.h"
#include "DebugSystem.h"
#include "Game.h"

SetDebugModeMessage::SetDebugModeMessage(DebugMode _mode) :GameMessage(SET_DEBUG_MODE), mMode(_mode)
{}

SetDebugModeMessage::~SetDebugModeMessage()
{}

void SetDebugModeMessage::process()
{
	gpGame->getDebugSystem()->setCurrentMode(mMode);
}