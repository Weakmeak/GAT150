#include "PhysicsComponent.h"
#include "Engine.h"

namespace digi {
	void PhysicsComponent::Update()
	{
		Velocity += Accel * g_Time.deltaTime;
		m_owner->GetTransform().position += Velocity * g_Time.deltaTime;
		Velocity *= damping;
		Accel = Vector2::zero;
	}
	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, damping);
		READ_DATA(value, Accel);
		READ_DATA(value, Velocity);
		return true;
	}
}
