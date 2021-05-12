#include "AnchoredCableForceGenerator.h"

AnchoredCableForceGenerator::AnchoredCableForceGenerator(
	Vector position,
	float _springConstant,
	float _restLength
) {
	anchorPoint = position;
	springConstant = _springConstant;
	restLength = _restLength;
}

void AnchoredCableForceGenerator::applyForce(Particle* particle) {
	Vector position = particle->getPosition();
	Vector force = anchorPoint - position;
	float mag = force.getMagnitude();
	if (mag > restLength) return;

	float springForce = -springConstant * abs(mag - restLength);
	force = force.getNormalized();
	force = force * springForce;

	particle->applyForce(force);
}