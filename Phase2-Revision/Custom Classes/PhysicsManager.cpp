#include "PhysicsManager.h"

PhysicsManager::PhysicsManager() {
	srand(time(0));
}

PhysicsManager::~PhysicsManager() {
	contactList.clear();
	forceRegistry.clear();
	anchorList.clear();
	linkList.clear();
	particleList.clear();
}

void PhysicsManager::setGravity(float gravMagnitude, Vector gravDirect) {
	gravityGenerator.setGravity(gravDirect * gravMagnitude);
}

void PhysicsManager::setLimit(unsigned int limit) {
	particleLimit = limit;
}

void PhysicsManager::setOrigin(Vector origin) {
	Utils::worldOrigin = origin;
}

void PhysicsManager::setContactLimit(unsigned int limit) {
	iterator.max_iterations = limit;
}

Vector PhysicsManager::getGravity() {
	return gravityGenerator.getGravity();
}

int PhysicsManager::getLimit() {
	return particleLimit;
}

Vector PhysicsManager::getOrigin() {
	return Utils::worldOrigin;
}

void PhysicsManager::addParticle(Particle* particle) {
	if (particleList.size() < particleLimit) {
		particleList.push_back(particle);
		addForce(particle, &gravityGenerator);
	}
}

void PhysicsManager::addForce(Particle* particle, ForceGenerator* generator) {
	forcePair f;
	f.generator = generator;
	f.target = particle;
	forceRegistry.push_back(f);
}

void PhysicsManager::removeForce(Particle* target, ForceGenerator* generator) {
	forceRegistry.remove_if([target, generator](forcePair f) {return f.target == target && f.generator == generator; });
}

void PhysicsManager::updateForces() {
	for (list<forcePair>::iterator i = forceRegistry.begin(); i != forceRegistry.end(); i++) {
		i->generator->applyForce(i->target);
	}
}

void PhysicsManager::clearRegistry() {
	forceRegistry.clear();
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

void PhysicsManager::addContact(Particle* particleA, Particle* particleB, float restitution, float depth) {
	ContactResolver* contact = new ContactResolver(particleA, particleB, restitution, depth);
	contactList.push_back(contact);
}

void PhysicsManager::getParticleOverlaps(Particle* a, Particle* b) {
	float x1 = a->getPosition().x;
	float x2 = b->getPosition().x;
	float y1 = a->getPosition().y;
	float y2 = b->getPosition().y;

	//square magnitude
	float mag2 = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));

	//square of sum of radius
	float rad2 = ((a)->getRadius() + (b)->getRadius()) * ((a)->getRadius() + (b)->getRadius());

	//if sq mag = sq sum; touching
	//if sq mag < sq sum; overlapping
	if (mag2 <= rad2) {
		Vector dir = Vector((a)->getPosition().x - (b)->getPosition().x, (a)->getPosition().y - (b)->getPosition().y);
		dir = dir.getNormalized();
		float r = rad2 - mag2;
		float depth = sqrt(r);
		addContact(a, b, 1.f, depth);
	}
}

void PhysicsManager::getRigidBodyOverlaps() {}

void PhysicsManager::checkParticles() {
	for (int i = 0; i < particleList.size() - 1; i++) {

		std::list<Particle*>::iterator a = std::next(particleList.begin(), i);

		for (int j = i + 1; j < particleList.size(); j++) {

			std::list<Particle*>::iterator b = std::next(particleList.begin(), j);

			switch ((*a)->particleType) {
			case Particle::GenericParticle:
				switch ((*b)->particleType) {
				case Particle::GenericParticle:
					getParticleOverlaps(*a, *b);
					break;
				}
				break;
			default:
				break;
			}

		}
	}
}

void PhysicsManager::checkAnchors() {
	if (!anchorList.empty()) {
		for (int i = 0; i < anchorList.size(); i++) {
			ContactResolver* contact = anchorList[i]->getContact();
			if (contact != nullptr) contactList.push_back(contact);
		}
	}
}

