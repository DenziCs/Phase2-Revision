#include "AnchoredRod.h"

AnchoredRod::AnchoredRod(
	Vector position,
	Particle* _particle
) : ParticleAnchor(position, _particle)
{
	length = getCurrentLength();
}

ContactResolver* AnchoredRod::getContact() {
	float currentLength = this->getCurrentLength();
	if (currentLength == length) return nullptr;

	ContactResolver* contact = new ContactResolver();
	contact->particles[0] = particle;
	contact->particles[1] = nullptr;
	Vector direction = (anchorPoint - contact->particles[0]->getPosition()).getNormalized();
	contact->restitution = restitution;

	if (currentLength > length) {
		contact->contactNormal = direction;
		contact->overlapDepth = currentLength - length;
	}

	else {
		contact->contactNormal = direction * -1;
		contact->overlapDepth = -currentLength + length;
	}

	return contact;
}