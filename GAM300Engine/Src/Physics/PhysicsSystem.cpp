#include "Physics/PhysicsSystem.h"

namespace TDS
{
	System<Transform, RigidBody> _PhysicsSystem(1);
	void PhysicsSystem::PhysicsSystemInit()
	{
		
	}

	void PhysicsSystem::PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody)
	{
		// Physics loop
		accumulatedTime += dt;
		while (accumulatedTime >= TimeStep::GetFixedDeltaTime())
		{
			for (int i = 0; i < entities.size(); ++i)
			{
				NewtonianPhysics(_transform[i], _rigidbody[i]);
			}
			accumulatedTime -= TimeStep::GetFixedDeltaTime();
		}
		
	}

	Vec3 PhysicsSystem::CalculateTotalForce(RigidBody _rigidbody)
	{
		Vec3 totalForce		= Vec3(0.0f);
		totalForce			+= _rigidbody.GetInputForce();
		totalForce.y		+= (-_rigidbody.GetGravity() * _rigidbody.GetMass());
		return totalForce;
	}

	void PhysicsSystem::NewtonianPhysics(Transform _transform, RigidBody _rigidbody)
	{
		Vec3 totalForce = CalculateTotalForce(_rigidbody);
		Vec3 acceleration	= totalForce * _rigidbody.GetInverseMass();
		_rigidbody.SetAcceleration(acceleration);
		
		Vec3 velocity		= _rigidbody.GetLinearVel();
		velocity += acceleration * TimeStep::GetFixedDeltaTime();
		_rigidbody.SetLinearVel(velocity);
		
		Vec3 position		= _transform.GetPosition();
		position			+= velocity * TimeStep::GetFixedDeltaTime();
		_transform.SetPosition(position);
	}

	
}
