#ifndef IMGUI_AUDIO
#define IMGUI_AUDIO

#include "ImguiHelper.h"
#include "fmod_engine/AudioEngine.h"

namespace TDS
{
	class AudioImgui : public LevelEditorPanel
	{
	public:
		AudioImgui();
		~AudioImgui();

		void activate_audio_controls();
		void deactivate_audio_controls();
		void update();

	private:
		AudioWerks::AudioEngine audeng;

		bool appear;
	};
}

#endif