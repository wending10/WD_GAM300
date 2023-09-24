#include "ecs.h"

namespace TDS
{
	std::uint32_t                 ECS::systemCount = 0;
	std::uint32_t                 ECS::componentCount = 0;
	ECS::EntityArchetypeMap       ECS::mEntityArchetypeMap;
	ECS::ArchetypesArray          ECS::mArchetypes;
	EntityID                      ECS::mEntityIdCounter = 1;
	ECS::SystemsArrayMap          ECS::mSystems;
	ECS::ComponentTypeIDBaseMap   ECS::mComponentMap;
}

//namespace TDS
//{
//	inline std::vector<EntityID> ECS::getEntities();
//}