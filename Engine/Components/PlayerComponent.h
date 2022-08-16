#pragma once
#include "Framework/Component.h"

namespace digi {
	class PlayerComponent : public Component {
		public:
			PlayerComponent() = default;
			void Update() override;
		private:
			float m_speed = 300;
	};
}