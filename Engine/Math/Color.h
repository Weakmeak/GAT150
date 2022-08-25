#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>
//#include <SDL.h>

namespace digi {

	//typedef unsigned char u8_t; These two lines accomplish the same thing
	//using u8_t = unsigned char;

	struct Color {
		uint8_t r, g, b, a;

		/*Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } {}
		Color() {};*/

		static const Color white;
		static const Color black;

		friend std::istream& operator >> (std::istream& stream, Color& color);
		friend std::ostream& operator << (std::ostream& stream, const Color& color);

		uint8_t operator [] (size_t index) const { return (&r)[index]; }
		uint8_t& operator [] (size_t index) { return (&r)[index]; }

		/*operator SDL_Color() const {
			SDL_Color c;
			c.r = (Uint8)r;
			c.g = (Uint8)g;
			c.b = (Uint8)b;
			c.a = (Uint8)a;

			return c;
		}*/
	};

	std::istream& operator >> (std::istream& stream, Color& out);

}