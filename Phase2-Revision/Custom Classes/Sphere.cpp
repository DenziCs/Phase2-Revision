#include "Sphere.h"

Sphere::Sphere(
	bool lifespanIsOn,
	float _mass,
	float x,
	float y,
	float damp,
	float angleDamp,
	float rest,

	float radius,
	sf::Color sColor
) : RigidBody()
{
	particleType = CircleRigidBody;
	sf::CircleShape* circle = new sf::CircleShape();
	psSprite = circle;
	netForce = Vector(0.0f, 0.0f);

	hasLifespan = lifespanIsOn;
	mass = _mass;
	dampFactor = damp;
	angularDampFactor = angleDamp;
	restitution = rest;

	circle->setRadius(radius);
	circle->setOrigin(sf::Vector2f(radius, radius));
	psSprite->setPosition(Utils::toWindowPoint(Vector(x, y)));
	circle->setFillColor(sColor);
}