#include "ParticleAnchor.h"

ParticleAnchor::ParticleAnchor(Vector position, Particle* _particle) {
	anchorPoint = position;
	particle = _particle;

	line[0].color = sf::Color::White;
	line[0].position = Utils::toWindowPoint(anchorPoint);

	line[1].color = sf::Color::White;
	line[1].position = particle->psSprite->getPosition();
}

ContactResolver* ParticleAnchor::getContact() {
	return nullptr;
}

float ParticleAnchor::getCurrentLength() {
	Vector length = anchorPoint - particle->getPosition();
	return length.getMagnitude();
}

void ParticleAnchor::draw(sf::RenderWindow* pgWindow) {
	pgWindow->draw(line, 2, sf::Lines);
}

void::ParticleAnchor::update() {
	line[1].position = particle->psSprite->getPosition();
}