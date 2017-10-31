#include "Boid.h"
#include "BlendedSteering.h"
#include "BoidAlignSteering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "KinematicWanderSteering.h"

Boid::Boid(int _ID, Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration)
	:KinematicUnit(_ID, pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration)

{
	BlendedSteering* steering = new BlendedSteering();

	steering->addBehavior(new BoidAlignSteering(this));
	steering->addBehavior(new CohesionSteering(this));
	steering->addBehavior(new SeparationSteering(this));
	steering->addBehavior(new KinematicWanderSteering(this), 0.75f);

	KinematicUnit::setSteering(steering);
}

Boid::~Boid()
{}