#pragma once 

namespace FMOD
{
	class Channel;
}

namespace digi
{
	class AudioChannel
	{
	public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel) { m_channel = channel; }

		bool IsPlaying();
		void Stop();

		// !! create SetPitch/GetPitch (takes float, returns float) 
		void SetPitch(float pitch);
		float GetPitch();
		void SetVolume(float volume);
		float GetVolume();
		// !! create SetVolume/GetVolume (takes float, returns float) 

	private:
		FMOD::Channel* m_channel = nullptr;
	};
}