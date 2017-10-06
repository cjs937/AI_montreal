#pragma once
#include "Component.h"

class Vector2D;

class WanderAndFleeComponent : public Component
{
public:
	WanderAndFleeComponent(KinematicUnit* _unit, float _radius);
	~WanderAndFleeComponent();

	void update(float _dt);

private:

	float mDetectionRadius;
	bool mFleeing;

	inline float getDetectionRadius() { return mDetectionRadius; };
	bool playerInRadius();
	float distance(Vector2D _vectorA, Vector2D _vectorB);
};