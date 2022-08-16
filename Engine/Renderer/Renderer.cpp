#include "Renderer.h" 
#include "Math/Transform.h"
#include <SDL.h> 
#include <SDL_ttf.h> 
#include <SDL_image.h>

namespace digi
{
	SDL_Renderer* renderer{ nullptr };
	SDL_Window* window{ nullptr };

	void Renderer::CreateWindow(int width, int height, const char* name)
	{
		m_width = width;
		m_height = height;

		m_window = SDL_CreateWindow(name, 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColor(m_renderer, m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::drawLine(float x1, float y1, float x2, float y2, const Color& col)
	{
		SDL_SetRenderDrawColor(m_renderer, col.r, col.g, col.b, col.a);
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::drawLine(const Vector2& vec1, const Vector2& vec2, const Color& col)
	{
		SDL_SetRenderDrawColor(m_renderer, col.r, col.g, col.b, col.a);
		SDL_RenderDrawLineF(m_renderer, vec1.x, vec1.y, vec2.x, vec2.y);
	}

	void Renderer::drawPoint(float x, float y, const Color& col)
	{
		SDL_SetRenderDrawColor(m_renderer, col.r, col.g, col.b, col.a);
		SDL_RenderDrawPoint(m_renderer, (int)x, (int)y);
	}

	void Renderer::drawPoint(const Vector2& vec, const Color& col)
	{
		SDL_SetRenderDrawColor(m_renderer, col.r, col.g, col.b, col.a);
		SDL_RenderDrawPoint(m_renderer, (int)vec.x, (int)vec.y);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle, const Vector2& scale, const Vector2& registration)
	{
		Vector2 size = texture->GetSize();
		size *= scale;

		Vector2 origin = size * registration;
		Vector2 tPos = position - origin;

		SDL_Rect dest;
		// !! make sure to cast to int to prevent compiler warnings 
		dest.x = (int)tPos.x;
		dest.y = (int)tPos.y;
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{(int)origin.x, (int)origin.y};

		SDL_RenderCopyEx(m_renderer, texture -> m_texture, nullptr, &dest, angle, &center, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Transform& trans, const Vector2& registration)
	{
		Vector2 size = texture->GetSize();
		size *= trans.scale;

		Vector2 origin = size * registration;
		Vector2 tPos = trans.position - origin;

		SDL_Rect dest;
		// !! make sure to cast to int to prevent compiler warnings 
		dest.x = (int)tPos.x;
		dest.y = (int)tPos.y;
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, trans.rotation, &center, SDL_FLIP_NONE);
	}

	void Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();
	}

	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		IMG_Quit();
		TTF_Quit();
	}
}