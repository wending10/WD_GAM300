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

		music.clear();
		SFX.clear();
		background.clear();

		std::cout << "AudImg Constructor" << '\n';

		audeng = audeng = AudioWerks::AudioEngine::get_audioengine_instance();
	}

	AudioImgui::~AudioImgui()
	{
		delete audeng;
	}

	bool& AudioImgui::ToggleControls(bool state)
	{
		appear = state;

		if (appear)
		{
			flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		}
		else
		{
			flags = ImGuiWindowFlags_None;
			
			for(SoundInfo& sort : music)
			{
				audeng->stopSound(sort);
			}
			for (SoundInfo& sort : SFX)
			{
				audeng->stopSound(sort);
			}
			for (SoundInfo& sort : background)
			{
				audeng->stopSound(sort);
			}
		}

		return appear;
	}

	void AudioImgui::add_audio_files(std::filesystem::path folder_path)
	{
		std::filesystem::path pathing = folder_path;
		std::cout << "The file path is " << pathing.string() << '\n';

		/*SoundInfo add_sound(pathing.string());
		sounds.push_back(add_sound);*/
		SoundInfo test_path("../../assets/audioFiles/Songs/test.flac");
		test_path.setLoop(false);
		test_path.set3DCoords(0.f, 0.f, 0.f);
		test_path.setVolume(0.5f);

		music.push_back(test_path);
	}

	void AudioImgui::play()
	{
		audeng->loadSound(music[0]);
		audeng->playSound(music[0]);

		/*audeng->loadSound(add_sound);
		audeng->playSound(add_sound);*/
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