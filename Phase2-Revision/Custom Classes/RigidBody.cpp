#include "RigidBody.h"

void RigidBody::applyForceAtPoint(Vector point, Vector force) {
	netForce = netForce + force;
	netTorque = point.crossProduct(force);
}