#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ecs/ecs.h"
#include "components/collider.h"
#include "components/rigidBody.h"
#include "components/transform.h"

// X = moving left, right
// Y = moving up, down
// Z = moving forward, backward

namespace TDS
{
	class PhysicsSystem
	{
	public:
		static void PhysicsSystemInit();
		static void PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider);

	private:
		static Vec3 CalculateTotalForce(RigidBody& _collider);
		static Vec3 NewtonianPhysics(Transform& _transform, RigidBody& _rigidbody);


		static const double fixedDt;
		static double accumulator;
		
	};
}



#endif // !PHYSICSSYSTEM_H
