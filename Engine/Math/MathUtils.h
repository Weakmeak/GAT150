#pragma once
#include <cmath>
//#ifndef __MATHUTILS_H__
//#define __MATHUTILS_H__

namespace Math {
	constexpr float Pi = 3.14159265359f;

	inline float DegToRad(float degrees) { return (float)((degrees / 180) * 3.1415926535); }
	inline float RadToDeg(float radians) { return (float)((radians / 3.1415926535) * 180); }

	template <typename T>
	T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}
	template <typename T>
	T Lerp(T min, T max, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return min + ((max - min) * t);
	}
	template <typename T>
	T Normalize(T value, T min, T max)
	{
		return (value - min) / (max - min);
	}
	template <typename T>
	T Remap(T value, T inMin, T inMax, T outMin, T outMax)
	{
		return Lerp(outMin, outMax, Normalize(value, inMin, inMax));
	}

	template <typename T>
	T mod(T numerator, T denominator)
	{
		return std::fmod(numerator, denominator);
	}

	template <>
	inline int mod(int numerator, int denominator)
	{
		return numerator % denominator;
	}

	template <typename T>
	T Wrap(T value, T min, T max)
	{
		if (value < min) return max - mod((min - value), (max - min));
		if (value > max) return min + mod((value - min), (max - min));

		return value;
	}
}

//#endif