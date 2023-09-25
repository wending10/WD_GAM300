#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ecs/ecs.h"
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
		void PhysicsSystemInit();
		void PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody);

	private:
		Vec3 CalculateTotalForce(RigidBody _collider);
		void NewtonianPhysics(Transform _transform, RigidBody _rigidbody);


		const double fixedDt = 0.0166666f;
		double accumulator = 0.0f;		
		
	};
}



#endif // !PHYSICSSYSTEM_H
