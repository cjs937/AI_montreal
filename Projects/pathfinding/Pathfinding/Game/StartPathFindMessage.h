#pragma once
#include "GameMessage.h"
#include "Vector2D.h"

class StartPathfindMessage : public GameMessage
{
public:
	StartPathfindMessage(Vector2D _pathTo);
	~StartPathfindMessage();

	void process();

	Vector2D getDestination() { return mPathTo; };

private:
	Vector2D mPathTo;
};