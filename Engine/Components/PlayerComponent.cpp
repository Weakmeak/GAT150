#include "PlayerComponent.h"
#include "Engine.h"
#include "Input/InputSystem.h"

namespace digi {
	void PlayerComponent::Update()
	{
		if (m_owner->GetTransform().position.x > digi::g_Ren.getWindowWidth()) { m_owner->GetTransform().position.x = 0; }
		if (m_owner->GetTransform().position.x < 0) { m_owner->GetTransform().position.x = (float)digi::g_Ren.getWindowWidth(); }
		if (m_owner->GetTransform().position.y > digi::g_Ren.getWindowHeight()) { m_owner->GetTransform().position.y = 0; }
		if (m_owner->GetTransform().position.y < 0) { m_owner->GetTransform().position.y = (float)digi::g_Ren.getWindowHeight(); }

		Vector2 temp(0);

		if (g_Input.GetKeyDown(key_left))
		{
			temp.x -= speed * g_Time.deltaTime;
		}
		if (g_Input.GetKeyDown(key_right))
		{
			temp.x += speed * g_Time.deltaTime;
		}
		if (g_Input.GetKeyDown(key_up))
		{
			temp.y -= speed * g_Time.deltaTime;
		}
		if (g_Input.GetKeyDown(key_down))
		{
			temp.y += speed * g_Time.deltaTime;
		}
		
		/*
		Vector2 force{ h_thrust, v_thrust };
		force *= 1.0f / (1.0f + (m_damping * g_Time.deltaTime));
		m_velocity += force;*/
		m_owner->GetTransform().position += temp;

		Vector2 target = g_Input.GetMousePosition();
		target -= m_owner->GetTransform().position;
		m_owner->GetTransform().rotation = Math::RadToDeg(target.GetAngle());

		/*if (g_Input.GetButtonState(key_space) == InputSystem::Pressed) {
			AudioComponent* temp = m_owner->GetComponent<AudioComponent>();
			if (temp) temp->Play();
		}*/
	}
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}
}
