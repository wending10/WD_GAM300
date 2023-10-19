/*!*************************************************************************
****
\file AudioClip.h
\author Wong Chong Sheng
\par DP email: w.chongsheng@digipen.edu
\date 19-10-2023
\brief  This header declares the AudioClip class. This could probably be merged with AudioSource class.
****************************************************************************
***/

#ifndef AUDIOCLIP_H_
#define AUDIOCLIP_H_

#include "iComponent.h"
#include "fmod_engine/AudioEngine.h"

namespace TDS
{
	class AudioClip : public IComponent
	{
	public:
		friend class AudioSource;

	public:
		DLL_API AudioClip();
		DLL_API ~AudioClip();

		DLL_API virtual bool Deserialize(const rapidjson::Value& obj) = 0;
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;

		/*void Play(unsigned int ID);
		void Stop();

		void Add(unsigned int ID, FMOD::Sound* snd);
		void Remove(unsigned int ID);

		void Update();*/

	private:
		std::map<unsigned int, FMOD::Sound*> Sounds;
	};
}

#endif