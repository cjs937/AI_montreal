#pragma once
#include "Component.h"
#include "Game.h"
#include "KinematicUnit.h"
class Vector2D;

class WanderAndSeekComponent : public Component
{
public:
	WanderAndSeekComponent(KinematicUnit* _unit, float _radius);
	~WanderAndSeekComponent();

	void update(float _dt);

private:

	float mDetectionRadius;
	bool mSeeking;

	inline float getDetectionRadius() { return mDetectionRadius; };
	bool playerInRadius();
	float distance(Vector2D _vectorA, Vector2D _vectorB);
};