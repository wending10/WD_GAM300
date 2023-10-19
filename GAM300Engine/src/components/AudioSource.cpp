#include "components/AudioSource.h"

namespace TDS
{
	AudioSource::AudioSource()
	{
		position.Set(0.f, 0.f, 0.f);
	}

	AudioSource::~AudioSource()
	{
		//Empty
	}

	bool AudioSource::Deserialize(const rapidjson::Value& obj)
	{		
		position = { obj["PositionX"].GetFloat(), obj["PositionY"].GetFloat(), obj["PositionZ"].GetFloat() };

		return true;
	}

	bool AudioSource::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("PositionX");
		writer->Double(static_cast<float>(position[0]));
	}
}