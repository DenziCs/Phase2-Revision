#include"ParticleLink.h"
#pragma once

class ParticleRod : public ParticleLink
{
public:
	ParticleRod(Particle*, Particle*);
	ContactResolver* getContact();
	
	float length;
	float restitution = 0;
};