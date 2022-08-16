#pragma once
#include "Math//Vector2.h"
namespace digi {
	struct Matrix2x2 {
		Vector2 rows[2];

		Matrix2x2() = default;
		Matrix2x2(const Vector2& row1, const Vector2& row2);

		Vector2 operator [] (size_t index) const { return rows[index]; }
		Vector2& operator [] (size_t index) { return rows[index]; }

		Vector2 operator * (const Vector2& v);
		Matrix2x2 operator * (const Matrix2x2& mx);

		static Matrix2x2 CreateScale(const Vector2& scale);
		static Matrix2x2 CreateScale(float scale);
		static Matrix2x2 CreateScale(float scalex, float scaley);
		static Matrix2x2 CreateRotation(float radians);

		static const Matrix2x2 identity;
		static const Matrix2x2 zero;
	};

	inline Matrix2x2::Matrix2x2(const Vector2& row1, const Vector2& row2) {
		rows[0] = row1;
		rows[1] = row2;
	}
	inline Vector2 Matrix2x2::operator*(const Vector2& v)
	{
		Vector2 temp;

		temp[0] = (v.x * rows[0][0]) + (v.y * rows[0][1]);
		temp[1] = (v.x * rows[1][0]) + (v.y * rows[1][1]);

		return temp;
	}
	inline Matrix2x2 Matrix2x2::operator*(const Matrix2x2& mx)
	{
		Matrix2x2 temp;
		temp[0][0] = (rows[0][0] * mx[0][0]) + (rows[0][1] * mx[1][0]);
		temp[0][1] = (rows[0][0] * mx[0][1]) + (rows[0][1] * mx[1][1]);
		temp[1][0] = (rows[1][0] * mx[0][0]) + (rows[1][1] * mx[1][0]);
		temp[1][1] = (rows[1][0] * mx[0][1]) + (rows[1][1] * mx[1][1]);
		return temp;
	}
	inline Matrix2x2 Matrix2x2::CreateScale(const Vector2& scale)
	{
		Matrix2x2 mx;
		mx[0] = Vector2{ scale[0], 0.0 };
		mx[1] = Vector2{ 0.0, scale[1]};

		return mx;
	}
	inline Matrix2x2 Matrix2x2::CreateScale(float scale)
	{
		Matrix2x2 mx;
		mx[0] = Vector2{ scale, 0.0 };
		mx[1] = Vector2{ 0.0, scale };

		return mx;
	}
	inline Matrix2x2 Matrix2x2::CreateScale(float scalex, float scaley)
	{
		Matrix2x2 mx;
		mx[0] = Vector2{ scalex, 0.0 };
		mx[1] = Vector2{ 0.0, scaley };

		return mx;
	}
	inline Matrix2x2 Matrix2x2::CreateRotation(float radians)
	{
		Matrix2x2 mx;
		mx[0] = Vector2{ std::cos(radians), -std::sin(radians)};
		mx[1] = Vector2{ std::sin(radians), std::cos(radians)};

		return mx;
	}
}