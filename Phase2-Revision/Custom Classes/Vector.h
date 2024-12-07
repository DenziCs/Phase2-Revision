#include<iostream>
#include<math.h>
#pragma once

namespace gdphys {
	class Vector {
	public:
		float x;
		float y;

		Vector();
		Vector(float, float);
		float getMagnitude();
		Vector getNormalized();
		Vector operator +(const Vector&);
		Vector operator -(const Vector&);
		Vector operator *(float);
		Vector comProduct(Vector);
		float dotProduct(Vector);
		float crossProduct(Vector);
	};
}