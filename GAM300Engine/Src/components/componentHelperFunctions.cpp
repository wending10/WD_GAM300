#include "components/components.h"

namespace TDS
{
	IComponent* addComponentByName(std::string componentName, EntityID entityID)
	{
		if (componentName == "NameTag")
			return ECS::addComponent<NameTag>(entityID);
		else if (componentName == "Transform")
			return ECS::addComponent<Transform>(entityID);
		else 
			return nullptr;
	}
}
