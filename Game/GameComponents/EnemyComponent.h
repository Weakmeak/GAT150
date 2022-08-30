#pragma once
#include "Components/CharacterComponent.h"

class EnemyComponent : public digi::CharacterComponent
{
		public:
			CLASS_DECLARATION(EnemyComponent)

			virtual void Initialize() override;
			virtual void Update() override;

			virtual void OnCollisionEnter(digi::Actor* other) override;
			virtual void OnCollisionExit(digi::Actor* other) override;

			virtual void OnNotify(const digi::Event& event) override;

			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;

		protected:
			float damage = 1;
};