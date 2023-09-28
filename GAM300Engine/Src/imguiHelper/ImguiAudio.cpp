#include "imguiHelper/ImguiAudio.h"

namespace TDS
{
	AudioImgui::AudioImgui()
	{
		flags = NULL;
		panelTitle = "Audio Files";
		windowPadding = ImVec2(0.f, 0.f);

		appear = false;

		audeng.init();
	}

	AudioImgui::~AudioImgui()
	{
		audeng.deactivate();
	}

	void AudioImgui::activate_audio_controls()
	{
		flags = ImGuiWindowFlags_ChildMenu;
		appear = true;
	}

	void AudioImgui::deactivate_audio_controls()
	{
		appear = false;
	}

	void AudioImgui::update()
	{
		if(appear)
		{
			ImGui::Text("Controls: ");
			ImGui::SameLine();

			/*if(ImGui::Selectable(""))
			{
				if (ImGui::ArrowButton("Play", ImGuiDir_Right))
				{
					audeng.playSound(current_sound);
				}
			}*/
		}
		
		//audeng.update();
	}
}