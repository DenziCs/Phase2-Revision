#pragma once
#include "ParticleAnchor.h"
#include"AnchoredCableForceGenerator.h"
#include"ContactResolver.h"

class AnchoredCable : public ParticleAnchor
{
public:
	AnchoredCable(Vector, Particle*, float, float);
	ContactResolver* getContact();
private:
	float length;
	float restitution = 0;
};