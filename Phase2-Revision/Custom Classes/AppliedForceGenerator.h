#include"ForceGenerator.h"
#pragma once

class AppliedForceGenerator : public ForceGenerator
{
public:
	AppliedForceGenerator(Vector);
	void applyForce(Particle*);
private:
	Vector appliedForce;
};