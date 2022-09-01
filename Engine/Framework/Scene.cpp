#include "Scene.h"
#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Framework/Factory.h"


namespace digi {
	void Scene::Update()
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			(*iter)->Update();
			if ((*iter)->destroyed) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}
	void Scene::Initialize()
	{
		for (auto& act : m_actors) { act->Initialize(); }
	}
	void Scene::Draw(Renderer& ren)
	{
		for (auto& act : m_actors) {
			if (act->isActive()) act->Draw(ren);
		}
	}
	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}
	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
	bool Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray()) {
			return false;
		}
		
		//read actors
		for (auto& actVal : value["actors"].GetArray()) {
			std::string type;
			READ_DATA(actVal, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor) {
				actor->Read(actVal);

				bool prefab = false;
				READ_DATA(actVal, prefab);

				if (prefab) {
					std::string temp = actor->GetName();
					Factory::Instance().RegisterPrefab(temp, std::move(actor));
				}
				else {
					Add(std::move(actor));
				}
			}
		}
		return true;
	}
}
