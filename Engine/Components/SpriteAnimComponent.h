#pragma once
#include "RendererComponent.h"
#include "Math/Rect.h"

namespace digi {
	class Texture;
	class SpriteAnimComponent : public RendererComponent {
	public:
		void Draw(Renderer& ren) override;
		void Update() override;

		CLASS_DECLARATION(SpriteAnimComponent);

		Rect& GetSource() override;

		// Inherited via RendererComponnent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	public:

		float fps = 0;
		int num_columns = 0;
		int num_rows = 0;
		int start_frame = 0;
		int end_frame = 0;

		int frame = 0;
		float frameTimer = 0;

		Rect source;
		std::shared_ptr<Texture> m_tex;

	};
}