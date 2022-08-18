#include "AudioComponent.h"
#include "Engine.h"

namespace digi {
	void AudioComponent::Update()
	{
	}
	void AudioComponent::Play()
	{
		g_Sound.PlayAudio(soundName);
	}
	void AudioComponent::Stop()
	{
	}
	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		return false;
	}
}
