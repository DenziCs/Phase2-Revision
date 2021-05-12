#pragma once
#include "Vector.h"
#include "Particle.h"

class ContactResolver {
public:
	ContactResolver() {};
	ContactResolver(Particle*, Particle*, float, float);
	void resolve();
	float getSeparatingSpeed();

	Particle* particles[2];
	float restitution = 1.f;
	Vector contactNormal;
	float overlapDepth;
private:
	void resolveVelocity();
	void resolveInterpenetration();
	Vector getContactNormal();
};