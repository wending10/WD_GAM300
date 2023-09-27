#include "Physics/PhysicsSystem.h"

namespace TDS
{
	const double PhysicsSystem::fixedDt = 0.0166666f;
	double PhysicsSystem::accumulator = 0.0f;
	//System<Transform, RigidBody, Collider> _PhysicsSystem(1);
		
	void PhysicsSystem::PhysicsSystemInit()
	{
		
	}

	void PhysicsSystem::PhysicsSystemUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _transform, RigidBody* _rigidbody, Collider* _collider)
	{
		// need fix timestep
		for (int i = 0; i < entities.size(); ++i)
		{
			//NewtonianPhysics(_transform[i], _rigidbody[i]);
			std::cout << "test";
		}
	}

	Vec3 PhysicsSystem::CalculateTotalForce(RigidBody& _rigidbody)
	{
		Vec3 totalForce		= Vec3(0.0f);
		totalForce			+= _rigidbody.GetInputForce();
		totalForce.y		+= (-_rigidbody.GetGravity() * _rigidbody.GetMass());
		return totalForce;
	}

	Vec3 PhysicsSystem::NewtonianPhysics(Transform& _transform, RigidBody& _rigidbody)
	{
		Vec3 totalForce = CalculateTotalForce(_rigidbody);
		Vec3 acceleration	= totalForce * _rigidbody.GetInverseMass();
		_rigidbody.SetAcceleration(acceleration);
		
		Vec3 velocity		= _rigidbody.GetVel();
		velocity			+= acceleration * fixedDt/*dt*/;
		_rigidbody.SetVel(velocity);
		
		Vec3 position		= _transform.GetPosition();
		position			+= velocity * fixedDt/*dt*/;
		_transform.SetPosition(position);
		
		return position;
	}

	
}
