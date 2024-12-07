#include"Vector.h"
#include"Particle.h"
#include"ContactResolver.h"
#include"ForceGenerator.h"
#pragma once

class ParticleAnchor
{
public:
	ParticleAnchor(Vector, Particle*);
	void draw(sf::RenderWindow*);
	void update();

	Vector anchorPoint;
	Particle* particle;
	ForceGenerator* forceGen;
	sf::Vertex line[2];
protected:
	float getCurrentLength();
};