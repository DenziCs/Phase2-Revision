#pragma once
#include "ParticleAnchor.h"
#include"ContactResolver.h"

class AnchoredRod : public ParticleAnchor
{
public:
	AnchoredRod(Vector, Particle*);
	ContactResolver* getContact();
private:
	float length;
	float restitution = 0;
};