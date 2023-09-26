#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ecs/ecs.h"
#include "components/collider.h"
#include "components/transform.h"
#include "components/rigidBody.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class DLL_API CollisionSystem
	{
	public:
		void CollisionSystemInit();
		void CollisionSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider);

	private:
		bool SphereSphereCollision(Transform trans1, RigidBody body1, Collider collider1, Transform trans2, RigidBody body2, Collider collider2);
		void SphereSphereResolution(Transform trans1, RigidBody body1, Transform trans2, RigidBody body2);

	};
}


#endif // !COLLISIONSYSTEM_H
