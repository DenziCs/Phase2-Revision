#include "ParticleSpringForceGenerator.h"

ParticleSpringForceGenerator::ParticleSpringForceGenerator(Particle* _partner, float _springConstant, float _restLength) {
	partner = _partner;
	springConstant = _springConstant;
	restLength = _restLength;
}

void ParticleSpringForceGenerator::applyForce(Particle* particle) {
	Vector position1 = particle->getPosition();
	Vector position2 = partner->getPosition();
	Vector force = position1 - position2;
	float mag = force.getMagnitude();

	float springForce = -springConstant * abs(mag - restLength);
	force = force.getNormalized();
	force = force * springForce;

	particle->applyForce(force);
}