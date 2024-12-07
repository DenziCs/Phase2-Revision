#include"ParticleAnchor.h"
#include"AnchoredSpringForceGenerator.h"
#pragma once

class AnchoredSpring : public ParticleAnchor
{
public:
	AnchoredSpring(Vector, Particle*, float, float);
};