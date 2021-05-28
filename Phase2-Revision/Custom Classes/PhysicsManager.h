#include"Utils.h"
#include"Particle.h"
#include"ForceGenerator.h"
#include"GravityForceGenerator.h"
#include"AppliedForceGenerator.h"
#include"ContactResolver.h"
#include"ContactResolverIterator.h"
#include"ParticleAnchor.h"
#include"AnchoredSpring.h"
#include"AnchoredCable.h"
#include"ParticleLink.h"
#include"ParticleSpring.h"
#include"ParticleRod.h"
#include"RigidBody.h"
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
	void setLimit(unsigned int);
	void setOrigin(Vector);
	void setContactLimit(unsigned int);

	Vector getGravity();
	int getLimit();
	Vector getOrigin();

	void addParticle(Particle*);

	void addForce(Particle*, ForceGenerator*);
	void removeForce(Particle*, ForceGenerator*);
	void clearRegistry();

	void applyToAll(Vector);
	void addToAll(ForceGenerator*);

	void addContact(Particle*, Particle*, float, float);
	void getParticleOverlaps(Particle*, Particle*);
	void getRigidBodyOverlaps();
	void checkParticles();
	void checkAnchors();
	void checkLinks();

	void anchorWithSpring(Particle*, Vector, float, float);
	void anchorWithCable(Particle*, Vector, float, float);

	void linkWithSpring(Particle*, Particle*, float, float);
	void linkWithRod(Particle*, Particle*);

	void updateForces();
	void update(float);
	void drawAll(sf::RenderWindow*);
	
	list<Particle*> particleList;
	vector<ContactResolver*> contactList;
	vector<ParticleAnchor*> anchorList;
	vector<ParticleLink*> linkList;
private:
	struct forcePair {
		ForceGenerator* generator;
		Particle* target;
	};
	
	void updateParticleList();

	list<forcePair> forceRegistry;
	ContactResolverIterator iterator;
	GravityForceGenerator gravityGenerator;
	int particleLimit;
};