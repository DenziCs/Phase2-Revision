#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(Vector a) {
	gravAccel = a;
}

void GravityForceGenerator::setGravity(Vector a) {
	gravAccel = a;
}

Vector GravityForceGenerator::getGravity() {
	return gravAccel;
}

void GravityForceGenerator::applyForce(Particle* particle) {
	Vector gravForce;
	gravForce = gravAccel * particle->getMass();
	particle->applyForce(gravForce);
}