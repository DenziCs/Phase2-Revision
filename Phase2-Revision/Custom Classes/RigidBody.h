#pragma once
#include "Particle.h"

class RigidBody : public Particle
{
public:
	RigidBody() : Particle() {}

	void applyForceAtPoint(Vector, Vector);
};