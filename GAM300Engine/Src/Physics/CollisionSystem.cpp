#include "Physics/CollisionSystem.h"

namespace TDS
{
	System<Transform, RigidBody, Collider> CollisionSystem(1);
	void CollisionSystem::CollisionSystemInit()
	{
	}
	
	void CollisionSystem::CollisionSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider)
	{
		for (int i = 0; i < entities.size(); ++i)
		{
			for (int j = 0; j < entities.size(); ++j)
			{
				if (i == j)
					continue;
				if (SphereSphereCollision(_rigidbody[i], _collider[i], _rigidbody[j], _collider[j]))
				{
					// sphere resolution
				}
			}
		}
	}


	/*Helper Function*/
	bool CollisionSystem::SphereSphereCollision(RigidBody body1, Collider _collider1, RigidBody body2, Collider _collider2)
	{
		
	}
}

