#pragma once
#include "GameMessage.h"
#include "GameApp.h"

class QuitGameMessage : public GameMessage
{
public:

	QuitGameMessage() :GameMessage(QUIT_GAME) {};
	~QuitGameMessage() {};

private:

	void process() { static_cast<GameApp*>(gpGame)->quit(); };
};