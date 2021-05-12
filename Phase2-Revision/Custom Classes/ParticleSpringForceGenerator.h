#pragma once
#include "ForceGenerator.h"

class ParticleSpringForceGenerator : public ForceGenerator
{
public:
	ParticleSpringForceGenerator(Particle*, float, float);
	void applyForce(Particle*);

private:
	Particle* partner;
	float springConstant;
	float restLength;
};