#include "ParticleLink.h"

ContactResolver* ParticleLink::getContact() {
	return nullptr;
}

void ParticleLink::draw(sf::RenderWindow* pgWindow) {
	pgWindow->draw(line, 2, sf::Lines);
}

void::ParticleLink::update() {
	line[0].position = partners[0]->psSprite->getPosition();
	line[1].position = partners[1]->psSprite->getPosition();
}

float ParticleLink::getCurrentLength() {
	Vector length = partners[0]->getPosition() - partners[1]->getPosition();
	return length.getMagnitude();
}