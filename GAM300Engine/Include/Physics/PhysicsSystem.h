#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ecs/ecs.h"
#include "components/rigidBody.h"
#include "components/transform.h"
#include "dotnet/ImportExport.h"
#include "Timestep/Timestep.h"

// X = moving left, right
// Y = moving up, down
// Z = moving forward, backward

namespace TDS
{
	class DLL_API PhysicsSystem
	{
	public:
		static void PhysicsSystemInit();
		static void PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody);

	private:
		static Vec3 CalculateTotalForce(RigidBody& _collider);
		static void NewtonianPhysics(Transform& _transform, RigidBody& _rigidbody);
		static void SettingObjectDirection(Vec3& totalForce, RigidBody& _rigidbody);
	private:
		static const double fixedDt;
		static double accumulatedTime;
	};
}



#endif // !PHYSICSSYSTEM_H
