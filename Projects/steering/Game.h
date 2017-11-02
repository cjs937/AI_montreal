#pragma once

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <string>

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class Timer;
class InputSystem;
class UnitManager;
class UIManager;
class DebugSystem;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType WALL_SPRITE_ID = 3;
const IDType CIRCLE_SPRITE_ID = 4;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline InputSystem* getInputSystem() const { return mpInputSystem; };
	inline UnitManager* getUnitManager() const { return mpUnitManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline UIManager* getUIManager() const { return mpUIManager; };
	inline DebugSystem* getDebugSystem() const { return mpDebugSystem; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline void quit() { mShouldExit = true; };
	KinematicUnit* const getPlayerUnit();//player unit id should always be 0

private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	UnitManager* mpUnitManager;
	InputSystem* mpInputSystem;
	UIManager* mpUIManager;
	DebugSystem* mpDebugSystem;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;

	//should be somewhere else
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

