/*!*************************************************************************
****
\file ImguiAudio.h
\author w.chongsheng
\par DP email: w.chongsheng@digipen.edu
\par Course: CSD3400
\par Section: a
\brief  Imgui UI in charge of audio manipulations
****************************************************************************
***/

#ifndef IMGUI_AUDIO
#define IMGUI_AUDIO

#include <filesystem>

#include "ImguiHelper.h"
#include "fmod_engine/AudioEngine.h"

namespace TDS
{
	class AudioImgui : public LevelEditorPanel
	{
	public:
		/**
		 * @brief Constructor that sets appear to false and bar as 0.f. Initiates the Audio Engine.
		*/
		AudioImgui();

		/**
		 * @brief Destructor that deactivates the Audio Engine
		*/
		~AudioImgui();

		/**
		 * @brief Show or hide audio controls. Also can be used to see if active or not
		 * @param state 
		 * @return 
		*/
		bool& ToggleControls(bool state = false);

		void add_audio_files(std::filesystem::path folder_path);

		/**
		 * @brief Initialize
		*/
		virtual void init();

		/**
		 * @brief Update loop.
		*/
		void update();

	private:
		AudioWerks::AudioEngine* audeng;

		bool appear;
		float bar;

		std::vector<SoundInfo> sounds;
	};
}

#endif