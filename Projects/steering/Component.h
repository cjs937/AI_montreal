#pragma once
#include "Trackable.h"

class KinematicUnit;

class Component : public Trackable
{
public:

	KinematicUnit* mpCurrentUnit;

	Component(KinematicUnit* _unit) :mpCurrentUnit(_unit) {};
	~Component(){};

	virtual void update(float _dt) = 0;
};