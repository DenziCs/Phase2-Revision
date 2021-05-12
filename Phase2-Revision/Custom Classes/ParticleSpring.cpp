#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(Particle* particle1, Particle* particle2, float springConst, float restLength) {
	partners[0] = particle1;
	partners[1] = particle2;
	forceGen = new ParticleSpringForceGenerator(particle2, springConst, restLength);

	line[0].color = sf::Color::White;
	line[0].position = partners[0]->psSprite->getPosition();

	line[1].color = sf::Color::White;
	line[1].position = partners[1]->psSprite->getPosition();
}