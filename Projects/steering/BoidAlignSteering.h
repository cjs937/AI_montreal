#pragma once
#include "Steering.h"

class KinematicUnit;

class BoidAlignSteering : public Steering
{
public:

	BoidAlignSteering(KinematicUnit* _unit);
	~BoidAlignSteering();

	Steering* getSteering() override;

private:

	KinematicUnit* mpUnit;
};