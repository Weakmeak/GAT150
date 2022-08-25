#pragma once 
#include "Math/Vector2.h" 
#include "Resource/Resource.h"
#include <string> 

// !! forward declaration for SDL pointers below (SDL likes to use structs) 
struct SDL_Texture;
struct SDL_Surface;
// !! add namespace 
namespace digi{
// !! forward declaration for Renderer below 
	class Renderer;
	class Texture : public Resource
	{
		public:
			Texture() = default;
			~Texture();


			bool Create(Renderer& renderer, const std::string& filename);
			bool Create(std::string filename, ...) override;
			bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

			Vector2 GetSize() const;

			// !! allow Renderer to access private texture data (friend) 
			friend class Renderer;
		private:
			SDL_Texture* m_texture = nullptr;
	};
}