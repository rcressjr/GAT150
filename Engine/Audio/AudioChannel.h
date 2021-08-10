#pragma once
#include <fmod.hpp>

namespace rj {
	class AudioChannel {
	public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel) : channel{ channel } {}

		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);
		float GetPitch();

		void SetVolume(float volume);
		
	private:
		FMOD::Channel* channel{ nullptr };
	};
}