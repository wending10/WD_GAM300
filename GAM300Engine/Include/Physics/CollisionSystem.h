#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ecs/ecs.h"
#include "components/collider.h"
#include "components/transform.h"
#include "components/rigidBody.h"


namespace TDS
{
	class CollisionSystem
	{
	public:
		void CollisionSystemInit();
		void CollisionSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider);

	private:
		bool SphereSphereCollision(RigidBody body1, Collider _collider1, RigidBody body2, Collider _collider2); // assuming all are spheres
	};
}


#endif // !COLLISIONSYSTEM_H
