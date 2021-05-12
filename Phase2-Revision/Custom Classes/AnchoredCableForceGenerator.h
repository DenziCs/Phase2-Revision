#pragma once
#include "ForceGenerator.h"

class AnchoredCableForceGenerator :
    public ForceGenerator
{
public:
    AnchoredCableForceGenerator(Vector, float, float);
	void applyForce(Particle*);
private:
	Vector anchorPoint;
	float springConstant;
	float restLength;
};