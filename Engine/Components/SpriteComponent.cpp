#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace digi {
	void SpriteComponent::Draw(Renderer& ren)
	{
		ren.Draw(m_tex, m_owner->GetTransform());
	}

	void SpriteComponent::Update()
	{
	}
}
