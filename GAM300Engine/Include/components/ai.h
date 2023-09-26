#ifndef AICOMPONENT
#define AICOMPONENT

#include "ecs/ecs.h"

namespace TDS
{
	class AI : public IComponent
	{
	public:
		AI();
		AI(AI&& toMove) noexcept;
		~AI() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		virtual void ImGuiDisplay();

	private:
		std::string mTitle;
		float mMasterVolume;
	};
}

#endif // AICOMPONENT