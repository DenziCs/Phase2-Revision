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

void PhysicsManager::setDrawLinks(bool flag) {
	drawLinks = flag;
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

		float rest = a->getRestitution();
		if (b->getRestitution() < a->getRestitution()) rest = b->getRestitution();
		addContact(a, b, rest, depth);
	}
}

void PhysicsManager::getRectangleOverlaps(Particle* a, Particle* b) {
	switch (a->particleType) {
	case Particle::RectangleRigidBody:
		switch (b->particleType) {
		case Particle::RectangleRigidBody:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void PhysicsManager::checkParticles() {
	for (int i = 0; i < particleList.size() - 1; i++) {

		std::list<Particle*>::iterator a = std::next(particleList.begin(), i);

		for (int j = i + 1; j < particleList.size(); j++) {

			std::list<Particle*>::iterator b = std::next(particleList.begin(), j);

			switch ((*a)->particleType) {
			case Particle::GenericParticle:
			case Particle::CircleRigidBody:
				switch ((*b)->particleType) {
				case Particle::GenericParticle:
				case Particle::CircleRigidBody:
					getParticleOverlaps(*a, *b);
					break;
				default:
					getRectangleOverlaps(*a, *b);
				}
				break;
			default:
				getRectangleOverlaps(*a, *b);
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

	if (drawLinks) {
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

void PhysicsManager::generateParticleContacts(Particle* a, Particle* b) {
	float x1 = (a)->getPosition().x;
	float x2 = (b)->getPosition().x;
	float y1 = (a)->getPosition().y;
	float y2 = (b)->getPosition().y;

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

void PhysicsManager::generateRigidbodyContacts(Particle* a, Particle* b) {
	/*
		GenericParticle = 0,
		GenericRigidBody = 1,
		CircleRigidBody = 2,
		RectangleRigidBody = 3
	*/

	//for 2 circles or a circle and particle
	if ((a->particleType == 2 && b->particleType == 2) ||
		(a->particleType == 2 && b->particleType == 0) ||
		(a->particleType == 0 && b->particleType == 2))
	{
		//both objects can be considered a circle
		generateParticleContacts(a, b);
	}

	//2 rectangle rigidbodies
	else if (a->particleType == 3 && b->particleType == 3) {
		processRigidbodyContact(a, b);
	}

	//rect and circle
	else {
		//a is rect
		if (a->particleType == 3) {
			processRigidbodyContact(a, b);
		}

		//b is rect
		else {
			processRigidbodyContact(b, a);
		}
	}
}

//rectangle and circle
void PhysicsManager::processRigidbodyContact(RectangularPrism* a, Particle* b) {
	Vector relVector = b->getPosition() - a->getPosition();
	float invAngle = -(a->getRotation());
	Vector locVector = Utils::rotatePoint(relVector, invAngle);

	float minX = locVector.x;
	if ((a->getWidth() / 2) < minX) {
		minX = a->getWidth() / 2;
	}
	float maxX = minX;
	if (maxX < -(a->getWidth() / 2)) {
		maxX = -(a->getWidth() / 2);
	}

	float minY = locVector.y;
	if ((a->getLength() / 2) < minY) {
		minY = a->getLength() / 2;
	}
	float maxY = minY;
	if (maxY < -(a->getLength() / 2)) {
		maxY = -(a->getLength() / 2);
	}

	float D_x = locVector.x - maxX;
	float D_y = locVector.y - maxY;

	bool col = ((D_x * D_x) + (D_y + D_y)) <= (b->getRadius() * b->getRadius());
	float depth = (D_x * D_x) + (D_y + D_y);

	if (col) {
		Vector dir = locVector * -1;
		dir = dir.getNormalized();

		float restitution = a->getRest();
		if (b->getRestitution() < a->getRest()) {
			restitution = b->getRestitution();
		}

		addContact(a, b, restitution, depth);
	}
}

//two rectangles
void PhysicsManager::processRigidbodyContact(RectangularPrism* a, RectangularPrism* b) {
	std::vector<RectangularPrism*> rects;
	rects.push_back(a);
	rects.push_back(b);

	bool ret = true;

	for (int i = 0; i < rects.size(); i++) {
		for (int e1 = 0; e1 < rects[i]->points.size(); e1++) {
			int e2 = (e1 + 1) % rects[i]->points.size();
			Vector p1 = rects[i]->points[e1];
			Vector p2 = rects[i]->points[e2];
			
			Vector projectionNormal = Vector(p2.y - p1.y, p1.x - p2.x);

			//first rect
			float minA = projectionNormal.dotProduct(rects[0]->points[0]);
			float maxA = projectionNormal.dotProduct(rects[0]->points[0]);

			for (int h = 1; h < rects[0]->points.size(); h++) {
				float proj = projectionNormal.dotProduct(rects[0]->points[h]);

				if (proj < minA) minA = proj;
				if (proj > maxA) maxA = proj;
			}

			//second rect
			float minB = projectionNormal.dotProduct(rects[1]->points[0]);
			float maxB = projectionNormal.dotProduct(rects[1]->points[0]);

			for (int h = 1; h < rects[1]->points.size(); h++) {
				float proj = projectionNormal.dotProduct(rects[1]->points[h]);

				if (proj < minB) minB = proj;
				if (proj > maxB) maxB = proj;
			}

			//check if test fail
			if (maxA < minB || maxB < minA) {
				ret = false;
				//end loop to save calls
				break;
			}

			if (ret) {
				Vector dir = a->getPosition() - b->getPosition();
				dir = dir.getNormalized();

				float rest = a->getRestitution();
				if (b->getRestitution() < a->getRestitution()) rest = b->getRestitution();

				addContact(a, b, rest, 0);
			}
		}
	}
}

//two circles
void PhysicsManager::processRigidbodyContact(Particle* a, Particle* b) {
	float x1 = (a)->getPosition().x;
	float x2 = (b)->getPosition().x;
	float y1 = (a)->getPosition().y;
	float y2 = (b)->getPosition().y;

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