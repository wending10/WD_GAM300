#ifndef RIGIDBODYCOMPONENT
#define RIGIDBODYCOMPONENT

#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{
	class RigidBody : public IComponent
	{
	public:
		RigidBody();
		~RigidBody() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		void ImGuiDisplay();

		Vec3& GetAcceleration() { return mAcceleration; }
		void SetAcceleration(Vec3 acceleration) { mAcceleration = acceleration; }

		Vec3& GetVel() { return mVelocity; }
		void SetVel(Vec3 velocity) { mVelocity = velocity; }
		void SetVel(float velocityX, float velocityY) { mVelocity = Vec3(velocityX, velocityY); }

		Vec3& GetInputForce() { return mInputForce; }
		void SetInputForce(Vec3 inputForce) { mInputForce = inputForce; }
		void SetInputForce(float inputForceX, float inputForceY) { mInputForce = Vec3(inputForceX, inputForceY); }

		Vec3& GetDirection() { return mDirection; }
		void SetDirection(Vec3 direction) { mDirection = direction; }
		void SetDirection(float directionX, float directionY) { mDirection = Vec3(directionX, directionY); }

		Vec3& GetNextPosition() { return mNextPosition; }
		void SetNextPosition(Vec3 nextPosition) { mNextPosition = nextPosition; }
		
		float& GetFriction() { return mFriction; }
		void SetFrictionCoefficient(float friction) { mFriction = friction; }

		float& GetRestitution() { return mRestitution; }
		void SetRestitution(float restitution) { mRestitution = restitution; }

		float& GetMass() { return mMass; }
		float& GetInverseMass() { return mInverseMass; }
		void SetMass(float mass) { mMass = mass; mInverseMass = 1.0f / mass; }

		float& GetGravity() { return mGravity; }
		void SetGravity(float gravity) { mGravity = gravity; }
		

	private:
		Vec3 mAcceleration;
		Vec3 mVelocity;
		Vec3 mDirection;
		Vec3 mNextPosition;
		Vec3 mInputForce;
		Vec3 mTotalForce;
		
		float mFriction;
		float mRestitution;
		float mMass;
		float mInverseMass;
		float mGravity;
	};

}

#endif //RIGIDBODYCOMPONENT