#pragma once
#include "Framework/Component.h"

namespace digi {
	class PhysicsComponent : public Component {
		public:
			PhysicsComponent() = default;

			void Update() override;
			void ApplyForce(const Vector2& force) { m_Accel += force; };
			
			// Inherited via Component
			virtual bool Write(const rapidjson::Value& value) const override;

			virtual bool Read(const rapidjson::Value& value) override;

		public:
			Vector2 m_velocity;
			Vector2 m_Accel;
			float m_damp = 1;



	};
}
