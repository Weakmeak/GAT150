#pragma once
#include <cmath>
#include <sstream>
#include <string>

namespace digi {

	struct Vector2
	{
		float x, y;

		Vector2() : x{0}, y{0} {}
		Vector2(float x, float y) : x{x}, y{y} {}
		Vector2(int x, int y) : x{(float)x}, y{(float)y} {}
		Vector2(float v) : x{v}, y{v} {}

		void Set(float x, float y) { this->x = x; this->y = y; }
		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector2 operator + (const Vector2& vec) const { return Vector2{ (this->x + vec.x), (this->y + vec.y) }; }
		Vector2 operator - (const Vector2& vec) const { return Vector2{ (this->x - vec.x), (this->y - vec.y) }; }
		Vector2 operator * (const Vector2& vec) const { return Vector2{ (this->x * vec.x), (this->y * vec.y) }; }
		Vector2 operator / (const Vector2& vec) const { return Vector2{ (this->x / vec.x), (this->y / vec.y) }; }

		Vector2& operator += (const Vector2& vec) { this->x += vec.x; this->y += vec.y; return *this; }
		Vector2& operator -= (const Vector2& vec) { this->x -= vec.x; this->y -= vec.y; return *this; }
		Vector2& operator *= (const Vector2& vec) { this->x *= vec.x; this->y *= vec.y; return *this; }
		Vector2& operator /= (const Vector2& vec) { this->x /= vec.x; this->y /= vec.y; return *this; }

		Vector2& operator += (float s) { this->x += s; this->y += s; return *this; }
		Vector2& operator -= (float s) { this->x -= s; this->y -= s; return *this; }
		Vector2& operator *= (float s) { this->x *= s; this->y *= s; return *this; }
		Vector2& operator /= (float s) { this->x /= s; this->y /= s; return *this; }

		Vector2 operator + (const float& s) const { return Vector2{ (this->x + s), (this->y + s) }; }
		Vector2 operator - (const float& s) const { return Vector2{ (this->x - s), (this->y - s) }; }
		Vector2 operator * (const float& s) const { return Vector2{ (this->x * s), (this->y * s) }; }
		Vector2 operator / (const float& s) const { return Vector2{ (this->x / s), (this->y / s) }; }

		Vector2 operator - () { return Vector2{ -x, -y }; }

		bool operator == (const Vector2& vec) const { return (this->x == vec.x) && (this->y == vec.y); }
		bool operator != (const Vector2& vec) const { return (this->x != vec.x) || (this->y != vec.y); }

		float LengthSqr();
		float Length();

		float DistanceSqr(const Vector2& vec);
		float Distance(const Vector2& vec);
		
		Vector2 Normalized();
		void Normalize();

		float Dot(const Vector2& v);
		float GetAngleBetween(const Vector2& v);
		float GetSignedAngleBetween(const Vector2& v);

		static Vector2 Rotate(const Vector2 vec, float angle);
		float GetAngle()
		{
			return std::atan2(y, x);
		}

		//friend std::istream& >> (std::istream& stream, Vector2& vec)

		static const Vector2 one;
		static const Vector2 zero;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 left;
		static const Vector2 right;
	};

	std::istream& operator >> (std::istream& stream, Vector2& out);
	std::ostream& operator << (std::ostream& stream, const Vector2& v);

	inline float Vector2::LengthSqr() { return (x * x) + (y * y); }
	inline float Vector2::Length() { return std::sqrt(x * x + y * y); }
	inline float Vector2::DistanceSqr(const Vector2& vec) { return (*this - vec).LengthSqr(); }
	inline float Vector2::Distance(const Vector2& vec) { return (*this - vec).Length(); }
	inline Vector2 Vector2::Normalized()
	{
		float len = Length();
		if (len == 0) {
			return Vector2::zero;
		}
		return Vector2{ x/len, y/len};
	}
	inline void Vector2::Normalize()
	{
		*this /= Length();
	}
	inline Vector2 Vector2::Rotate(const Vector2 vec, float angle) //rotate
	{
		float x = vec.x * std::cos(angle) - vec.y * std::sin(angle);
		float y = vec.x * std::sin(angle) + vec.y * std::cos(angle);

		return Vector2{ x, y };
	}
	inline float Vector2::Dot(const Vector2& v)
	{
		return x * v.x + y * v.y;
	}
	inline float Vector2::GetAngleBetween(const Vector2& v)
	{
		return std::acos(Dot(v));
	}
	inline float Vector2::GetSignedAngleBetween(const Vector2& v)
	{
		float y = x * v.y - y * v.x; // perpendicular dot product 
		float x = x * v.x + y * v.y; // dor product 

		return std::atan2(y, x);
	}

}