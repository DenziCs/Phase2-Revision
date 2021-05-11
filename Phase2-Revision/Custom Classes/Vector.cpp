#include "Vector.h"
using namespace gdphys;

Vector::Vector() {
	x = 0;
	y = 0;
}

Vector::Vector(float _x, float _y) {
	x = _x;
	y = _y;
}

float Vector::getMagnitude() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector::normalize() {
	Vector normVector;
	this->x = x / getMagnitude();
	this->y = y / getMagnitude();
}

Vector Vector::operator +(const Vector& vector2) {
	Vector vectorSum;
	vectorSum.x = this->x + vector2.x;
	vectorSum.y = this->y + vector2.y;
	return vectorSum;
}

Vector Vector::operator -(const Vector& vector2) {
	Vector resultVector;
	resultVector.x = this->x - vector2.x;
	resultVector.y = this->y - vector2.y;
	return resultVector;
}

Vector Vector::operator *(float scalar) {
	Vector resultVector;
	resultVector.x = scalar * this->x;
	resultVector.y = scalar * this->y;
	return resultVector;
}

Vector Vector::comProduct(Vector vector2) {
	Vector resultVector;
	resultVector.x = this->x * vector2.x;
	resultVector.y = this->y * vector2.y;
	return resultVector;
}

float Vector::dotProduct(Vector vector2) {
	Vector resultVector = comProduct(vector2);
	return resultVector.x + resultVector.y;
}

float Vector::crossProduct(Vector vector2) {
	return (this->x * vector2.y) - (this->y * vector2.x);
}