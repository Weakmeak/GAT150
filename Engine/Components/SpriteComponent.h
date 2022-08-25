#pragma once
#include "RendererComponent.h"
#include "Math/Rect.h"

namespace digi {
	class Texture;
	class SpriteComponent : public RendererComponent {
		public :
			void Draw(Renderer& ren) override;
			void Update() override;
			
			CLASS_DECLARATION(SpriteComponent);

			// Inherited via RendererComponnent
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;
		public:
			Rect source;
			std::shared_ptr<Texture> m_tex;

	};
}