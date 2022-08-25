#pragma once
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include "Texture.h"

struct SDL_Renderer;	//Forward Declaration, we're coming back to this later
struct SDL_Window;

namespace digi {

	struct Transform;
	struct Rect;
	class Renderer {
		public:
			Renderer() = default;
			~Renderer() = default;

			void Initialize();
			void Shutdown();

			void CreateWindow(int width, int height, const char* name);
			void BeginFrame();
			void EndFrame();
			inline void setClearColor(const Color& col) { m_clearColor = col; };

			void drawLine(float x1, float y1, float x2, float y2, const Color& col);
			void drawLine(const Vector2& vec1, const Vector2& vec2, const Color& col);
			void drawPoint(float x, float y, const Color& col);
			void drawPoint(const Vector2& vec, const Color& col);

			void Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle = 0, const Vector2& scale = 1, const Vector2& registration = 0.5);
			void Draw(std::shared_ptr<Texture> texture, const Transform& trans, const Vector2& registration = 0.5);
			void Draw(std::shared_ptr<Texture> texture, const Rect& rect, const Transform& trans, const Vector2& registration = 0.5);


			int getWindowWidth() { return m_width; }
			int getWindowHeight() { return m_height; }

			friend class Text;
			friend class Texture;

		private:

			int m_width = 0;
			int m_height = 0;
			Color m_clearColor = Color{0,0,0,255};

			SDL_Renderer* m_renderer{ nullptr };
			SDL_Window* m_window{ nullptr };
	};

}