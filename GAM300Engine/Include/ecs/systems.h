#ifndef SYSTEMS
#define SYSTEMS

#include "ecs/ecs.h"
#include "components/components.h"

// DONT INCLUDE THIS ANYWHERE BUT ECS.CPP

namespace TDS
{
	ECS::SystemsArrayMap						ECS::mSystems;

	System<Transform, RigidBody, Collider>		_PhysicsSystem(1);
	//System<Transform, RigidBody> _AISystem(1);
	//System<Transform> _GraphicsSystem(1);
}

#endif // SYSTEMS