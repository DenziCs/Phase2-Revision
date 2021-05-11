#include"Particle.h"
#include<list>
#include<SFML/Graphics.hpp>
#include<time.h>
#pragma once
using namespace std;
using namespace gdphys;

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	void setGravity(float, Vector);
	void setLimit(int);
	void setOrigin(Vector);
	Vector getGravity();
	int getLimit();
	Vector getOrigin();
	Vector asWindowPoint(Vector);
	void addParticle(Particle*);
	void applyToAll(Vector);
	void resetAll();
	void update(float);
	void drawAll(sf::RenderWindow*);
	
	list<Particle*> particleList;
private:
	void updateParticleList();

	Vector gravity;
	Vector worldOrigin;
	int particleLimit;
};