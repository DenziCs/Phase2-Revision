#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector _position, float _springConstant, float _restLength) {
	anchorPoint = _position;
	springConstant = _springConstant;
	restLength = _restLength;
}

void AnchoredSpringForceGenerator::applyForce(Particle* particle) {
	Vector position = particle->getPosition();
	Vector force = position - anchorPoint;
	float mag = force.getMagnitude();

	float springForce = -springConstant * abs(mag - restLength);
	force = force.getNormalized();
	force = force * springForce;

	particle->applyForce(force);
}