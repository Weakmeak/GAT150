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

	class Scene : public ISerializable{
		public:
			Scene() = default;
			Scene(Game* game) { m_game = game; }
			~Scene() = default;

			void Update();
			void Draw(Renderer& ren);

			void Add(std::unique_ptr<Actor> actor);

			template<typename T>
			T* GetActor();
			
			Game* GetGame() { return m_game; }
		private:
			std::list<std::unique_ptr<Actor>> m_actors;
			Game* m_game = nullptr;

			// Inherited via ISerializable
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;
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
}