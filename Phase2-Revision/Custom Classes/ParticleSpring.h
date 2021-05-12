#pragma once
#include "ParticleLink.h"
#include"ForceGenerator.h"
#include"ParticleSpringForceGenerator.h"

class ParticleSpring : public ParticleLink
{
public:
	ParticleSpring(Particle*, Particle*, float, float);
	ParticleSpringForceGenerator* forceGen;
};