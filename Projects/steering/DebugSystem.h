#pragma once
#include "Trackable.h"

enum DebugMode
{
	NO_DEBUG = -1,
	VELOCITY_CONTROL,
	REACTION_RADIUS,
	ANGULAR_VELOCITY,
	NUM_MODES
};

class UIText;

class DebugSystem : public Trackable
{
public:

	DebugSystem();
	~DebugSystem();

	inline UIText* getDebugText() { return mUIText; };
	inline DebugMode getCurrentMode() { return mCurrentMode; };
	inline bool isActive() { return mIsActive; };
	inline void setCurrentMode(DebugMode _mode) { mCurrentMode = _mode; };

	void update(float _dt);
	void changeDebugText(std::string _newText);
	void toggleActivation();

private:
	DebugMode mCurrentMode;
	bool mIsActive;
	UIText* mUIText;
};