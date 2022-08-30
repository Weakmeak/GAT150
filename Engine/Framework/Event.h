#pragma once
#include <string>
#include <variant>
#include <functional>

namespace digi {

	class GameObject;
	class Event {
		public:
			using FunctPtr = std::function<void(const Event)>;
		public:
			std::string name;
			GameObject* receiver = nullptr;
			std::variant<int, bool, float, std::string> data;
	};
}