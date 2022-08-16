#include "Font.h" 
#include <SDL_ttf.h> 

namespace digi
{
	Font::Font(const std::string& filename, int fontSize)
	{
		// !! call Load() function below passing filename and fontSize 
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		// !! if m_ttfFont not null, close font (TTF_CloseFont) 
		if (m_ttfFont != NULL) {
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Create(std::string filename, ...)
	{
		// va_list - type to hold information about variable arguments 
		va_list args;

		// va_start - enables access to variadic function arguments 
		va_start(args, filename);

		// va_arg - accesses the next variadic function arguments 
		int size = va_arg(args, int);

		// va_end - ends traversal of the variadic function arguments 
		va_end(args);

		// create texture (returns true/false if successful) 
		return Create(filename, size);
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		// !! call TTF_OpenFont  
		// !! use filename.c_str() to get the c-style string 
		// !! assign the return value of TTF_OpenFont to m_ttfFont 
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	}
}