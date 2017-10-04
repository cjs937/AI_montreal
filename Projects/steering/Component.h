#pragma once
#include "Trackable.h"

class KinematicUnit;

class Component : public Trackable
{
public:

	KinematicUnit* mCurrentUnit;

	Component(KinematicUnit* _unit) :mCurrentUnit(_unit) {};
	
	virtual void update(float _dt) = 0;

private:

	~Component() 
	{ };
};