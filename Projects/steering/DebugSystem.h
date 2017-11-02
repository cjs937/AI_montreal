#pragma once
#include "Trackable.h"
#include <map>

enum DebugMode
{
	NO_DEBUG = -1,
	VELOCITY_CONTROL,
	REACTION_RADIUS,
	ANGULAR_VELOCITY,
	COHESION,
	SEPARATION,
	ALIGNMENT,
	NUM_MODES
};

class UIText;

struct DebugTextObject
{
	DebugMode mode;
	bool isActive;
	UIText* text;

	//DebugTextObject(DebugMode _mode, std::string _sampleText, )
};

class DebugSystem : public Trackable
{
public:

	DebugSystem();
	~DebugSystem();
	 
	//inline UIText* getDebugText() { return mUIText; };
	inline DebugMode getCurrentMode() { return mCurrentMode; };
	inline bool isActive() { return mIsActive; };
	inline void setCurrentMode(DebugMode _mode) { mCurrentMode = _mode; };

	void update(float _dt);
	void changeDebugText(std::string _newText);
	void toggleActivation();

private:
	DebugMode mCurrentMode;
	bool mIsActive;
	std::map<DebugMode, UIText*> mDebugText;
	int mCurrentValue;
	int mNumValues;
	UIText* mUIText;

	void DebugVelocityControl();
	void DebugReactionRadius();
	void DebugAngularVelocity();
	void DebugCohesion();
	void DebugSeparation();
	void DebugAlignment();
};