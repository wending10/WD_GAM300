#include "components/components.h"

namespace TDS
{
	IComponent* addComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "NameTag")
			return ecs.addComponent<NameTag>(entityID);
		else if (componentName == "Transform")
			return ecs.addComponent<Transform>(entityID);
		else 
			return nullptr;
	}
}
