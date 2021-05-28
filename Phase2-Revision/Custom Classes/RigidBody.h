#pragma once
#include "Particle.h"

class RigidBody : public Particle
{
public:
	RigidBody() : Particle() {}

	void setRotation(float theta);
	float getRotation(float theta);
	void applyForceAtPoint(Vector, Vector);
};