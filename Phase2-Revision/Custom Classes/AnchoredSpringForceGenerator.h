#pragma once
#include "ForceGenerator.h"
#include<math.h>

class AnchoredSpringForceGenerator : public ForceGenerator
{
public:
	AnchoredSpringForceGenerator(Vector, float, float);
	void applyForce(Particle*);
private:
	Vector anchorPoint;
	float springConstant;
	float restLength;
};