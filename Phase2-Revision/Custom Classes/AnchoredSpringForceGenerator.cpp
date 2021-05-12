#include "AnchoredSpringForceGenerator.h"
#include<iostream>
using namespace std;

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector _position, float _springConstant, float _restLength) {
	anchorPoint = _position;
	springConstant = _springConstant;
	restLength = _restLength;
}

void AnchoredSpringForceGenerator::applyForce(Particle* particle) {
	sf::Vector2f pos = particle->psSprite->getPosition();
	Vector position(pos.x, pos.y);
	Vector force = anchorPoint - position;
	float mag = force.getMagnitude();

	float springForce = -springConstant * abs(mag - restLength);
	force = force.getNormalized();
	cout << force.x << " " << force.y << endl;
	force = force * springForce;
	cout << force.x << " " << force.y << endl;

	particle->applyForce(force);
}