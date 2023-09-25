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
				if (SphereSphereCollision(_transform[i], _rigidbody[i], _collider[i],_transform[j], _rigidbody[j], _collider[j]))
				{
					SphereSphereResolution(_transform[i], _rigidbody[i], _transform[j], _rigidbody[j]);
					
				}
			}
		}
	}


	/*Helper Function*/
	bool CollisionSystem::SphereSphereCollision(Transform trans1, RigidBody body1, Collider collider1, Transform trans2, RigidBody body2, Collider collider2)
	{
		// get the distance between the two objects
		float distance = (trans1.GetPosition() - trans2.GetPosition()).magnitude();
		// if the distance is less than the sum of the two radii, they are colliding
		if (distance < collider1.GetRadius() + collider2.GetRadius())
		{
			return true;
		}
		return false;
	}

	void CollisionSystem::SphereSphereResolution(Transform trans1, RigidBody body1, Transform trans2, RigidBody body2)
	{
		// get the direction of both objects, reflect them and multiply back into the forces
		Vec3 Dir1 = body1.GetDirection();
		Vec3 Dir2 = body2.GetDirection();
		Dir1 = Dir1 * -1;
		Dir2 = Dir2 * -1;
		body1.SetDirection(Dir1);
		body2.SetDirection(Dir2);
		
	}

	
}

