#include "Vector2.h"

namespace digi {
	const Vector2 Vector2::one = { 1,1 };
	const Vector2 Vector2::zero = { 0,0 };
	const Vector2 Vector2::up = { 0,-1 };
	const Vector2 Vector2::down = { 0,1 };
	const Vector2 Vector2::left = { -1,0 };
	const Vector2 Vector2::right = { 1,0 };

	std::istream& operator >> (std::istream& stream, Vector2& out)
	{
		std::string line;
		std::getline(stream, line);

		std::string xs = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		out.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
		out.y = std::stof(ys);

		return stream;
	}
}