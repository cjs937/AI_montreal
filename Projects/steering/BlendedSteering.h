#pragma once
#include "Steering.h"
#include <vector>

struct BlendedSteeringBehavior
{
public:
	BlendedSteeringBehavior(Steering* _steeringBehavior, float _weight) : steeringBehavior(_steeringBehavior), weight(_weight)
	{}

	~BlendedSteeringBehavior() {};

	Steering* steeringBehavior;
	float weight;

};

class BlendedSteering : Steering
{
private:
	std::vector<BlendedSteeringBehavior*> mBehaviors;

public:

	BlendedSteering();
	~BlendedSteering();

	Steering* getSteering() override;
	std::vector<BlendedSteeringBehavior*> getBehaviors() { return mBehaviors; };

	void addBehavior(Steering* _newBehavior, float _weight = 1);
	bool removeBehavior(int _index);
	bool removeBehavior(Steering* _behavior);
};