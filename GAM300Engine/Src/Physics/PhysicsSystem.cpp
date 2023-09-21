#include "Physics/PhysicsSystem.h"

namespace TDS
{
	System<Transform, RigidBody, Collider> _PhysicsSystem(1);
		
	namespace PhysicsSystem
	{
		void PhysicsSystemInit() {}
		
		void PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider)
		{
		}
	}
}
