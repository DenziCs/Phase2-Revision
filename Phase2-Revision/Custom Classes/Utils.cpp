#include "Utils.h"

Vector Utils::worldOrigin = Vector(0, 0);

sf::Vector2f Utils::toWindowPoint(Vector v) {
	return sf::Vector2f(worldOrigin.x + v.x, worldOrigin.y - v.y);
}