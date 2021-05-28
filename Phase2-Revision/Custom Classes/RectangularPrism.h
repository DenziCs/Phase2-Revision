#pragma once
#include "RigidBody.h"

class RectangularPrism : public RigidBody
{
public:
	RectangularPrism(
		bool lifespanIsOn,
		float _mass,
		float x,
		float y,
		float damp,
		float rest,

		float width,
		float length,
		sf::Color sColor
	);
};