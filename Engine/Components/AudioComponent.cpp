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
}
