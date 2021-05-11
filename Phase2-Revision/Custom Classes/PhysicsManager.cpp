#include "PhysicsManager.h"

PhysicsManager::PhysicsManager() {
	srand(time(0));
}

PhysicsManager::~PhysicsManager() {
	particleList.clear();
}

void PhysicsManager::setGravity(float gravMagnitude, Vector gravDirect) {
	gravity.x = gravDirect.x * gravMagnitude;
	gravity.y = gravDirect.y * gravMagnitude;

	gravityGenerator = new GravityForceGenerator(gravDirect * gravMagnitude);
}

void PhysicsManager::setLimit(int limit) {
	particleLimit = limit;
}

void PhysicsManager::setOrigin(Vector origin) {
	worldOrigin.x = origin.x;
	worldOrigin.y = origin.y;
}

Vector PhysicsManager::getGravity() {
	return gravity;
}

int PhysicsManager::getLimit() {
	return particleLimit;
}

Vector PhysicsManager::getOrigin() {
	return worldOrigin;
}

Vector PhysicsManager::asWindowPoint(Vector cVector) {
	return Vector(worldOrigin.x + cVector.x, worldOrigin.y - cVector.y);
}

void PhysicsManager::addParticle(Particle* particle) {
	if (particleList.size() < particleLimit) {
		particleList.push_back(particle);
		addForce(particle, gravityGenerator);
	}
}

void PhysicsManager::addAnchorPoint(Particle* particle) {
	if (particleList.size() < particleLimit) particleList.push_back(particle);
}

void PhysicsManager::addForce(Particle* particle, ForceGenerator* generator) {
	forcePair f;
	f.generator = generator;
	f.target = particle;
	forceRegistry.push_back(f);
}

void PhysicsManager::updateForces() {
	for (int i = 0; i < forceRegistry.size(); i++) {
		forceRegistry[i].generator->applyForce(forceRegistry[i].target);
	}
}

void PhysicsManager::applyToAll(Vector appForce) {
	if (!particleList.empty()) {
		for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
			(*i)->applyForce(appForce);
		}
	}
}

void PhysicsManager::addToAll(ForceGenerator* generator) {
	if (!particleList.empty()) {
		for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
			addForce(*i, generator);
		}
	}
}

void PhysicsManager::update(float deltaTime) {
	updateParticleList();
	updateForces();

	if (!particleList.empty()) {
		for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
			(*i)->update(deltaTime);
		}
	}
}

void PhysicsManager::drawAll(sf::RenderWindow* pgWindow) {
	if (!particleList.empty()) {
		for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
			(*i)->draw(pgWindow);
		}
	}
}

void PhysicsManager::updateParticleList() {
	if (!particleList.empty()) {
		if (particleList.size() == 1) {
			list<Particle*>::iterator i = particleList.begin();
			if ((*i)->destroyed()) particleList.erase(i);
		}

		else {
			for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
				if ((*i)->destroyed()) {
					list<Particle*>::iterator temp = i;
					i++;
					particleList.erase(temp);
				}
			}
		}
	}
}