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
#include <string.h>

namespace TDS
{
	AudioImgui::AudioImgui()
	{
		flags = NULL;
		panelTitle = "Audio Files";
		windowPadding = ImVec2(0.f, 0.f);

		appear = playing = false;
		bar = 0.f;

		music.clear();
		SFX.clear();
		background.clear();
		VO.clear();

		std::cout << "AudImg Constructor" << '\n';

		audeng = AudioWerks::AudioEngine::get_audioengine_instance();
		add_audio_files("../assets/audioFiles/");
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
			
			if(playing)
			{
				for (SoundInfo& sort : music)
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
				for (SoundInfo& sort : VO)
				{
					audeng->stopSound(sort);
				}

				playing = false;
			}
		}

		return appear;
	}

	void AudioImgui::add_audio_files(std::filesystem::path folder_path)
	{
		/*std::filesystem::path Music_path{ folder_path / "Music" }, Background_path{ folder_path / "Songs" },
			SFX_path{ folder_path / "Sound Effects" }, Voice_path{ folder_path / "Voice Overs" };*/
		
		std::filesystem::path full_path = folder_path; //pathing / append;
		std::vector<std::filesystem::path> all_files; //store all file path

		if (std::filesystem::is_directory(folder_path))
		{
			all_files = go_deeper(full_path);
		}

		for (auto& str : all_files)
		{
			if (str.string().find("/Music\\") != std::string::npos)
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				background.push_back(temp);
			}
			else if (str.string().find("/Songs\\") != std::string::npos)
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				music.push_back(temp);
			}
			else if (str.string().find("/Sound Effects\\") != std::string::npos)
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				SFX.push_back(temp);
			}
			else if (str.string().find("/Voice Overs\\") != std::string::npos)
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				VO.push_back(temp);
			}
		}
	}

	std::vector<std::filesystem::path> AudioImgui::go_deeper(std::filesystem::path f_path)
	{
		std::vector<std::filesystem::path> folders;
		std::vector<std::filesystem::path> files;

		for (auto& temp : std::filesystem::directory_iterator(f_path))
		{
			if (temp.is_directory())
			{
				folders = go_deeper(temp);

				for (auto& temp2 : folders)
				{
					std::size_t pos{ temp2.string().find("\\") };
					if (pos != std::string::npos)
					{
						temp2.string().replace(pos, pos + 1, "/");
					}
					files.push_back(temp2);
				}
			}
			else
			{
				std::size_t pos{ temp.path().string().find("\\") };
				if (pos != std::string::npos)
				{
					temp.path().string().replace(pos, pos + 1, "/");
				}
				files.push_back(temp);
			}
		}

		return files;
	}

	void AudioImgui::play(std::string file)
	{
		SoundInfo this_one{};
		
		for (SoundInfo& temp : music)
		{
			if (temp.getFilePath().find(file) != std::string::npos)
			{
				this_one = temp;
			}
		}
		for (SoundInfo& temp : background)
		{
			if (temp.getFilePath().find(file) != std::string::npos)
			{
				this_one = temp;
			}
		}
		for (SoundInfo& temp : SFX)
		{
			if (temp.getFilePath().find(file) != std::string::npos)
			{
				this_one = temp;
			}
		}
		for (SoundInfo& temp : VO)
		{
			if (temp.getFilePath().find(file) != std::string::npos)
			{
				this_one = temp;
			}
		}

		audeng->loadSound(this_one);
		audeng->playSound(this_one);

		playing = true;
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