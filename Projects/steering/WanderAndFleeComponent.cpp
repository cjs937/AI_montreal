#include "WanderAndFleeComponent.h"
#include "Game.h"
#include "KinematicUnit.h"

WanderAndFleeComponent::WanderAndFleeComponent(KinematicUnit* _unit, float _radius) :Component(_unit)
{
	mDetectionRadius = _radius;
	mFleeing = false;
}

WanderAndFleeComponent::~WanderAndFleeComponent() {}

void WanderAndFleeComponent::update(float _dt)
{
	if (playerInRadius())
	{
		if (!mFleeing)
		{
			std::cout << "in there\n";
			mFleeing = true;
			mpCurrentUnit->dynamicFlee(gpGame->getPlayerUnit());
		}
	}
	else
	{
		if (mFleeing)
		{
			std::cout << "outta there\n";
			mFleeing = false;
			mpCurrentUnit->wander();
		}
	}
}

bool WanderAndFleeComponent::playerInRadius()
{
	if (distance(mpCurrentUnit->getPosition(), gpGame->getPlayerUnit()->getPosition()) <= mDetectionRadius)
	{
		return true;
	}

	return false;
}

float WanderAndFleeComponent::distance(Vector2D _vectorA, Vector2D _vectorB)
{
	float xSquared = (_vectorA.getX() - _vectorB.getX()) * (_vectorA.getX() - _vectorB.getX());
	float ySquared = (_vectorA.getY() - _vectorB.getY()) * (_vectorA.getY() - _vectorB.getY());

	return sqrt(xSquared + ySquared);
}