#pragma once
#include "GameObject.h"
#include "Serial/Serializable.h"

namespace digi {
	class Actor; 
	class Component : public GameObject, public ISerializable {
		public:
			Component() = default;
			friend class Actor;

			virtual void Update() = 0;
			virtual void Initialize() override {};
		protected:
			Actor* m_owner = nullptr;
	};
}