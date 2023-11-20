#include "Audio.hxx"
#include <ctime>
#include <msclr\marshal_cppstd.h>

using namespace TDS::AudioWerks;

namespace ScriptAPI
{
	AudioSource::AudioSource()
	{
		audio_engine = AudioEngine::AudioEngine::get_audioengine_instance();
		deltatime = 0.f;
		wait = 0;
	}
	
	void AudioSource::Play(unsigned long delay)
	{
		if (delay > 0)
		{
			//deltatime = time(NULL);
		}
		else
		{
			msclr::interop::marshal_context context;
			std::string str = context.marshal_as<std::string>(clip->clips[clip->sub]);
			
			TDS::SoundInfo temp();
			
			audio_engine->playSound();
		}
	}

	void AudioSource::Pause()
	{
		audio_engine->pauseSound(clip->clips[clip->sub]);
	}

	void AudioSource::Stop()
	{
		audio_engine->stopSound(clip->clips[clip->sub]);
	}

	/*float AudioSource::get_volume()
	{
		
	}

	void AudioSource::set_volume(float vol)
	{

	}*/

	void AudioSource::Loop(bool set)
	{
		if (set)
		{
			TDS::SoundInfo temp(clip->clips[clip->sub]);

			if (!temp.isPlaying() && temp.isLoaded())
			{
				audio_engine->playSound(temp);
			}
		}
	}

	bool AudioSource::enabled()
	{
		TDS::SoundInfo temp(clip->clips[clip->sub]);

		return temp.isLoaded();
	}

	/*float AudioSource::get_pitch()
	{

	}

	void AudioSource::set_pitch(float vol)
	{

	}*/

	bool AudioSource::isPlaying()
	{
		TDS::SoundInfo temp(clip->clips[clip->sub]);

		return temp.isPlaying();
	}

	System::String^ AudioSource::GetElementFromAudioClip(int index)
	{
		if (clip != nullptr)
		{
			return
		}
	}

	template<typename T>
	T& AudioSource::operator=(float val)
	{
		value = val;
	}

	void AudioClip::add_clips(std::filesystem::path file)
	{
		System::String^ temp = gcnew System::String(file.string().c_str());
		
		clips.Add(temp);
		++sub;
	}

	System::String^ AudioClip::GetElement()
	{
		if(sub >= 0 && sub < clips.Count)
		{
			return clips[sub];
		}
	}
}