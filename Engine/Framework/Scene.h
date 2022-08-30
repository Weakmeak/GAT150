#pragma once
#include <list>
#include <memory>
#include "Serial/Serializable.h"
#include "Game.h"
#include "Actor.h"

namespace digi {

	//class Actor; //forward declaration
	class Renderer; //forward declaration
	class Game;

	class Scene : public ISerializable, public GameObject{
		public:
			Scene() = default;
			Scene(Game* game) { m_game = game; }
			~Scene() = default;
			Scene(const Scene& other) {};

			CLASS_DECLARATION(Scene);

			void Update() override;
			void Initialize() override;
			void Draw(Renderer& ren);

			void Add(std::unique_ptr<Actor> actor);
			void RemoveAll();

			template<typename T>
			T* GetActor();
			
			Game* GetGame() { return m_game; }

			template<typename T = Actor>
			T* GetActorFromName(const std::string& name);

			template<typename T = Actor>
			std::vector<T*> GetActorsFromTag(const std::string& tag);

			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;
		private:
			std::list<std::unique_ptr<Actor>> m_actors;
			Game* m_game = nullptr;
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors) {
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorFromName(const std::string & name)
	{
		for (auto& act : m_actors)
		{
			if (name == act.GetName())
			{
				return dynamic_cast<T*>(act.get());
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsFromTag(const std::string& tag)
	{
		std::vector<T*> result;

		for (auto& act : m_actors) 
		{
			if (act->GetTag() == tag )
			{
				T * tagActor = dynamic_cast<T*>(act.get()); 
				if (tagActor) result.push_back(tagActor);
			}
		}

		return result;
	}
}