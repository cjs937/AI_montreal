#include "BlendedSteering.h"
#include "Game.h"
#include "UnitManager.h"

BlendedSteering::BlendedSteering()
{}

BlendedSteering::~BlendedSteering()
{
	for (int i = 0; i < mBehaviors.size(); ++i)
	{
		delete mBehaviors[i];

		mBehaviors[i] = NULL;
	}

	mBehaviors.clear();
}

Steering* BlendedSteering::getSteering()
{
	Steering* steering = this;
	mLinear = Vector2D();
	mAngular = 0;

	float maxVelocity = gpGame->getUnitManager()->getMaxVelocity();
	float maxRotation = gpGame->getUnitManager()->getMaxRotation();

	for (int i = 0; i < mBehaviors.size(); ++i)//mBehaviors.begin(); i != mBehaviors.end(); ++i)
	{
		Steering* currentSteering = mBehaviors[i]->steeringBehavior->getSteering();
		float weight = mBehaviors[i]->weight;

		steering->setLinear(steering->getLinear() + currentSteering->getLinear() * weight);

		steering->setAngular(steering->getAngular() + currentSteering->getAngular() * weight);
	}

	steering->setLinear(Vector2D(min(steering->getLinear().getX(), maxVelocity), min(steering->getLinear().getY(), maxVelocity)));
	steering->setAngular(min(steering->getAngular(), maxRotation));

	return steering;
}

void BlendedSteering::addBehavior(Steering* _newBehavior, float _weight)
{
	BlendedSteeringBehavior* newBehavior = new BlendedSteeringBehavior(_newBehavior, _weight);

	mBehaviors.push_back(newBehavior);
}

bool BlendedSteering::removeBehavior(int _index)
{
	//if (_index < 0 || _index > mBehaviors.size())
	//	return false;

	//mBehaviors.erase(mBehaviors.at((size_t)_index));
	return false;
}

bool BlendedSteering::removeBehavior(Steering* _behavior)
{
	return false;
}