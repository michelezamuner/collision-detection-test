#include <cmath>
#include "Vector.h"
#include <sstream>

Vector::Vector(float x, float y, float z):
	x(x), y(y), z(z)
{
}

Vector::Vector(float* v, int size)
{
	loadArray(v, size);
}

void Vector::loadArray(float* v, int size)
{
	if (size < 1 || size > 3)
		throw "Invalid array size";
	x = v[0];
	if (size > 1) y = v[1];
	if (size > 2) z = v[2];
}

float* Vector::toArray(int size) const
{
	if (size < 1 || size > 3)
		throw "Invalid array size";
        float* result = new float[size];
	result[0] = x;
	if (size > 1) result[1] = y;
	if (size > 2) result[2] = z;
	return result;
}

Vector::Vector(const Vector& v):
	x(v.x), y(v.y), z(v.z)
{
}

float Vector::getModulus() const
{
	return sqrt(x*x + y*y);
}

float Vector::getX() const
{
	return x;
}

Vector& Vector::setX(float v)
{
	x = v;
	return *this;
}

float Vector::getY() const
{
	return y;
}

Vector& Vector::setY(float v)
{
	y = v;
	return *this;
}

float Vector::getZ() const
{
	return z;
}

Vector& Vector::setZ(float v)
{
	z = v;
	return *this;
}

Vector& Vector::set(float* v, int size)
{
	loadArray(v, size);
	return *this;
}

Vector& Vector::set(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector& Vector::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

Vector& Vector::getDistanceFrom(const Vector& v) const
{
	return *new Vector(v.x - x, v.y - y, 0);
}

const string Vector::toString() const
{
	ostringstream stm;
	stm << '(' << x << ", " << y << ", " << z << ')';
	return stm.str();
}

Vector::operator string() const
{
	return toString();
}

Vector::operator float() const
{
	return getModulus();
}

ostream& operator<<(ostream& str, const Vector& v)
{
	return str << (string)v;
}
