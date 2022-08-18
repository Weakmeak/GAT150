#include "PhysicsComponent.h"
#include "Engine.h"

namespace digi {
	void PhysicsComponent::Update()
	{
		m_velocity += m_Accel * g_Time.deltaTime;
		m_owner->GetTransform().position += m_velocity * g_Time.deltaTime;
		m_velocity *= m_damp;
		m_Accel = Vector2::zero;
	}
	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		return false;
	}
}
