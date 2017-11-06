#pragma once

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	PATH_TO_MESSAGE = 1,
	START_PATHFIND,
	TOGGLE_PATHFIND_ALGORITHM,
	CHANGE_TO_DIJKSTRA,
	CHANGE_TO_ASTAR,
	INPUT_MESSAGE,
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


