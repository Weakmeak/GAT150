#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace digi {
	void SpriteComponent::Draw(Renderer& ren)
	{
		ren.Draw(m_tex, source, m_owner->GetTransform());
	}

	void SpriteComponent::Update()
	{
	}
	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		string sprite_name;
		READ_DATA(value, sprite_name);

		m_tex = g_Resource.Get<Texture>(sprite_name, g_Ren);

		if (!READ_DATA(value, source)) 
		{
			source.x = 0;
			source.y = 0;
			source.w = (int)m_tex->GetSize().x;
			source.h = (int)m_tex->GetSize().y;
		}
		return true;
	}
}
