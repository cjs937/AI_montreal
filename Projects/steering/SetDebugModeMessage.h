#pragma once
#include "GameMessage.h"

enum DebugMode;

class SetDebugModeMessage : public GameMessage
{
public:
	SetDebugModeMessage(DebugMode _mode);
	~SetDebugModeMessage();

	void process();

private:
	DebugMode mMode;

};