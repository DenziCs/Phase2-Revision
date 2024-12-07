#include "ContactResolver.h"
#include<iostream>
using namespace std;

ContactResolver::ContactResolver(Particle* particleA, Particle* particleB, float newRest, float depth) {
	particles[0] = particleA;
	particles[1] = particleB;
	restitution = newRest;
	contactNormal = getContactNormal();
	overlapDepth = depth;
}

Vector ContactResolver::getContactNormal() {
	Vector norm = particles[0]->getPosition();
	if (particles[1]) {
		norm = norm - (particles[1]->getPosition());
	}
	return norm.getNormalized();
}

float ContactResolver::getSeparatingSpeed() {
	Vector velocity = particles[0]->getVelocity();
	if (particles[1]) {
		velocity = velocity - particles[1]->getVelocity();
	}
	return velocity.dotProduct(contactNormal);
}

void ContactResolver::resolveVelocity(float time) {
	float separatingSpeed = getSeparatingSpeed();

	if (separatingSpeed > 0) {
		return;
	}

	float newSeparatingSpeed = -restitution * separatingSpeed;
	float deltaSpeed = newSeparatingSpeed - separatingSpeed;
	float totalMass = (float)1 / particles[0]->getMass();

	if (particles[1]) {
		totalMass += (float)1 / particles[1]->getMass();
	}

	if (totalMass <= 0) {
		return;
	}

	float impulse_mag = deltaSpeed / totalMass;
	Vector impulse = contactNormal * impulse_mag;

	Vector V_a = impulse * ((float)1 / particles[0]->getMass());
	particles[0]->setVelocity(particles[0]->getVelocity() + V_a);

	if (particles[1]) {
		Vector V_b = impulse * (-(float)1 / particles[1]->getMass());
		particles[1]->setVelocity(particles[1]->getVelocity() + V_b);
	}
}

void ContactResolver::resolveInterpenetration(float time) {
	if (overlapDepth <= 0) {
		return;
	}

	float totalMass = (float)1 / particles[0]->getMass();
	if (particles[1]) {
		totalMass += (float)1 / particles[1]->getMass();
	}

	if (totalMass <= 0) {
		return;
	}

	float totalMoveByMass = overlapDepth / totalMass;
	Vector moveByMass = contactNormal * totalMoveByMass;

	Vector P_a = moveByMass * ((float)1 / particles[0]->getMass());
	particles[0]->setPosition(particles[0]->getPosition().x + P_a.x, particles[0]->getPosition().y + P_a.y);

	if (particles[1]) {
		Vector P_b = moveByMass * (-(float)1 / particles[1]->getMass());
		particles[1]->setPosition(particles[1]->getPosition().x + P_b.x, particles[1]->getPosition().y + P_b.y);
	}
	
	overlapDepth = 0;
}

void ContactResolver::resolve(float time) {
	resolveInterpenetration(time);
	resolveVelocity(time);
}