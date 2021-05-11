#include"Particle.h"
#pragma once

class ForceGenerator
{
public:
	virtual void applyForce(Particle*) = 0;
};