void PhysicsManager::checkLinks() {
	if (!linkList.empty()) {
		for (int i = 0; i < linkList.size(); i++) {
			ContactResolver* contact = linkList[i]->getContact();
			if(contact != nullptr) contactList.push_back(contact);
		}
	}
}

void PhysicsManager::anchorWithSpring(Particle* particle, Vector anchorPoint, float springConst, float restLength) {
	AnchoredSpring* spring = new AnchoredSpring(anchorPoint, particle, springConst, restLength);
	anchorList.push_back(spring);
	addForce(particle, spring->forceGen);
}

void PhysicsManager::anchorWithCable(Particle* particle, Vector anchorPoint, float springConst, float restLength) {
	AnchoredCable* cable = new AnchoredCable(anchorPoint, particle, springConst, restLength);
	anchorList.push_back(cable);
	addForce(particle, cable->forceGen);
}

void PhysicsManager::linkWithSpring(Particle* particleA, Particle* particleB, float springConst, float restLength) {
	ParticleSpring* spring = new ParticleSpring(particleA, particleB, springConst, restLength);
	linkList.push_back(spring);
	addForce(particleA, spring->forceGen);
}

void PhysicsManager::linkWithRod(Particle* particleA, Particle* particleB) {
	ParticleRod* rod = new ParticleRod(particleA, particleB);
	linkList.push_back(rod);
}

void PhysicsManager::update(float deltaTime) {
	updateParticleList();
	updateForces();

	if (!particleList.empty()) {
		for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
			(*i)->update(deltaTime);
		}
	}

	checkParticles();
	checkAnchors();
	checkLinks();
	iterator.resolveContacts(contactList);
	contactList.clear();

	if (!anchorList.empty()) {
		for (int i = 0; i < anchorList.size(); i++) {
			anchorList[i]->update();
		}
	}

	if (!linkList.empty()) {
		for (int i = 0; i < linkList.size(); i++) {
			linkList[i]->update();
		}
	}
}

void PhysicsManager::drawAll(sf::RenderWindow* pgWindow) {
	if (!particleList.empty()) {
		for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
			(*i)->draw(pgWindow);
		}
	}

	if (!anchorList.empty()) {
		for (int i = 0; i < anchorList.size(); i++) {
			anchorList[i]->draw(pgWindow);
		}
	}

	if (!linkList.empty()) {
		for (int i = 0; i < linkList.size(); i++) {
			linkList[i]->draw(pgWindow);
		}
	}
}

void PhysicsManager::updateParticleList() {
	if (!particleList.empty()) {
		if (particleList.size() == 1) {
			list<Particle*>::iterator i = particleList.begin();
			if ((*i)->destroyed()) {
				forceRegistry.remove_if([i](forcePair f) {return f.target == *i; });

				int oldSize = linkList.size();
				for (int j = 0; j < oldSize; j++) {
					if (linkList[j]->partners[0] == *i) {
						linkList.erase(linkList.begin() + j);
					}
					else if (linkList[j]->partners[1] && linkList[j]->partners[1] == *i) {
						linkList.erase(linkList.begin() + j);
					}
				}

				oldSize = anchorList.size();
				for (int j = 0; j < oldSize; j++) {
					if (anchorList[j]->particle == *i) {
						anchorList.erase(anchorList.begin() + j);
					}
				}

				particleList.erase(i);
			}
		}

		else {
			for (list<Particle*>::iterator i = particleList.begin(); i != particleList.end(); i++) {
				if ((*i)->destroyed()) {
					forceRegistry.remove_if([i](forcePair f) {return f.target == *i; });

					int oldSize = linkList.size();
					for (int j = 0; j < oldSize; j++) {
						if (linkList[j]->partners[0] == *i) {
							linkList.erase(linkList.begin() + j);
						}
						else if (linkList[j]->partners[1] && linkList[j]->partners[1] == *i) {
							linkList.erase(linkList.begin() + j);
						}
					}

					oldSize = anchorList.size();
					for (int j = 0; j < oldSize; j++) {
						if (anchorList[j]->particle == *i) {
							anchorList.erase(anchorList.begin() + j);
						}
					}
				}
			}
			particleList.remove_if([](Particle* p) {return p->destroyed(); });
		}
	}
}