#pragma once
#include "GameMessage.h"
#include "Game.h"

class QuitGameMessage : public GameMessage
{
public:

	QuitGameMessage() :GameMessage(QUIT_GAME) {};
	~QuitGameMessage() {};

private:

	void process() { gpGame->quit(); };
};