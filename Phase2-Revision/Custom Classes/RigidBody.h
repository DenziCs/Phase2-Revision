#pragma once
#include "Particle.h"

class RigidBody : public Particle
{
public:
	RigidBody() : Particle() {}

	void setRotation(float);
	void setAngularDampFactor(float);
	
	float getRotation();

	void applyForceAtPoint(Vector, Vector);
};