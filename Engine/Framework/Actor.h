#pragma once

#include "GameObject.h"
#include <vector>
#include "Framework/Component.h"
#include "Math/Transform.h"
#include "Serial/Serializable.h"

using namespace std;

namespace digi {

	class Scene;
	class Renderer;

	class Actor : public GameObject, public ISerializable {
		public:
			Actor() = default;
			Actor(const Actor& other);
			Actor(const Transform& trnsf) { m_trans = trnsf; }
			~Actor() = default;

			CLASS_DECLARATION(Actor);

			virtual void Update() override;
			virtual void Initialize() override;
			virtual void Draw(Renderer ren);

			void addComponent(unique_ptr<Component> component);

			float GetRadius() { return 0; }; // m_model.GetRadius()* std::max(m_trans.scale.x, m_trans.scale.y);
			const std::string& GetTag() { return tag; };
			void SetTag(const std::string& t) { tag = t; };

			const std::string& GetName() { return name; };
			void SetName(const std::string& n) { name = n; };

			virtual void OnCollision(Actor* other) {};
			Transform& GetTransform() { return m_trans; }

			void AddChild(unique_ptr<Actor> child);

			template<typename T>
			T* GetComponent();

			// Inherited via ISerializable
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;

			friend class Scene;

		protected:
			bool destroyed = false;

			Transform m_trans;
			std::string tag = "";
			std::string name;
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
