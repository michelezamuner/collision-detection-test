#ifndef VECTOR_H
#define VECTOR_H

#include <string>

using std::string;
using std::ostream;

namespace slc
{
	class Vector
	{
	public:
		Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Vector(float* v, int size = 3);
		Vector(const Vector& v);
		float getModulus() const;
		float getX() const;
		Vector& setX(float v);
		float getY() const;
		Vector& setY(float v);
		float getZ() const;
		Vector& setZ(float v);
		Vector& set(float* v, int size = 3);
		Vector& set(const Vector& v);
		Vector& set(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		float* toArray(int size) const;
		Vector& getDistanceFrom(const Vector& v) const;
		const string toString() const;
		operator string() const;
		operator float() const;
	protected:
		float x, y, z;
		void loadArray(float* v, int size);
		static float norm(float v);
	};
}
ostream& operator<<(ostream& str, const slc::Vector& v);
#endif
