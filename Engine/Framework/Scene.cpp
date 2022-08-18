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

		//check collide
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) 
		{
			for (auto iter2 = m_actors.begin(); iter2 != m_actors.end(); iter2++) 
			{
				if (iter1 == iter2) continue;

				float rad = (*iter1)->GetRadius() + (*iter2)->GetRadius();
				float dist = (*iter1)->m_trans.position.Distance((*iter2)->m_trans.position);

				if (dist < rad) { //collision!
					//std::cout << "Collision!" << std::endl;

					(*iter1)->OnCollision((*iter2).get());
					(*iter2)->OnCollision((*iter1).get());
				}
			}
		}
	}
	void Scene::Draw(Renderer& ren)
	{
		for (auto& act : m_actors) {
			act->Draw(ren);
		}
	}
	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
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
				Add(std::move(actor));
			}
		}
		return true;
	}
}
