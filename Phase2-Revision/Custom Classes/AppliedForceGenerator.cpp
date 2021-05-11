#include "AppliedForceGenerator.h"

AppliedForceGenerator::AppliedForceGenerator(Vector force) {
	appliedForce = force;
}

void AppliedForceGenerator::applyForce(Particle* particle) {
	particle->applyForce(appliedForce);
}