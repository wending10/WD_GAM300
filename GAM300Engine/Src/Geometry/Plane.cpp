#include "Plane.h"

namespace TDS
{

Plane::Plane() : n(0.0), d(0.0) {}
Plane::Plane(const Vec3& normal, float new_d)
{
    // ensure normal is normalized
    n = Vec3::Normalize(normal);
    d = new_d;

}
Plane::Plane(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3)
{
    ComputePlane(p1, p2, p3);
}
Plane::~Plane() {}

Plane Plane::ComputePlane(Vec3 p1, Vec3 p2, Vec3 p3)
{
    Plane p;
    p.n = Vec3::Normalize(Vec3::Cross(p2 - p1, p3 - p1));
    p.d = Vec3::Dot(p.n, p1);
    return p;
}

Vec3 Plane::ClosestPointOnPlane(Vec3 point, Plane plane)
{
    float t = Vec3::Dot(plane.n, point) - plane.d;
    return point - t * plane.n;
}

float Plane::DistanceToPlane(Vec3 point, Plane plane)
{
    return (Vec3::Dot(plane.getNormal(), point) - plane.getD()) / Vec3::Dot(plane.getNormal(), plane.getNormal());
}

} // namespace TDS