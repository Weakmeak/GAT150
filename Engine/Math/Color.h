#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>

namespace digi {

	//typedef unsigned char u8_t; These two lines accomplish the same thing
	//using u8_t = unsigned char;

	struct Color {
		uint8_t r, g, b, a;

		static const Color white;
		static const Color black;

		friend std::istream& operator >> (std::istream& stream, Color& color);
	};

	std::istream& operator >> (std::istream& stream, Color& out);

}