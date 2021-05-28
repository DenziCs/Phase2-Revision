#pragma once
#include "Vector.h"
#include<SFML/Graphics.hpp>
using namespace gdphys;

class Utils{
public:
	static Vector toPhysicsPoint(sf::Vector2f);
	static sf::Vector2f toWindowPoint(Vector v);
	static Vector toPhysicsVector(sf::Vector2f);
	static sf::Vector2f toWindowVector(Vector v);
	static float inDegrees(float theta);
	static float inRadians(float theta);
	static Vector rotatePoint(Vector, float);

	static Vector worldOrigin;
};