#pragma once
#include "Steering.h"

class KinematicUnit;

class SeparationSteering : public Steering
{
public:
	SeparationSteering(KinematicUnit* _unit);
	
	~SeparationSteering();

	virtual Steering* getSteering();

private:

	KinematicUnit* mpCurrentUnit;
};