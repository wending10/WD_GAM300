#include "components/ai.h"

namespace TDS
{
	AI::AI()
	{ }

	AI::AI(AI&& toMove) noexcept
	{ }

	bool AI::Deserialize(const rapidjson::Value& obj)
	{

		return true;
	}

	bool AI::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{

		return true;
	}

	void AI::ImGuiDisplay()
	{

	}
}
