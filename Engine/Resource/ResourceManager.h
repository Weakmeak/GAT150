#pragma once
#include "Resource.h"
#include <map>
#include <string>
#include <memory>

namespace digi {

	class ResourceManager {
		public:
			ResourceManager() = default;

			void Initialize();
			void Shutdown();

			template<typename T, typename ... TArgs>
			std::shared_ptr<T> Get(const std::string& key, TArgs... args);

		private:
			std::map<std::string, std::shared_ptr<Resource>> m_Resources;
	};

	template<typename T, typename ... TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& key, TArgs... args) {
		if (m_Resources.find(key) != m_Resources.end()) {
			//found
			return std::dynamic_pointer_cast<T>(m_Resources[key]);
		}
		else {
			std::shared_ptr<T> resource = std::make_shared<T>();
			resource->Create(key, args...);
			m_Resources[key] = resource;

			return resource;
		}
	}
}