#pragma once
#include "RendererComponent.h"
#include "Renderer/Model.h"

namespace digi {
	class Texture;
	class ModelComponent : public RendererComponnent {
	public:
		void Draw(Renderer& ren) override;
		void Update() override;
	public:
		std::shared_ptr<Model> m_verts;
	};
}