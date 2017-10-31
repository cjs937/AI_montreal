#pragma once
#include "Steering.h"

class KinematicUnit;

class CohesionSteering : public Steering
{
public:

	CohesionSteering(KinematicUnit* _unit);
	~CohesionSteering();

	Steering* getSteering() override;

private:

	KinematicUnit* mpUnit;
};