#pragma once
#include "Math//Vector2.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

namespace digi {
	struct Matrix3x3 {
		Vector3 rows[3];

		Matrix3x3() = default;
		Matrix3x3(const Vector3& row1, const Vector3& row2, const Vector3& row3);

		Vector3 operator [] (size_t index) const { return rows[index]; }
		Vector3& operator [] (size_t index) { return rows[index]; }

		Vector2 operator * (const Vector2& v) const;
		Matrix3x3 operator * (const Matrix3x3& mx) const;

		static Matrix3x3 CreateScale(const Vector2& scale);
		static Matrix3x3 CreateScale(float scale);
		static Matrix3x3 CreateScale(float scaleX, float scaleY);
		static Matrix3x3 CreateRotation(float radians);
		static Matrix3x3 CreateTranslation(const Vector2& trans);

		Vector2 GetTranslation() const;
		float GetRotation() const;
		Vector2 GetScale() const;

		static const Matrix3x3 identity;
		static const Matrix3x3 zero;
	};

	inline Matrix3x3::Matrix3x3(const Vector3& row1, const Vector3& row2, const Vector3& row3) {
		rows[0] = row1;
		rows[1] = row2;
		rows[2] = row3;
	}
	inline Vector2 Matrix3x3::operator*(const Vector2& v) const
	{
		Vector2 temp;

		temp[0] = (v.x * rows[0][0]) + (v.y * rows[0][1]) + rows[0][2];
		temp[1] = (v.x * rows[1][0]) + (v.y * rows[1][1]) + rows[1][2];

		return temp;
	}
	inline Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mx) const
	{
		Matrix3x3 temp;

		temp[0][0] = (rows[0][0] * mx[0][0]) + (rows[0][1] * mx[1][0]) + (rows[0][2] * mx[2][0]); //row 1 * col 1 
		temp[0][1] = (rows[0][0] * mx[0][1]) + (rows[0][1] * mx[1][1]) + (rows[0][2] * mx[2][1]); //row 1 * col 2
		temp[0][2] = (rows[0][0] * mx[0][2]) + (rows[0][1] * mx[1][2]) + (rows[0][2] * mx[2][2]); //row 1 * col 3

		temp[1][0] = (rows[1][0] * mx[0][0]) + (rows[1][1] * mx[1][0]) + (rows[1][2] * mx[2][0]); //row 2 * col 1
		temp[1][1] = (rows[1][0] * mx[0][1]) + (rows[1][1] * mx[1][1]) + (rows[1][2] * mx[2][1]); //row 2 * col 2
		temp[1][2] = (rows[1][0] * mx[0][2]) + (rows[1][1] * mx[1][2]) + (rows[1][2] * mx[2][2]); //row 2 * col 3

		temp[2][0] = (rows[2][0] * mx[0][0]) + (rows[2][1] * mx[1][0]) + (rows[2][2] * mx[2][0]); //row 3 * col 1
		temp[2][1] = (rows[2][0] * mx[0][1]) + (rows[2][1] * mx[1][1]) + (rows[2][2] * mx[2][1]); //row 3 * col 2
		temp[2][2] = (rows[2][0] * mx[0][2]) + (rows[2][1] * mx[1][2]) + (rows[2][2] * mx[2][2]); //row 3 * col 3

		return temp;
	}
	inline Matrix3x3 Matrix3x3::CreateScale(const Vector2& scale)
	{
		Matrix3x3 mx;

		mx[0] = Vector3{ scale.x, 0.0,	0.0 };
		mx[1] = Vector3{ 0.0,	scale.y,	0.0 };
		mx[2] = Vector3{ 0.0,	0.0,	1.0f };

		return mx;
	}
	inline Matrix3x3 Matrix3x3::CreateScale(float scale)
	{
		Matrix3x3 mx;

		mx[0] = Vector3{ scale, 0.0,	0.0 };
		mx[1] = Vector3{ 0.0,	scale,	0.0 };
		mx[2] = Vector3{ 0.0,	0.0,	1.0f};

		return mx;
	}
	inline Matrix3x3 Matrix3x3::CreateScale(float scaleX, float scaleY)
	{
		Matrix3x3 mx;

		mx[0] = Vector3{ scaleX, 0.0,	0.0 };
		mx[1] = Vector3{ 0.0,	scaleY,	0.0 };
		mx[2] = Vector3{ 0.0,	0.0,	1.0f };

		return mx;
	}
	inline Matrix3x3 Matrix3x3::CreateRotation(float radians)
	{
		Matrix3x3 mx;
		mx[0] = Vector3{ std::cos(radians),		-std::sin(radians),		0.0f };
		mx[1] = Vector3{ std::sin(radians),		std::cos(radians),		0.0f };
		mx[2] = Vector3{ 0.0f,					0.0f,					0.0f };

		return mx;
	}
	inline Matrix3x3 Matrix3x3::CreateTranslation(const Vector2& trans)
	{
		Matrix3x3 temp = Matrix3x3::identity;

		temp[0][2] = trans.x;
		temp[1][2] = trans.y;


		return temp;
	}
	inline Vector2 Matrix3x3::GetTranslation() const
	{
		// 1 0 x 
		// 0 1 y 
		// 0 0 1 

		return { rows[0][2], rows[1][2] };
	}
	inline float Matrix3x3::GetRotation() const
	{
		// cos -sin 0 
		// sin  cos 0 
		//  0    0  1 

		// y = sin(angle) = rows[1][0] 
		// x = cos(angle) = rows[0][0] 

		return std::atan2(rows[1][0], rows[0][0]);
	}
	inline Vector2 Matrix3x3::GetScale() const
	{
		Vector2 x = { rows[0][0], rows[0][1] };
		Vector2 y = { rows[1][0], rows[1][1] };

		return { x.Length(), y.Length() };
	}
}