#include "imguiHelper/ImguiAudio.h"

namespace TDS
{
	AudioImgui::AudioImgui()
	{
		flags = ImGuiWindowFlags_NoCollapse;
		panelTitle = "Audio Files";
		windowPadding = ImVec2(0.f, 0.f);

		if(!audeng)
		{
			audeng = new AudioWerks::AudioEngine();
		}
	}

	AudioImgui::~AudioImgui()
	{
		if (audeng)
		{
			delete audeng;
		}
	}

	void AudioImgui::update()
	{
		
	}
}