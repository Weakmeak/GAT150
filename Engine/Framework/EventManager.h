#pragma once
#include <map>
#include <list>
#include "Event.h"
namespace digi {
	class EventManager {
		public:
			struct Observer {
				GameObject* receiver;
				Event::FunctPtr function;

			};
		public:
			void Initialize();
			void Shutdown();
			void Update();

			void Subscribe(const std::string& name, Event::FunctPtr function, GameObject* receiver = nullptr);
			void Unsubscribe(const std::string& name, GameObject* receiver);
			void Notify(const Event& eve);
		private:
			std::map<std::string, std::list<Observer>> m_events;
	};
}
