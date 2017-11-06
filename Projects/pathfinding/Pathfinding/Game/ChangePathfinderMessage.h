#pragma once
#include "GameMessage.h"

enum PathfinderType;

class ChangePathfinderMessage : public GameMessage
{
public:
	ChangePathfinderMessage(PathfinderType _type);
	~ChangePathfinderMessage();

	void process();

private:
	PathfinderType mPathfinderType;
};