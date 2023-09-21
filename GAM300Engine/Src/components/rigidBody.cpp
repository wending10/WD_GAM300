#include "components/rigidBody.h"

namespace TDS
{
	/*!*************************************************************************
	Ctor for RigidBody Component
	****************************************************************************/
	RigidBody::RigidBody() : mAcceleration	(Vec3(0.0f, 0.0f, 0.0f)),
							 mVelocity		(Vec3(0.0f, 0.0f, 0.0f)),
							 mDirection		(Vec3(0.0f, 0.0f, 0.0f)),
							 mNextPosition	(Vec3(0.0f, 0.0f, 0.0f)),
							 mInputForce	(Vec3(0.0f, 0.0f, 0.0f)),
							 mFriction		(0.0f),
							 mRestitution	(0.0f),
						     mMass(1.0f),
							 mGravity(-10.0f)
	{ }

	/*!*************************************************************************
	Deserialize for RigidBody
	****************************************************************************/
	bool RigidBody::Deserialize(const rapidjson::Value& obj)
	{
		mAcceleration	= Vec3(obj["accelerationX"].GetFloat(), obj["accelerationY"].GetFloat(), obj["accelerationZ"].GetFloat());
		mVelocity		= Vec3(obj["velocityX"].GetFloat(), obj["velocityY"].GetFloat(), obj["velocityZ"].GetFloat());
		mDirection		= Vec3(obj["directionX"].GetFloat(), obj["directionY"].GetFloat(), obj["directionZ"].GetFloat());
		mNextPosition	= Vec3(obj["nextPositionX"].GetFloat(), obj["nextPositionY"].GetFloat(), obj["nextPositionZ"].GetFloat());
		mFriction		= obj["friction"].GetFloat();
		mRestitution	= obj["restitution"].GetFloat();
		mMass			= obj["mass"].GetFloat();
		mGravity		= obj["gravity"].GetFloat();
		return true;
	}

	/*!*************************************************************************
	Serialize for RigidBody
	****************************************************************************/
	bool RigidBody::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("accelerationX");
		writer->Double(mAcceleration.x);
		writer->Key("accelerationY");
		writer->Double(mAcceleration.y);
		writer->Key("accelerationZ");
		writer->Double(mAcceleration.z);
		
		writer->Key("velocityX");
		writer->Double(mVelocity.x);
		writer->Key("velocityY");
		writer->Double(mVelocity.y);
		writer->Key("velocityZ");
		writer->Double(mVelocity.z);

		writer->Key("directionX");
		writer->Double(mDirection.x);
		writer->Key("directionY");
		writer->Double(mDirection.y);
		writer->Key("directionZ");
		writer->Double(mDirection.z);

		writer->Key("nextPositionX");
		writer->Double(mNextPosition.x);
		writer->Key("nextPositionY");
		writer->Double(mNextPosition.y);
		writer->Key("nextPositionZ");
		writer->Double(mNextPosition.z);

		writer->Key("inputForceX");
		writer->Double(mInputForce.x);
		writer->Key("inputForceY");
		writer->Double(mInputForce.y);
		writer->Key("inputForceZ");
		writer->Double(mInputForce.z);
		
		writer->Key("friction");
		writer->Double(mFriction);

		writer->Key("restitution");
		writer->Double(mRestitution);

		writer->Key("mass");
		writer->Double(mMass);

		writer->Key("gravity");
		writer->Double(mGravity);

		return true;
	}
}