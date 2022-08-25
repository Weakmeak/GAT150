#pragma once
#include "Framework/Component.h"

namespace digi {
	class PhysicsComponent : public Component {
		public:
			PhysicsComponent() = default;

			void Update() override;
			virtual void ApplyForce(const Vector2& force) { Accel += force; };
			
			CLASS_DECLARATION(PhysicsComponent);

			// Inherited via Component
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;

		public:
			Vector2 Velocity;
			Vector2 Accel;
			float damping = 1;



	};
}
