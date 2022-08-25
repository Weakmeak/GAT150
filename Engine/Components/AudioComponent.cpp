#include "AudioComponent.h"
#include "Engine.h"

namespace digi {
	AudioComponent::~AudioComponent()
	{
		m_channel.Stop();
	}

	void AudioComponent::Initialize()
	{
		if (playOnWake)
		{
			Play();
		}
	}

	void AudioComponent::Update()
	{
	}

	void AudioComponent::Play()
	{
		m_channel.Stop();
		m_channel = g_Sound.PlayAudio(soundName, volume, pitch, loop);
	}

	void AudioComponent::Stop()
	{
		m_channel.Stop();
	}

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		// !! READ_DATA on sound_name, volume, ... 
		READ_DATA(value, soundName);
		READ_DATA(value, volume);
		READ_DATA(value, pitch);
		READ_DATA(value, loop);
		READ_DATA(value, playOnWake);
		g_Sound.AddAudio(soundName, soundName);

		return true;
	}
}
