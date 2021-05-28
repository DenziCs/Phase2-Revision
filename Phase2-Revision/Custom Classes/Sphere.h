#pragma once
#include "RigidBody.h"

class Sphere : public RigidBody
{
public:
	Sphere(
		bool lifespanIsOn,
		float _mass,
		float x,
		float y,
		float damp,
		float angleDamp,
		float rest,

		float radius,
		sf::Color sColor
	);
};