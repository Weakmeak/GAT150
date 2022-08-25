#include "rbPhysicsComponent.h"
#include "Engine.h"

namespace digi {
	rbPhysicsComponent::~rbPhysicsComponent()
	{
		if(m_body) g_Physics.DestroyBody(m_body);
	}
	void rbPhysicsComponent::Update()
	{
		Vector2 pos = B2VEC2_TO_VECTOR2(m_body->GetPosition());
		m_owner->GetTransform().position = PhysicsSystem::WorldToScreen(pos);
		m_owner->GetTransform().rotation = m_body->GetAngle();

	}
	void rbPhysicsComponent::Initialize()
	{
		m_body = g_Physics.CreateBody(m_owner->GetTransform().position, m_owner->GetTransform().rotation, data);
		m_body->SetGravityScale(data.gravity_scale);
		m_body->SetLinearDamping(damping);
	}
	void rbPhysicsComponent::ApplyForce(const Vector2& force)
	{
		m_body->ApplyForceToCenter(VECTOR2_TO_B2VEC2(force), true);
	}
	bool rbPhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool rbPhysicsComponent::Read(const rapidjson::Value& value)
	{
		PhysicsComponent::Read(value);
		READ_DATA(value, data.gravity_scale);
		READ_DATA(value, data.constrain_angle);
		READ_DATA(value, data.is_dynamic);
		return true;
	}
}
