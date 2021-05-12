#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* particle1, Particle* particle2, float len) {
	partners[0] = particle1;
	partners[1] = particle2;
	length = len;

	line[0].color = sf::Color::White;
	line[0].position = partners[0]->psSprite->getPosition();

	line[1].color = sf::Color::White;
	line[1].position = partners[1]->psSprite->getPosition();
}

ContactResolver* ParticleRod::getContact() {
	float currentLength = getCurrentLength();
	if (currentLength == length) return nullptr;

	ContactResolver* contact = new ContactResolver();
	contact->particles[0] = partners[0];
	contact->particles[1] = partners[1];
	contact->restitution = restitution;

	if (currentLength > length) {
		contact->contactNormal = contact->getContactNormal();
		contact->overlapDepth = currentLength - length;
	}
	else {
		contact->contactNormal = contact->getContactNormal() * -1;
		contact->overlapDepth = (currentLength - length) * -1;
	}
	
	return contact;
}