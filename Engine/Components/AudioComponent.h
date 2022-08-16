#pragma once
#include "Framework/Component.h"
#include <string>

namespace digi {
	class AudioComponent : public Component {
		public:
			void Update() override;
			float volume = 1.0f;
			float pitch = 1.0f;
			bool loop = false;
			bool playOnWake = false;
			std::string soundName = "";

			void Play();
			void Stop();
		
	};
}