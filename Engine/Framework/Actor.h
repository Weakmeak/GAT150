#pragma once

#include "GameObject.h"
#include <vector>
#include "Framework/Component.h"

using namespace std;

namespace digi {

	class Scene;
	class Renderer;

	class Actor : public GameObject {
		public:
			Actor() = default;
			Actor(const Transform& trnsf) { m_trans = trnsf; }
			~Actor() = default;

			virtual void Update() override;
			virtual void Draw(Renderer ren);

			void addComponent(unique_ptr<Component> component);

			float GetRadius() { return 0; }; // m_model.GetRadius()* std::max(m_trans.scale.x, m_trans.scale.y);
			std::string GetTag() { return m_tag; };
			void SetTag(const std::string& tag) { m_tag = tag; };

			virtual void OnCollision(Actor* other) {};
			Transform& GetTransform() { return m_trans; }

			void AddChild(unique_ptr<Actor> child);

			template<typename T>
			T* GetComponent();

			friend class Scene;

		protected:
			bool destroyed = false;

			Transform m_trans;
			std::string m_tag = "";
			Scene* m_scene = nullptr;
			Actor* m_parent = nullptr;
			Vector2 m_velocity;
			float m_damping = 1;

			vector<unique_ptr<Component>> m_components;
			vector<unique_ptr<Actor>> m_children;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& comp : m_components) {
			T* result = dynamic_cast<T*>(comp.get());
			if (result) return result;
		}
		return nullptr;
	}
}
