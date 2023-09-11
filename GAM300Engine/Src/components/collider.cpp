#include "components/collider.h"

namespace TDS {

	/*!*************************************************************************
	Constructor for collider component
	****************************************************************************/
	Collider::Collider() : mColliderType	(ColliderType::none),
						   mCollisionNormal (Vec2(0.0f, 0.0f)),
						   mMin				(Vec2(0.0f, 0.0f)),
						   mMax				(Vec2(0.0f, 0.0f)),
						   mOffset			(Vec2(0.0f, 0.0f)),
						   mHit				(0),
						   mRadius			(0.0f),
						   mIsAlive			(true)
	{ }

	/*!*************************************************************************
	Derserialize collider component
	****************************************************************************/
	bool Collider::Deserialize(const rapidjson::Value& obj)
	{
		mColliderType		= static_cast<ColliderType>(obj["colliderType"].GetInt());
		mCollisionNormal	= Vec2(obj["collisionNormalX"].GetFloat(), obj["collisionNormalY"].GetFloat());
		mMin				= Vec2(obj["minX"].GetFloat(), obj["minY"].GetFloat());
		mMax				= Vec2(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());
		mOffset				= Vec2(obj["offsetX"].GetFloat(), obj["offsetY"].GetFloat());
		mHit				= obj["hit"].GetInt();
		mRadius				= obj["radius"].GetFloat();
		mIsAlive			= obj["isAlive"].GetBool();

		return true;
	}

	/*!*************************************************************************
	Serialize collider component
	****************************************************************************/
	bool Collider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("colliderType");
		writer->Int(static_cast<int>(mColliderType));

		writer->Key("collisionNormalX");
		writer->Double(mCollisionNormal.x);
		writer->Key("collisionNormalY");
		writer->Double(mCollisionNormal.y);

		writer->Key("minX");
		writer->Double(mMin.x);
		writer->Key("minY");
		writer->Double(mMin.y);

		writer->Key("maxX");
		writer->Double(mMax.x);
		writer->Key("maxY");
		writer->Double(mMax.y);

		writer->Key("mOffsetX");
		writer->Double(mOffset.x);
		writer->Key("mOffsetY");
		writer->Double(mOffset.y);

		writer->Key("hit");
		writer->Double(mHit);

		writer->Key("radius");
		writer->Double(mRadius);

		writer->Key("isAlive");
		writer->Double(mIsAlive);

		return true;
	}
}