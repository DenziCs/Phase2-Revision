#include "RigidBody.h"

void RigidBody::applyForceAtPoint(Vector point, Vector force) {
	netForce = netForce + force;
	netTorque = point.crossProduct(force);
}

void RigidBody::setRotation(float theta) {
	psSprite->setRotation(Utils::inDegrees(-theta));
}

void RigidBody::setAngularDampFactor(float damp) {
	angularDampFactor = damp;
}

float RigidBody::getRotation() {
	return -Utils::inRadians(psSprite->getRotation());
}