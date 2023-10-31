/*!*************************************************************************
****
\file ImguiAudio.cpp
\author w.chongsheng
\par DP email: w.chongsheng@digipen.edu
\par Course: CSD3400
\par Section: a
\brief  Imgui UI in charge of audio manipulations
****************************************************************************
***/

#include "imguiHelper/ImguiAudio.h"

namespace TDS
{
	AudioImgui::AudioImgui()
	{
		flags = NULL;
		panelTitle = "Audio Files";
		windowPadding = ImVec2(0.f, 0.f);

		appear = false;
		bar = 0.f;

		audeng = AudioWerks::AudioEngine::get_audioengine_instance();
	}

	void AudioImgui::init(bool show)
	{
		appear = show;
	}

	AudioImgui::~AudioImgui()
	{
		delete audeng;
	}

	void AudioImgui::activate_audio_controls()
	{
		flags = ImGuiWindowFlags_ChildMenu;
		appear = true;
	}

	void AudioImgui::deactivate_audio_controls()
	{
		flags = ImGuiWindowFlags_None;
		appear = false;
	}

	void AudioImgui::add_audio_files()
	{
		std::filesystem::path pathing = std::filesystem::current_path();
		std::cout << "The file path is " << pathing << '\n';

		/*std::string file_name;

		SoundInfo add_sound(file_name);*/
	}

	void AudioImgui::update()
	{
		if (appear)
		{
			ImGui::Text("Controls: ");
			ImGui::SameLine();

			if(ImGui::Selectable("Play Song"))
			{
				if (ImGui::ArrowButton("Play", ImGuiDir_Right))
				{
					/*SoundInfo selected{};
					selected = ImGui::IsItemClicked();
					
					audeng->playSound();*/
				}
			}

			ImGui::Columns(3);
			ImGui::SliderFloat("Playback", &bar, 16, 512);
		}

		audeng->update();
	}
}