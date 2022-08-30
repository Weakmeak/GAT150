#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace digi {
	void digi::SpriteAnimComponent::Draw(Renderer& ren)
	{
		ren.Draw(m_tex, GetSource(), m_owner->GetTransform(), registration, flipHorizontal);
	}

	void digi::SpriteAnimComponent::Update()
	{
		//update frame
		frameTimer += g_Time.deltaTime;
		if (frameTimer >= 1.0f / fps)
		{
			frameTimer = 0;
			frame++;
			if (frame > end_frame)
			{
				frame = start_frame;
			}
		}

		//calculate source
		Vector2 cellSize = m_tex->GetSize() / Vector2{ num_columns, num_rows };

		int column = (frame - 1) % num_columns;
		int row = (frame - 1) / num_columns;

		source.x = (int)(column * cellSize.x);
		source.y = (int)(row * cellSize.y);
		source.w = (int)(cellSize.x);
		source.h = (int)(cellSize.y);
	}

	bool digi::SpriteAnimComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool digi::SpriteAnimComponent::Read(const rapidjson::Value& value)
	{
		string sprite_name;
		READ_DATA(value, sprite_name);

		m_tex = g_Resource.Get<Texture>(sprite_name, g_Ren);

		READ_DATA(value, fps);
		READ_DATA(value, num_rows);
		READ_DATA(value, num_columns);
		READ_DATA(value, start_frame);
		READ_DATA(value, end_frame);

		return true;
	}

	Rect& SpriteAnimComponent::GetSource()
	{
		// calculate source rect 
		Vector2 cellSize = m_tex->GetSize() / Vector2{ num_columns, num_rows };

		int column = (frame - 1) % num_columns;
		int row = (frame - 1) / num_columns;

		source.x = (int)(column * cellSize.x);
		source.y = (int)(row * cellSize.y);
		source.w = (int)(cellSize.x);
		source.h = (int)(cellSize.y);

		return source;
	}
}
