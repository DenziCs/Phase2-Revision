#include"ForceGenerator.h"
#pragma once

class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator() {};
	GravityForceGenerator(Vector);
	void setGravity(Vector);
	Vector getGravity();
	void applyForce(Particle*);
private:
	Vector gravAccel;
};