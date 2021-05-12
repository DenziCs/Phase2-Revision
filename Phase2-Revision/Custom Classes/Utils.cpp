#include "Utils.h"

Vector Utils::worldOrigin = Vector(0, 0);

Vector Utils::toPhysicsPoint(sf::Vector2f v) {
	return Vector(v.x - worldOrigin.x, worldOrigin.y - v.y);
}

sf::Vector2f Utils::toWindowPoint(Vector v) {
	return sf::Vector2f(worldOrigin.x + v.x, worldOrigin.y - v.y);
}

Vector Utils::toPhysicsVector(sf::Vector2f v) {
	return Vector(v.x, -v.y);
}

sf::Vector2f Utils::toWindowVector(Vector v) {
	return sf::Vector2f(v.x, -v.y);
}