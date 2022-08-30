#include "EventManager.h"

namespace digi {
	void EventManager::Initialize()
	{
		//
	}

	void EventManager::Shutdown()
	{
		//
	}

	void EventManager::Update()
	{
		//
	}

	void EventManager::Subscribe(const std::string& name, Event::FunctPtr function, GameObject* receiver)
	{
		Observer obs;
		obs.receiver = receiver;
		obs.function = function;
		m_events[name].push_back(obs);
	}

	void EventManager::Unsubscribe(const std::string& name, GameObject* receiver)
	{
		//
	}

	void EventManager::Notify(const Event& eve)
	{
		auto observers = m_events[eve.name];
		for (auto& observer : observers)
		{
			if (eve.receiver == nullptr || eve.receiver == observer.receiver) {
				observer.function(eve);
			}
		}
	}
}
