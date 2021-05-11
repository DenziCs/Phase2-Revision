#include"Vector.h"
#include<SFML/Graphics.hpp>
#include<vector>
#include<math.h>
#pragma once
using namespace std;
using namespace gdphys;

class Particle
{
public:
	Particle();
	Particle(float, float, float, float, float, float, sf::Color);
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
	void applyForce(Vector);
	void resetForce();
	void update(float);
	void draw(sf::RenderWindow*);

	sf::CircleShape* psSprite;
private:
	Vector asWindowVector(Vector);

	float mass;
	Vector velocity;
	Vector acceleration;
	Vector netForce;
		// Default constructor yields the zero vector.
	float lifespan;
	float dampFactor = 1;
	bool isDestroyed = false;
};