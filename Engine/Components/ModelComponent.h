#pragma once
#include "RendererComponent.h"
#include "Renderer/Model.h"

namespace digi {
	class Texture;
	class ModelComponent : public RendererComponent {
	public:
		void Draw(Renderer& ren) override;
		void Update() override;
		
		// Inherited via RendererComponnent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Model> m_verts;
	};
}