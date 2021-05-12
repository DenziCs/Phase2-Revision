#include"Vector.h"
#include"Particle.h"
#include"ContactResolver.h"
#pragma once

class ParticleLink
{
public:
	virtual ContactResolver* getContact();
	void draw(sf::RenderWindow*);
	float getCurrentLength();
	void update();

	Particle* partners[2];
	sf::Vertex line[2];
};