#include "RectangularPrism.h"

RectangularPrism::RectangularPrism(
	bool lifespanIsOn,
	float _mass,
	float x,
	float y,
	float damp,
	float rest,

	float width,
	float length,
	sf::Color sColor
) : RigidBody()
{
	particleType = RectangleRigidBody;
	sf::RectangleShape* rectangle = new sf::RectangleShape();
	psSprite = rectangle;

	hasLifespan = lifespanIsOn;
	mass = _mass;
	dampFactor = damp;
	restitution = rest;

	rectangle->setSize(sf::Vector2f(width, length));
	rectangle->setOrigin(sf::Vector2f(width / 2, length / 2));
	psSprite->setPosition(Utils::toWindowPoint(Vector(x, y)));
	rectangle->setFillColor(sColor);
}