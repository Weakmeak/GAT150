#include "PlayerComponent.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include <iostream>


namespace digi {
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();

		g_Sound.AddAudio("audio/ouch.wav", "audio/ouch.wav");
		g_Sound.AddAudio("audio/coin.wav", "audio/coin.wav");
	}
	void PlayerComponent::Update()
	{
		if (m_owner->GetTransform().position.x > digi::g_Ren.getWindowWidth()) { m_owner->GetTransform().position.x = 0; }
		if (m_owner->GetTransform().position.x < 0) { m_owner->GetTransform().position.x = (float)digi::g_Ren.getWindowWidth(); }
		if (m_owner->GetTransform().position.y > digi::g_Ren.getWindowHeight()) { m_owner->GetTransform().position.y = 0; }
		if (m_owner->GetTransform().position.y < 0) { m_owner->GetTransform().position.y = (float)digi::g_Ren.getWindowHeight(); }

		Vector2 temp(0);

		if (g_Input.GetKeyDown(key_left))
		{
			temp.x -= speed;
		}
		if (g_Input.GetKeyDown(key_right))
		{
			temp.x += speed;
		}
		if (g_Input.GetKeyDown(key_up))
		{
			temp.y -= speed;
		}
		if (g_Input.GetKeyDown(key_down))
		{
			temp.y += speed;
		}

		//std::cout << temp.x << " " << temp.y << std::endl;
		Vector2 velocity;
		auto physComp = m_owner->GetComponent<PhysicsComponent>();
		if (physComp) {
			physComp->ApplyForce(temp);
			velocity = physComp->Velocity;

		}
		else {
			m_owner->GetTransform().position += (temp * g_Time.deltaTime);
		}
		
		auto renderComp = m_owner->GetComponent<RendererComponent>();
		if (renderComp) {
			renderComp->setFlipHorizontal(!(velocity.x < 0));
		}

		Vector2 target = g_Input.GetMousePosition();
		target -= m_owner->GetTransform().position;
		m_owner->GetTransform().rotation = Math::RadToDeg(target.GetAngle());

		if (life <= 0) m_owner->SetDestroyed(true);
	}
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, speed);

		return true;
	}
	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetName() == "Coin") {
			Event eve;
			eve.name = "AddPoints";
			eve.data = 100;
			g_Events.Notify(eve);
			g_Sound.PlayAudio("audio/coin.wav");

			life += 2;
			other->SetDestroyed(true);

		}
		if (other->GetName() == "BadCoin") {
			g_Sound.PlayAudio("audio/ouch.wav");
			life *= 0.67;
			other->SetDestroyed(true);
		}
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		//
	}
	void PlayerComponent::OnNotify(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE") health -= std::get<float>(event.data);
		if (health <= 0) {
			// YOU ARE DEAD, DEAD, DEAD
		}
	}
}
