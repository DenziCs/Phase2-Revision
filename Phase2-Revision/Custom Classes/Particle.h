#include"Vector.h"
#include"Utils.h"
#include<SFML/Graphics.hpp>
#include<vector>
#include<math.h>
#pragma once
using namespace std;
using namespace gdphys;

class Particle
{
public:
	enum ParticleType {
		GenericParticle = 0,
		GenericRigidBody = 1,
		CircleRigidBody = 2,
		RectangleRigidBody = 3
	};

	Particle();
	Particle(bool, float, float, float, float, float, sf::Color);

	void setLifespanMode(bool);
	void setMass(float);
	void setPosition(float, float);
	void setVelocity(Vector);
	void setLifespan(float);
	void setRadius(float);
	void setColor(sf::Color);
	void setDampFactor(float);

	float getMass();
	Vector getPosition();
	Vector getVelocity();
	Vector getAcceleration();
	float getRadius();
	bool destroyed();
	virtual float getMomentOfInertia();

	void applyForce(Vector);
	void resetForce();
	void update(float);
	void draw(sf::RenderWindow*);

	sf::Shape* psSprite;
	ParticleType particleType;
protected:
	float mass;
	Vector velocity;
	Vector acceleration;
	Vector netForce;
	float netTorque = 0;

	float lifespan;
	float restitution;
	float dampFactor = 1.f;
	float angularDampFactor = 1.f;
	float angularVelocity;
	float rotation;

	bool hasLifespan = false;
	bool isDestroyed = false;
};