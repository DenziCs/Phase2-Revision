#include "RectangularPrism.h"

RectangularPrism::RectangularPrism(
	bool lifespanIsOn,
	float _mass,
	float x,
	float y,
	float damp,
	float angleDamp,
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
	angularDampFactor = angleDamp;
	restitution = rest;

	rectangle->setSize(sf::Vector2f(width, length));
	rectangle->setOrigin(sf::Vector2f(width / 2, length / 2));
	psSprite->setPosition(Utils::toWindowPoint(Vector(x, y)));
	rectangle->setFillColor(sColor);

	Vector ul = Vector(-width / 2, length / 2);
	Vector ll = Vector(-width / 2, -length / 2);
	Vector ur = Vector(width / 2, length / 2);
	Vector lr = Vector(width / 2, -length / 2);

	points[0] = Utils::rotatePoint(ul, this->getRotation()) + this->getPosition();
	points[1] = Utils::rotatePoint(ur, this->getRotation()) + this->getPosition();
	points[2] = Utils::rotatePoint(lr, this->getRotation()) + this->getPosition();
	points[3] = Utils::rotatePoint(ll, this->getRotation()) + this->getPosition();
}

float RectangularPrism::getWidth() {
	sf::RectangleShape* rect = (sf::RectangleShape*)psSprite;
	return rect->getSize().x;
}

float RectangularPrism::getLength() {
	sf::RectangleShape* rect = (sf::RectangleShape*)psSprite;
	return rect->getSize().y;
}

float RectangularPrism::getRest() {
	return restitution;
}