#include "Model.h"
#include "../Core/File.h"
#include "Math/Transform.h"
#include "Core/Logger.h"
#include <sstream>
#include <iostream>

namespace digi {
	Model::Model(const std::string& filename)
	{
		Load(filename);
	}

	void Model::Draw(Renderer& ren, const Vector2& position, float angle, const Vector2& scale)
	{
		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			Vector2 temp1 = Vector2::Rotate( (m_points[i] * scale), angle) + position;
			Vector2 temp2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;
			ren.drawLine(temp1, temp2, m_color);
		}
	}

	void Model::Draw(Renderer& ren, const Transform& trans)
	{
		Matrix3x3 mx = trans.matrix;
		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			Vector2 temp1 = mx * m_points[i];
			Vector2 temp2 = mx * m_points[i + 1];
			ren.drawLine(temp1, temp2, m_color);
		}
	}

	float Model::calcRadius()
	{
		float rad = 0;

		for (Vector2 point : m_points) {
			if (point.Length() > rad) {
				rad = point.Length();
			}
		}

		//std::cout << rad << std::endl;
		return rad;
	}

	bool Model::Create(std::string filename, ...)
	{
		if (!Load(filename))
		{
			LOG("YOU DONE MESSED UP A-A-RON!");
			return false;
		}
		return true;
	}

	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		if (!ReadFile(filename, buffer)) {
			LOG("ERROR: COULD NOT READ FILE: %s", filename.c_str());
			return false;
		}
		std::stringstream stream(buffer);

		stream >> m_color;

		std::string line;
		std::getline(stream, line);
		
		size_t numPoints = std::stoi(line);

		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}

		return true;
	}
}

