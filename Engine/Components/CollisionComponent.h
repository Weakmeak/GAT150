#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace digi {
	class CollisionComponent : public Component, public iCollision{
		public:
			using funcPtr = std::function<void(Actor*)>;
		public:

			CLASS_DECLARATION(CollisionComponent);

			virtual void Initialize() override;
			// Inherited via iCollision
			virtual void OnCollisionEnter(Actor* other) override;
			virtual void OnCollisionExit(Actor* other) override;

			void setCollisionEnter(funcPtr function) { m_enterFunction = function; };
			void setCollisionExit(funcPtr function) { m_exitFunction = function; };

			// Inherited via Component
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;
			virtual void Update() override;
		private:
			PhysicsSystem::CollisionData data;
			funcPtr m_enterFunction;
			funcPtr m_exitFunction;

	};
}