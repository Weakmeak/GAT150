#pragma once 
#include "Math/Vector2.h" 
#include "Resource/Resource.h"
#include <string> 

// !! forward declaration for SDL pointers below (SDL likes to use structs) 
struct SDL_Texture;;
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

			Vector2 GetSize() const;

			// !! allow Renderer to access private texture data (friend) 
			friend class Renderer;
		private:
			SDL_Texture* m_texture = nullptr;
	};
}