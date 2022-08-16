#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"
#include <vector>
#include <string>
namespace digi {
	class Model : public Resource
	{
		public:
			Model() = default;
			Model(const std::vector<Vector2>& points, const Color& color) : m_points{ points }, m_color{ color } {};
			Model(const std::string& filename);
			
			bool Create(std::string filename, ...) override;

			bool Load(const std::string& filename);
			void Draw(Renderer& ren, const Vector2& position, float angle, const Vector2& scale = 1);
			void Draw(Renderer& ren, const Transform& trans);
			float GetRadius() { return m_radius; };
			void SetRadius(float rad) { m_radius = rad; };
			void SetRadius() { m_radius = calcRadius(); };
			float calcRadius();

		private:
			std::vector<Vector2> m_points;
			Color m_color = Color::black;
			float m_radius = 0.5;
	};
}