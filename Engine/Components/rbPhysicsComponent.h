#pragma once
#include "Components/PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace digi {
	class rbPhysicsComponent : public PhysicsComponent
	{
		public:
			rbPhysicsComponent() = default;
			~rbPhysicsComponent();

			CLASS_DECLARATION(rbPhysicsComponent);

			void Update() override;
			void Initialize() override;
			virtual void ApplyForce(const Vector2& force);

			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;
		
			friend class CollisionComponent;
		private:
			PhysicsSystem::RigidBodyData data;
			b2Body* m_body = nullptr;
	};






}