#pragma once
#include "GameObject.h"

namespace digi {
	class Actor; 
	class Component : public GameObject {
		public:
			Component() = default;
			friend class Actor;

			virtual void Update() = 0;
		protected:
			Actor* m_owner = nullptr;
	};
}