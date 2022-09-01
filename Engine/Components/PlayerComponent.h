#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "CharacterComponent.h"

namespace digi {
	class PlayerComponent : public CharacterComponent {
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

			virtual void OnNotify(const Event& event) override;
			int life = 5;
		private:
			float speed = 300;

	};
}