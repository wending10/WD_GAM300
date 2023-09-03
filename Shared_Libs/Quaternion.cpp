#include "Quaternion.h"

namespace TDS
{
	Quat::Quat() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
	Quat::Quat(Quat const& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
	Quat::Quat(float value) : w(value), x(value), y(value), z(value) {}
	Quat::Quat(float data[]) : w(data[0]), x(data[1]), y(data[2]), z(data[3]) {}
	Quat::Quat(float newX, float newY, float newZ, float newW) : w(newW), x(newX), y(newY), z(newZ) {}
	Quat::Quat(float angle, Vec3 const& axis) : w(angle), x(axis.x), y(axis.y), z(axis.z) {}
	// Create a quaternion from two normalized vectors
    Quat::Quat(Vec3 const& u, Vec3 const& v)
    {
        float norm_u_norm_v = Mathf::Sqrt(Vec3::Dot(u,u) * Vec3::Dot(v,v));
        float real_part = norm_u_norm_v + Vec3::Dot(u,v);
        Vec3 t;

        if (real_part < 1.e-6f * norm_u_norm_v)
        {
            // If u and v are exactly opposite, rotate 180 degrees
            // around an arbitrary orthogonal axis. Axis normalisation
            // can happen later, when we normalise the quaternion.
            real_part = 0.0f;
            t = Mathf::Abs(u.x) > Mathf::Abs(u.z) ? Vec3(-u.y, u.x, 0.f)
                                                  : Vec3(0.f, -u.z, u.y);
        }
        else
        {
            // Otherwise, build quaternion the standard way.
            t = Vec3::Cross(u, v);
        }

        *this = normalize(Quat(real_part, t.x, t.y, t.z));
    }
	Quat::Quat(Vec3 const& euler)
	{
        Vec3 c = Vec3(Mathf::Cos(euler.x * 0.5f), Mathf::Cos(euler.y * 0.5f), Mathf::Cos(euler.z * 0.5f));
        Vec3 s = Vec3(Mathf::Sin(euler.x * 0.5f), Mathf::Sin(euler.y * 0.5f), Mathf::Sin(euler.z * 0.5f));

        w = c.x * c.y * c.z + s.x * s.y * s.z;
        x = s.x * c.y * c.z - c.x * s.y * s.z;
        y = c.x * s.y * c.z + s.x * c.y * s.z;
        z = c.x * c.y * s.z - s.x * s.y * c.z;
	}
	Quat::~Quat() {}
	float Quat::angle(Quat const& q)
	{
        if (Mathf::Abs(q.w) > Mathf::Cos(0.5f))
        {
            float const a = Mathf::Acos(Mathf::Sqrt(q.x * q.x + q.y * q.y + q.z * q.z)) * 2.0f;
            if (q.w < 0.0f)
                return Mathf::PI * 2.0f - a;
            return a;
        }
        return Mathf::Acos(q.w) * 2.0f;
    
	}
	Quat Quat::angleAxis(float const& angle, float const& newX, float const& newY, float const& newZ)
	{
		float const a = angle;
        float const s = Mathf::Sin(a * 0.5f);
        return Quat(Mathf::Cos(a * 0.5f), newX * s, newY * s, newZ * s);
	}
	Quat Quat::angleAxis(float const& angle, Vec3 const& axis)
	{
		float const a = angle;
        float const s = Mathf::Sin(a * 0.5f);
        return Quat(Mathf::Cos(a * 0.5f), axis.x * s, axis.y * s, axis.z * s);
	}
	Vec3 Quat::axis(Quat const& q)
	{
		float const tmp1 = 1.f - q.w * q.w;
        if (tmp1 <= 0.f)
            return Vec3(0.f, 0.f, 1.f);
        float const tmp2 = 1.f / Mathf::Sqrt(tmp1);
        return Vec3(q.x * tmp2, q.y * tmp2, q.z * tmp2);
	}
	Quat Quat::conjugate(Quat const& q)
	{
		return Quat(q.w, -q.x, -q.y, -q.z);
	}
	Quat Quat::cross(Quat const& q1, Quat const& q2)
	{
		return Quat(
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
			q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
	}
	Vec3 Quat::cross(Quat const& q, Vec3 const& v)
	{
		return q * v;
	}
	Vec3 Quat::cross(Vec3 const& v, Quat const& q)
	{
		return inverse(q) * v;
	}
	float Quat::dot(Quat const& q1, Quat const& q2)
	{
		return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	}
	Vec3 Quat::eulerAngle(Quat const& q)
	{
		return Vec3(pitch(q), yaw(q), roll(q));
	}
	Quat Quat::exp(Quat const& q)
	{
        Vec3 u = Vec3(q.x, q.y, q.z);
        float const tmpAngle = length(u);
        if (tmpAngle < Mathf::Epsilon)
            return Quat();
        Vec3 const v = u / tmpAngle;
        return Quat(Mathf::Cos(tmpAngle), v.x * Mathf::Sin(tmpAngle), v.y * Mathf::Sin(tmpAngle), v.z * Mathf::Sin(tmpAngle));
	}
	float Quat::extractRealComponent(Quat const& q)
	{
		float tmpW = 1.f - q.x * q.x - q.y * q.y - q.z * q.z;
        if (tmpW < 0.f)
            return 0.f;
        return -Mathf::Sqrt(tmpW);
	}
	Quat Quat::intermediate(Quat const& prev, Quat const& curr, Quat const& next)
	{
		Quat invQuat = inverse(curr);
		return exp((log(next * invQuat) + log(prev * invQuat)) / -4.f) * curr;
	}
	Quat Quat::inverse(Quat const& q)
	{
        return conjugate(q) / dot(q, q);
	}
	float Quat::length(Quat const& q)
	{
		return Mathf::Sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	}
	float Quat::length2(Quat const& q)
	{
		return q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
	}
	Quat Quat::log(Quat const& q)
	{
		Vec3 u(q.x, q.y, q.z);
		float Vec3Len = length(u);
		if (Vec3Len < Mathf::Epsilon)
		{
			if (q.w > 0.f) return Quat(Mathf::Log(q.w), 0.f, 0.f, 0.f);
			else if (q.w < 0.f) return Quat(Mathf::Log(-q.w), Mathf::PI, 0.f, 0.f);
			else return Quat(INFINITY, INFINITY, INFINITY, INFINITY);
		}
		else
		{
			float t = Mathf::Atan2(Vec3Len, q.w) / Vec3Len;
			float QuatLen2 = Vec3Len * Vec3Len + q.w * q.w;
			return Quat(Mathf::Log(QuatLen2) * 0.5f, t * q.x, t * q.y, t * q.z);
		}
	}
	Quat Quat::mix(Quat const& x, Quat const& y, float a)
	{
		float const cosTheta = dot(x,y);
		if (cosTheta > 1.f - Mathf::Epsilon)
		{
			float tmpW = x.w * (1.f -a) + y.w * a;
			float tmpX = x.x * (1.f -a) + y.x * a;
			float tmpY = x.y * (1.f -a) + y.y * a;
			float tmpZ = x.z * (1.f -a) + y.z * a;
			return Quat(tmpW, tmpX, tmpY, tmpZ);
		}
		else
		{
			float angle = Mathf::Acos(cosTheta);
			return (Mathf::Sin((1.f - a) * angle) * x + Mathf::Sin(a * angle) * y) / Mathf::Sin(angle);
		}
	}
	Quat Quat::normalize(Quat const& q)
	{
		float len = length(q);
		if (len <= 0.f)
			return Quat(1.f, 0.f, 0.f, 0.f);
		float oneOverLen = 1.f / len;
		return Quat(q.w * oneOverLen, q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen);
	}
	float Quat::pitch(Quat const& q)
	{
		float const y = 2.f * (q.y * q.z + q.w * q.x);
		float const x = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;
		if (x == 0.f && y == 0.f)
			return 2.f * Mathf::Atan2(q.x, q.w);
		return Mathf::Atan2(y, x);
	}
	Quat Quat::pow(Quat const& q, float const& exponent)
	{
		if (exponent > -Mathf::Epsilon && exponent < Mathf::Epsilon)
			return Quat(1.f, 0.f, 0.f, 0.f);
		float magnitude = length(q);
		float tmpAngle;
		if (Mathf::Abs(q.w / magnitude) > Mathf::Cos(0.5f))
		{
			float VectorMagnitude = q.x * q.x + q.y * q.y + q.z * q.z;
			if (VectorMagnitude < Mathf::Epsilon)
				return Quat(Mathf::Pow(q.w, exponent), 0.f, 0.f, 0.f);
			tmpAngle = Mathf::Asin(Mathf::Sqrt(VectorMagnitude) / magnitude);
		}
		else
		{
			tmpAngle = Mathf::Acos(q.w / magnitude);
		}

		float newAngle = tmpAngle * exponent;
		float Div = Mathf::Sin(newAngle) / Mathf::Sin(tmpAngle);
		float Mag = Mathf::Pow(magnitude, exponent - 1.f);
		return Quat(Mathf::Cos(newAngle) * magnitude * Mag, q.x * Div * Mag, q.y * Div * Mag, q.z * Div * Mag);
	}
	float Quat::roll(Quat const& q)
	{
		float const y = 2.f * (q.x * q.y + q.w * q.z);
		float const x = q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z;
		if (x == 0.f && y == 0.f)
			return 0.f;
		return Mathf::Atan2(y, x);	
	}
	Vec3 Quat::rotate(Quat const& q, Vec3 const& v)
	{
		return q * v;
	}
	Vec4 Quat::rotate(Quat const& q, Vec4 const& v)
	{
		return q * v;
	}
	Quat Quat::rotate(Quat const& q, float const& angle, Vec3 const& axis)
	{
		Vec3 tmp = axis;

		// axis of rotation must be normalised
		float len = length(tmp);
		if (Mathf::Abs(len - 1.f) > Mathf::Epsilon)
		{
			float oneOverLen = 1.f / len;
			tmp.x *= oneOverLen;
			tmp.y *= oneOverLen;
			tmp.z *= oneOverLen;
		}

		float const AngleRad(angle);
		float const Sin = Mathf::Sin(AngleRad * 0.5f);
		return q * Quat(Mathf::Cos(AngleRad * 0.5f), tmp.x * Sin, tmp.y * Sin, tmp.z * Sin);
	}
	Quat Quat::squad(Quat const& q1, Quat const& q2, Quat const& s1, Quat const& s2, float const& h)
	{
		return mix(mix(q1, q2, h), mix(s1, s2, h), 2.f * ((1.f) - h) * h);
	}
	Mat3 Quat::toMat3(Quat const& q)
	{
		Mat3 Result;
		float qxx(q.x * q.x);
		float qyy(q.y * q.y);
		float qzz(q.z * q.z);
		float qxz(q.x * q.z);
		float qxy(q.x * q.y);
		float qyz(q.y * q.z);
		float qwx(q.w * q.x);
		float qwy(q.w * q.y);
		float qwz(q.w * q.z);

		Result.m[0][0] = 1.f - 2.f * (qyy + qzz);
		Result.m[0][1] = 2.f * (qxy + qwz);
		Result.m[0][2] = 2.f * (qxz - qwy);

		Result.m[1][0] = 2.f * (qxy - qwz);
		Result.m[1][1] = 1.f - 2.f * (qxx + qzz);
		Result.m[1][2] = 2.f * (qyz + qwx);

		Result.m[2][0] = 2.f * (qxz + qwy);
		Result.m[2][1] = 2.f * (qyz - qwx);
		Result.m[2][2] = 1.f - 2.f * (qxx + qyy);
		return Result;
				
	}
	Mat4 Quat::toMat4(Quat const& q)
	{
		return Mat4(toMat3(q));
	}


	float Quat::yaw(Quat const& q)
	{
		float clamp = Mathf::Clamp(-2.f * (q.x * q.z - q.w * q.y), -1.f, 1.f);
		return Mathf::Asin(clamp);
	}

    // Component Access
	float& Quat::operator[](int index)
    {
        switch (index)
        {
        case 0: return w;
        case 1: return x;
        case 2: return y;
        case 3: return z;
        default: throw std::out_of_range("Index out of range");
        }
    }

	float const& Quat::operator[](int index) const
	{
        switch (index)
        {
        case 0: return w;
        case 1: return x;
        case 2: return y;
        case 3: return z;
        default: throw std::out_of_range("Index out of range");
        }
	}
	Quat& Quat::operator=(Quat const& q)
    {
        w = q.w;
        x = q.x;
        y = q.y;
        z = q.z;
        return *this;
    }
	Quat& Quat::operator+=(Quat const& q)
	{
        w = w + q.w;
        x = x + q.x;
        y = y + q.y;
        z = z + q.z;
        return *this;
    }
	Quat& Quat::operator-=(Quat const& q)
	{
        w = w - q.w;
        x = x - q.x;
        y = y - q.y;
        z = z - q.z;
        return *this;
	}
	Quat& Quat::operator*=(Quat const& q)
	{
        Quat p(*this);
        Quat r(q);
        w = p.w * r.w - p.x * r.x - p.y * r.y - p.z * r.z;
        x = p.w * r.x + p.x * r.w + p.y * r.z - p.z * r.y;
        y = p.w * r.y + p.y * r.w + p.z * r.x - p.x * r.z;
        z = p.w * r.z + p.z * r.w + p.x * r.y - p.y * r.x;

        return *this;
	}
	Quat& Quat::operator*=(float f)
	{
        w *= f;
        x *= f;
        y *= f;
        z *= f;
        return *this;
	}
	Quat& Quat::operator/=(float f)
	{
        w /= f;
        x /= f;
        y /= f;
        z /= f;
        return *this;
	}

	Quat operator-(Quat const& q)
	{
		return Quat(-q.w, -q.x, -q.y, -q.z);
	}
	Quat operator+(Quat const& q1, Quat const& q2)
	{
		return Quat(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z);
	}
	Quat operator-(Quat const& q1, Quat const& q2)
	{
		return Quat(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z);
	}
	Quat operator*(Quat const& q1, Quat const& q2)
	{
        return Quat(
            q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
            q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
            q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
            q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
	}
	Vec3 operator*(Quat const& q, Vec3 const& v)
	{
        Vec3 const QuatVector(q.x, q.y, q.z);
        Vec3 const uv(Vec3::Cross(QuatVector, v));
        Vec3 const uuv(Vec3::Cross(QuatVector, uv));
        return v + ((uv * q.w) + uuv) * 2.0f;
    }

	Vec4 operator*(Quat const& q, Vec4 const& v)
	{
        return (q * Vec3(v.x, v.y, v.z), v.w);
	}
	Vec4 operator*(Vec4 const& v, Quat const& q)
	{
        return Quat::inverse(q) * v;
	}
	Quat operator*(Quat const& q, float const& f)
	{
        return Quat(q.w * f, q.x * f, q.y * f, q.z * f);
	}
	Quat operator*(float const& f, Quat const& q)
	{
        return q * f;
	}
	Quat operator/(Quat const& q, float const& f)
	{
        return Quat(q.w / f, q.x / f, q.y / f, q.z / f);
	}
	bool operator==(Quat const& q1, Quat const& q2)
	{
		return q1.w == q2.w && q1.x == q2.x && q1.y == q2.y && q1.z == q2.z;
	}
	bool operator!=(Quat const& q1, Quat const& q2)
	{
		return q1.w != q2.w || q1.x != q2.x || q1.y != q2.y || q1.z != q2.z;
	}
} // namespace WD