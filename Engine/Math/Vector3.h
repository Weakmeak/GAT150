#pragma once
#include <cmath>
namespace digi {

	struct Vector3
	{
		float x, y, z;

		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
		Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y },  z{ (float)z } {}
		Vector3(float v) : x{ v }, y{ v }, z{ v } {}

		void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector3 operator + (const Vector3& vec) const { return Vector3{ (this->x + vec.x), (this->y + vec.y), (this->z + vec.z) }; }
		Vector3 operator - (const Vector3& vec) const { return Vector3{ (this->x - vec.x), (this->y - vec.y), (this->z - vec.z) }; }
		Vector3 operator * (const Vector3& vec) const { return Vector3{ (this->x * vec.x), (this->y * vec.y), (this->z * vec.z) }; }
		Vector3 operator / (const Vector3& vec) const { return Vector3{ (this->x / vec.x), (this->y / vec.y), (this->z / vec.z) }; }

		Vector3& operator += (const Vector3& vec) { this->x += vec.x; this->y += vec.y; this->z += vec.z; return *this; }
		Vector3& operator -= (const Vector3& vec) { this->x -= vec.x; this->y -= vec.y; this->z -= vec.z; return *this; }
		Vector3& operator *= (const Vector3& vec) { this->x *= vec.x; this->y *= vec.y; this->z *= vec.z; return *this; }
		Vector3& operator /= (const Vector3& vec) { this->x /= vec.x; this->y /= vec.y; this->z /= vec.z; return *this; }

		Vector3& operator += (float s) { this->x += s; this->y += s; this->z += s; return *this; }
		Vector3& operator -= (float s) { this->x -= s; this->y -= s; this->z -= s; return *this; }
		Vector3& operator *= (float s) { this->x *= s; this->y *= s; this->z *= s; return *this; }
		Vector3& operator /= (float s) { this->x /= s; this->y /= s; this->z /= s; return *this; }

		Vector3 operator + (const float& s) const { return Vector3{ (this->x + s), (this->y + s), (this->z + s) }; }
		Vector3 operator - (const float& s) const { return Vector3{ (this->x - s), (this->y - s), (this->z - s) }; }
		Vector3 operator * (const float& s) const { return Vector3{ (this->x * s), (this->y * s), (this->z * s) }; }
		Vector3 operator / (const float& s) const { return Vector3{ (this->x / s), (this->y / s), (this->z / s) }; }

		Vector3 operator - () { return Vector3{ -x, -y, -z }; }

		bool operator == (const Vector3& vec) const { return (this->x == vec.x) && (this->y == vec.y) && (this->z == vec.z); }
		bool operator != (const Vector3& vec) const { return !(*this == vec); }

		float LengthSqr();
		float Length();

		float DistanceSqr(const Vector3& vec);
		float Distance(const Vector3& vec);

		Vector3 Normalized();
		void Normalize();
	};

	inline float Vector3::LengthSqr() { return (x * x) + (y * y) + (z * z); }
	inline float Vector3::Length() { return std::sqrt(LengthSqr()); }
	inline float Vector3::DistanceSqr(const Vector3& vec) { return (*this - vec).LengthSqr(); }
	inline float Vector3::Distance(const Vector3& vec) { return (*this - vec).Length(); }
	inline Vector3 Vector3::Normalized()
	{
		float len = Length();
		if (len == 0) {
			return Vector3(0.0f);
		}
		return Vector3{ x / len, y / len, z / len };
	}
	inline void Vector3::Normalize()
	{
		*this /= Length();
	}
}