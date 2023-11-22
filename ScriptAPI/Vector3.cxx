#include "Vector3.hxx"

namespace ScriptAPI
{
	Vector3::Vector3(float valueX, float valueY, float valueZ)
	{
		X = valueX;
		Y = valueY;
		Z = valueZ;
	}

	Vector3::Vector3(TDS::Vec3 value)
	{
		X = value.x;
		Y = value.y;
		Z = value.z;
	}

	Vector3 Vector3::operator-(Vector3 lhs, Vector3 rhs)
	{
		return Vector3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
	}
}