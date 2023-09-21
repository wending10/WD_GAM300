#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ecs/ecs.h"
#include "components/collider.h"
#include "components/rigidBody.h"
#include "components/transform.h"

namespace TDS
{
	namespace PhysicsSystem
	{
		void PhysicsSystemInit();
		void PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform ,RigidBody* _rigidbody, Collider* _collider);
		
		Vec3 CalculateTotalForce(Collider* _collider);


	}
}



#endif // !PHYSICSSYSTEM_H
