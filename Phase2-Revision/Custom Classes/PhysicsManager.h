#include"Particle.h"
#include"ForceGenerator.h"
#include"GravityForceGenerator.h"
#include"AppliedForceGenerator.h"
#include"ContactResolver.h"
#include<list>
#include<vector>
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

	void addForce(Particle*, ForceGenerator*);
	void removeForce(Particle*, ForceGenerator*);
	void clearRegistry();

	void applyToAll(Vector);
	void addToAll(ForceGenerator*);

	void addContact(Particle*, Particle*, float, float);

	void updateForces();
	void update(float);
	void drawAll(sf::RenderWindow*);
	
	list<Particle*> particleList;
	vector<ContactResolver*> contactList;
private:
	struct forcePair {
		ForceGenerator* generator;
		Particle* target;
	};
	
	void updateParticleList();

	list<forcePair> forceRegistry;
	GravityForceGenerator gravityGenerator;
	Vector worldOrigin;
	int particleLimit;
};