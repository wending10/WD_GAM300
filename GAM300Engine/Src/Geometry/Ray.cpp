#include "Ray.h"

namespace TDS
{

Ray::Ray() : m_origin(0.0), m_direction(0.0) {}

Ray::Ray(const Vec3& origin, const Vec3& direction)
{
    m_origin = origin;
    m_direction = Vec3::Normalize(direction);
}

Ray::Ray(const Ray& newRay)
{
	m_origin = newRay.m_origin;
	m_direction = newRay.m_direction;
}

Ray::~Ray() {}

bool Ray::contains(const Vec3& point, float* t) const 
{
    Vec3 pt = point - m_origin;
    Vec3 dir = m_direction;
    if (t == NULL) 
        return false;
    if (Vec3::Dot(point - m_origin, m_direction) >= 0.0f)
    {
        *t = (pt).magnitude() / dir.magnitude();
        return true;
    }
    return false;
}

} // namespace TDS