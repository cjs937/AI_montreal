#include  "WanderAndSeekComponent.h"

WanderAndSeekComponent::WanderAndSeekComponent(KinematicUnit* _unit, float _radius) :Component(_unit)
{
	mDetectionRadius = _radius;
	mSeeking = false;
}

WanderAndSeekComponent::~WanderAndSeekComponent() {}

void WanderAndSeekComponent::update(float _dt)
{
	if (playerInRadius())
	{
		if (!mSeeking)
		{
			std::cout << "in there\n";
			mSeeking = true;
			mpCurrentUnit->dynamicSeek(gpGame->getPlayerUnit());
		}
	}
	else
	{
		if (mSeeking)
		{
			std::cout << "outta there\n";
			mSeeking = false;
			mpCurrentUnit->wander();
		}
	}
}

bool WanderAndSeekComponent::playerInRadius()
{
	if (distance(mpCurrentUnit->getPosition(), gpGame->getPlayerUnit()->getPosition()) <= mDetectionRadius)
	{
		return true;
	}

	return false;
}

float WanderAndSeekComponent::distance(Vector2D _vectorA, Vector2D _vectorB)
{
	float xSquared = (_vectorA.getX() - _vectorB.getX()) * (_vectorA.getX() - _vectorB.getX());
	float ySquared = (_vectorA.getY() - _vectorB.getY()) * (_vectorA.getY() - _vectorB.getY());

	return sqrt(xSquared + ySquared);
}