#include "AnchoredSpring.h"

AnchoredSpring::AnchoredSpring(
	Vector position,
	Particle* _particle,
	float springConstant,
	float restLength
) : ParticleAnchor(position, _particle)
{
	this->forceGen = new AnchoredSpringForceGenerator(position, springConstant, restLength);
}