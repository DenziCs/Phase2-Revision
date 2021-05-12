#include "AnchoredCable.h"

AnchoredCable::AnchoredCable(
	Vector position,
	Particle* _particle,
	float springConstant,
	float restLength
) : ParticleAnchor(position, _particle)
{
	length = restLength;
	this->forceGen = new AnchoredCableForceGenerator(position, springConstant, restLength);
}

ContactResolver* AnchoredCable::getContact() {
	float currentLength = this->getCurrentLength();
	if (currentLength <= length) return nullptr;

	ContactResolver* contact = new ContactResolver();
	contact->particles[0] = particle;
	contact->particles[1] = nullptr;
	Vector direction = (anchorPoint - contact->particles[0]->getPosition()).getNormalized();
	contact->restitution = restitution;

	if (currentLength > length) {
		contact->contactNormal = direction;
		contact->overlapDepth = currentLength - length;
	}

	return contact;
}