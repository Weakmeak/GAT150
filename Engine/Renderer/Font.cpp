#include "Font.h" 
#include "Core/Logger.h"
#include "Math/Color.h"
#include <SDL_ttf.h>

namespace digi
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont) {
			TTF_CloseFont(m_ttfFont);
			m_ttfFont = nullptr;
		}
	}

	bool Font::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);
		int size = va_arg(args, int);
		va_end(args);

		return Create(filename, size);
	}

	bool Font::Create(std::string filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);

		return (m_ttfFont != NULL);
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
	{
		SDL_Color c = (*(SDL_Color*)(&color));
		SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);

		if (!surface)
		{
			LOG(SDL_GetError());
		}

		return surface;
	}
}