#include "Particle.h"

Particle::Particle() {
	netForce = Vector(0.0f, 0.0f);
}

Particle::Particle(
	bool lifespanIsOn,
	float _mass,
	float x,
	float y,
	float damp,
	float rest,

	float radius,
	sf::Color sColor
) {
	particleType = GenericParticle;
	sf::CircleShape* circle = new sf::CircleShape;
	psSprite = circle;
	netForce = Vector(0.0f, 0.0f);

	hasLifespan = lifespanIsOn;
	mass = _mass;
	psSprite->setPosition(Utils::toWindowPoint(Vector(x, y)));
	dampFactor = damp;
	restitution = rest;
	
	circle->setRadius(radius);
	circle->setOrigin(sf::Vector2f(radius, radius));
	circle->setFillColor(sColor);
}

void Particle::setLifespanMode(bool lifespanIsOn) {
	hasLifespan = lifespanIsOn;
}

void Particle::setMass(float _mass) {
	mass = _mass;
}

void Particle::setPosition(float x, float y) {
	psSprite->setPosition(Utils::toWindowPoint(Vector(x, y)));
}

void Particle::setVelocity(Vector v) {
	velocity = v;
}

void Particle::setLifespan(float life) {
	lifespan = life;
}

void Particle::setRestitution(float rest) {
	restitution = rest;
}

void Particle::setRadius(float radius) {
	sf::CircleShape* circle = (sf::CircleShape*)psSprite;
	circle->setRadius(radius);
	circle->setOrigin(sf::Vector2f(radius, radius));
}

void Particle::setColor(sf::Color sColor) {
	psSprite->setFillColor(sColor);
}

void Particle::setDampFactor(float damp) {
	dampFactor = damp;
}

float Particle::getMass() {
	return mass;
}

Vector Particle::getPosition() {
	return Utils::toPhysicsPoint(psSprite->getPosition());
}

Vector Particle::getVelocity() {
	return velocity;
}

Vector Particle::getAcceleration() {
	return acceleration;
}

float Particle::getRestitution() {
	return restitution;
}

float Particle::getRadius() {
	sf::CircleShape* circle = (sf::CircleShape*)psSprite;
	return circle->getRadius();
}

bool Particle::destroyed() {
	return isDestroyed;
}

float Particle::getMomentOfInertia() {
	return 0.4 * mass * getRadius() * getRadius();
}

void Particle::applyForce(Vector appForce) {
	netForce = netForce + appForce;
}

void Particle::resetForce() {
	netForce = Vector(0, 0);
	acceleration = Vector(0, 0);
	netTorque = 0;
}

void Particle::update(float deltaTime) {
	Vector displacement;
	acceleration = netForce * (1 / mass);

	displacement.x = (0.5 * acceleration.x * powf(deltaTime, 2)) + (velocity.x * deltaTime);
	displacement.y = (0.5 * acceleration.y * powf(deltaTime, 2)) + (velocity.y * deltaTime);
	psSprite->move(Utils::toWindowVector(displacement));

	float deltaRotation = angularVelocity * deltaTime;
	psSprite->rotate(Utils::inDegrees(deltaRotation));

	velocity.x += acceleration.x * deltaTime;
	velocity.x *= powf(dampFactor, deltaTime);
	velocity.y += acceleration.y * deltaTime;
	velocity.y *= powf(dampFactor, deltaTime);

	float mI = getMomentOfInertia();
	angularVelocity += -netTorque * deltaTime * (1.f / mI);
	angularVelocity *= powf(angularDampFactor, deltaTime);

	if (hasLifespan) {
		lifespan -= deltaTime;
		if (lifespan <= 0) isDestroyed = true;
	}

	resetForce();
}

void Particle::draw(sf::RenderWindow* pgWindow) {
	pgWindow->draw(*psSprite);
}