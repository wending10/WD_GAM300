#include "components/nameTag.h"

namespace TDS
{
	NameTag::NameTag() : mName	("entity") 
	{ }

	bool NameTag::Deserialize(const rapidjson::Value& obj)
	{
		mName = obj["name"].GetString();
		return true;
	}

	bool NameTag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("name");
		writer->String(mName.c_str());
		return true;
	}
}
