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

float Utils::inDegrees(float theta) {
	return theta * (180.f / acos(-1.f));
}

float Utils::inRadians(float theta) {
	return theta * (acos(-1.f) / 180.f);
}

Vector Utils::rotatePoint(Vector v, float theta) {
	Vector result;
	result.x = (v.x * cos(theta)) + (v.y * sin(theta));
	result.y = -(v.x * sin(theta)) + (v.y * cos(theta));
	return result;
}