#pragma once
#include "Framework/Component.h"
#include "Audio/AudioChannel.h"
#include <string>

namespace digi {
	class AudioComponent : public Component {
		public:
			AudioComponent() = default;
			~AudioComponent();

			CLASS_DECLARATION(AudioComponent);

			void Initialize() override;
			void Update() override;

			void Play();
			void Stop();
		
			// Inherited via Component
			virtual bool Write(const rapidjson::Value& value) const override;
			virtual bool Read(const rapidjson::Value& value) override;

		private:
			AudioChannel m_channel;

			float volume = 1.0f;
			float pitch = 1.0f;
			bool loop = false;
			bool playOnWake = false;
			std::string soundName = "";
	};
}