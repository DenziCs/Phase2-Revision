#include "Particle.h"

Particle::Particle() {
	psSprite = new sf::CircleShape;
	netForce = Vector(0.0f, 0.0f);
}

Particle::Particle(
	float _mass,
	float x,
	float y,
	float life,
	float damp,

	float size,
	sf::Color sColor
) {
	psSprite = new sf::CircleShape;
	netForce = Vector(0.0f, 0.0f);

	mass = _mass;
	psSprite->setPosition(x, y);
	lifespan = life;
	dampFactor = damp;
	psSprite->setRadius(size);
	psSprite->setFillColor(sColor);
}

void Particle::setMass(float _mass) {
	mass = _mass;
}

void Particle::setPos(float x, float y) {
	psSprite->setPosition(x, y);
}

void Particle::setLifespan(float life) {
	lifespan = life;
}

void Particle::setSize(float size) {
	psSprite->setRadius(size);
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

Vector Particle::getVelocity() {
	return velocity;
}

Vector Particle::getAcceleration() {
	return acceleration;
}

bool Particle::destroyed() {
	return isDestroyed;
}

void Particle::applyForce(Vector appForce) {
	netForce = netForce + appForce;
}

void Particle::resetForce() {
	netForce = Vector(0, 0);
	acceleration = Vector(0, 0);
}

void Particle::update(float deltaTime) {
	Vector displacement;
	acceleration = netForce * (1 / mass);

	displacement.x = (0.5 * acceleration.x * powf(deltaTime, 2)) + (velocity.x * deltaTime);
	displacement.y = (0.5 * acceleration.y * powf(deltaTime, 2)) + (velocity.y * deltaTime);
	displacement = asWindowVector(displacement);
	psSprite->move(sf::Vector2f(displacement.x, displacement.y));

	velocity.x += acceleration.x * deltaTime;
	velocity.x *= powf(dampFactor, deltaTime);
	velocity.y += acceleration.y * deltaTime;
	velocity.y *= powf(dampFactor, deltaTime);

	lifespan -= deltaTime;
	if (lifespan <= 0) isDestroyed = true;

	resetForce();
}

void Particle::draw(sf::RenderWindow* pgWindow) {
	pgWindow->draw(*psSprite);
}

Vector Particle::asWindowVector(Vector cVector) {
	return Vector(cVector.x, -cVector.y);
}