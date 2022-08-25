#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"

namespace digi {
	class PlayerComponent : public Component, public iCollision {
		public:
			PlayerComponent() = default;

			void Initialize() override;
			void Update() override;

			CLASS_DECLARATION(PlayerComponent);

			// Inherited via Component
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;
			
			// Inherited via iCollision
			virtual void OnCollisionEnter(Actor* other) override;
			virtual void OnCollisionExit(Actor* other) override;

		private:
			float speed = 300;

	};
}