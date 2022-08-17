#include "Color.h"

namespace digi {

	const Color Color::black = { 0,0,0,255 };
	const Color Color::white = { 255,255,255,255 };

	std::istream& operator >> (std::istream& stream, Color& out)
	{
		std::string line;
		std::getline(stream, line);

		std::string str;

		// red
		str = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		out.r = (uint8_t)(std::stof(str) * 255);

		// setting line to another sub section of the string to read green and blue 
		line = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);

		// line: #g, #b } 

		// green 
		str = line.substr(0, line.find(","));
		out.g = (uint8_t)(std::stof(str) * 255);

		// blue 
		str = line.substr(line.find(",") + 1);
		out.b = (uint8_t)(std::stof(str) * 255);

		// default alpha to 255 
		out.a = 255;

		return stream;
	}
	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		stream << (int)color.r << " " << (int)color.g << " " << (int)color.b << " " << (int)color.a;

		return stream;
	}
}