#pragma once
#include "RendererComponent.h"

namespace digi {
	class Texture;
	class SpriteComponent : public RendererComponnent {
		public :
			void Draw(Renderer& ren) override;
			void Update() override;
		public:
			std::shared_ptr<Texture> m_tex;
	};
}