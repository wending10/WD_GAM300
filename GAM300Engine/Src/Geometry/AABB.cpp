#include "AABB.h"

namespace TDS
{

AABB::AABB()
{
    setNull();
}

AABB::AABB(const Vec3 &center, float radius)
{
    setNull();
    extend(center, radius);
}

AABB::AABB(const Vec3 &p1, const Vec3 &p2)
{
    setNull();
    extend(p1);
    extend(p2);
}

AABB::AABB(const AABB &aabb)
{
    setNull();
    extend(aabb);
}

AABB::~AABB()
{
}

void AABB::extend(float value)
{
    if (!isNull())
    {
        m_min -= Vec3(value);
        m_max -= Vec3(value);
    }
}

void AABB::extend(const Vec3 &pt)
{
    if (!isNull())
    {
        m_min = Vec3::Min(m_min, pt);
        m_max = Vec3::Max(m_max, pt);
    }
    else
    {
        m_min = pt;
        m_max = pt;
    }
}

void AABB::extend(const Vec3 &pt, float radius)
{
    Vec3 r(radius);
    if (!isNull())
    {
        m_min = Vec3::Min(m_min, pt - r);
        m_max = Vec3::Max(m_max, pt + r);
    }
    else
    {
        m_min = pt - r;
        m_max = pt + r;
    }
}

void AABB::extend(const AABB &aabb)
{
    if (!aabb.isNull())
    {
        extend(aabb.m_min);
        extend(aabb.m_max);
    }
}

void AABB::extendDisk(const Vec3 &center, const Vec3 &normal, float radius)
{
    Vec3 n(normal);
    if (n.magnitude() < Mathf::Epsilon)
    {
        extend(center);
        return;
    }
    Vec3 norm = n.normalize();
    float x = Mathf::Sqrt(1.f - norm.x) * radius;
    float y = Mathf::Sqrt(1.f - norm.y) * radius;
    float z = Mathf::Sqrt(1.f - norm.z) * radius;
    extend(center + Vec3(x, y, z));
    extend(center - Vec3(x, y, z));
}

Vec3 AABB::getDiagonal() const
{
    if (!isNull())
        return m_max - m_min;
    return Vec3(0.0f);
}

Vec3 AABB::getSize() const
{
    if (!isNull())
        return m_max - m_min;
    return Vec3(0.0f);
}

Vec3 AABB::getExtent() const
{
    if (!isNull())
        return (m_max - m_min) * 0.5f;
    return Vec3(0.0f);
}

float AABB::getLongestEdge() const
{
    Vec3 diag = getDiagonal();
    return Mathf::Max(diag.x, diag.y, diag.z);
}

float AABB::getShortestEdge() const
{
    Vec3 diag = getDiagonal();
    return Mathf::Min(diag.x, diag.y, diag.z);
}

Vec3 AABB::getCenter() const
{
    if (!isNull())
    {
        Vec3 diag = getDiagonal();
        return m_min + (diag * 0.5f);
    }
    return Vec3(0.0f);
}

void AABB::translate(const Vec3 &v)
{
    if (!isNull())
    {
        m_min += v;
        m_max += v;
    }
}

void AABB::scale(const Vec3 &scale, const Vec3 &origin)
{
    if (!isNull())
    {
        m_min = (m_min - origin) * scale + origin;
        m_max = (m_max - origin) * scale + origin;
    }
}

bool AABB::contains(const Vec3 &pt) const
{
    if (!isNull())
    {
        return (pt.x >= m_min.x && pt.x <= m_max.x && 
                pt.y >= m_min.y && pt.y <= m_max.y && 
                pt.z >= m_min.z && pt.z <= m_max.z);
    }
    return false;
}

void AABB::ClosestPtPointAABB(const Vec3 &p, AABB box, Vec3 &q)
{
    if (p.x < box.m_min.x)
        q.x = box.m_min.x;
    else if (p.x > box.m_max.x)
        q.x = box.m_max.x;
    else
        q.x = p.x;

    if (p.y < box.m_min.y)
        q.y = box.m_min.y;
    else if (p.y > box.m_max.y)
        q.y = box.m_max.y;
    else
        q.y = p.y;

    if (p.z < box.m_min.z)
        q.z = box.m_min.z;
    else if (p.z > box.m_max.z)
        q.z = box.m_max.z;
    else
        q.z = p.z;
}

float AABB::SqrDistPointAABB(const Vec3 &p, const AABB &box)
{
    float sqrDist = 0.0f;
    if (p.x < box.m_min.x)
        sqrDist += (box.m_min.x - p.x) * (box.m_min.x - p.x);
    if (p.x > box.m_max.x)
        sqrDist += (p.x - box.m_max.x) * (p.x - box.m_max.x);

    if (p.y < box.m_min.y)
        sqrDist += (box.m_min.y - p.y) * (box.m_min.y - p.y);
    if (p.y > box.m_max.y)
        sqrDist += (p.y - box.m_max.y) * (p.y - box.m_max.y);

    if (p.z < box.m_min.z)
        sqrDist += (box.m_min.z - p.z) * (box.m_min.z - p.z);
    if (p.z > box.m_max.z)
        sqrDist += (p.z - box.m_max.z) * (p.z - box.m_max.z);

    return sqrDist;
}

} // namespace TDS