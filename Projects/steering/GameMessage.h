#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	INPUT_MESSAGE,
	ADD_UNIT,
	REMOVE_RAND_UNIT,
	ADD_BOIDS,
	SET_DEBUG_MODE,
	INC_DEBUG_VALUE,
	QUIT_GAME
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

