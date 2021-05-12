#pragma once
#include "Vector.h"
#include<SFML/Graphics.hpp>
using namespace gdphys;

class Utils{
public:
	static Vector worldOrigin;
	static sf::Vector2f toWindowPoint(Vector v);
};