#include "Geometry.h"

namespace TDS
{

bool Geometry::TestAABBAABB(const AABB &a, const AABB &b)
{
    if (a.isNull() || b.isNull())
        return false;

    // Exit with no intersection if separated along an axis
    if (a.getMax().x < b.getMin().x || a.getMin().x > b.getMax().x)
        return false;
    if (a.getMax().y < b.getMin().y || a.getMin().y > b.getMax().y)
        return false;
    if (a.getMax().z < b.getMin().z || a.getMin().z > b.getMax().z)
        return false;

    // Overlapping on all axes means AABBs are intersecting
    return true;
}

bool Geometry::TestSpherePlane(const Sphere &s, const Plane &p)
{
    float dist = Vec3::Dot(s.getCenter(), p.getNormal()) - p.getD();
    return Mathf::Abs(dist) <= s.getRadius();
}

bool Geometry::InsideSpherePlane(const Sphere &s, const Plane &p)
{
    float dist = Vec3::Dot(s.getCenter(), p.getNormal()) - p.getD();
    return dist < s.getRadius();
}

bool Geometry::TestAABBPlane(const AABB &b, const Plane &p)
{
    Vec3 c = b.getCenter();
    Vec3 e = b.getExtent();
    // Compute the projection interval 
    float r = e.x * Mathf::Abs(p.getNormal().x) + e.y * Mathf::Abs(p.getNormal().y) + e.z * Mathf::Abs(p.getNormal().z);
    // Compute distance of box center from plane
    float s = Vec3::Dot(p.getNormal(), c) - p.getD();
    return Mathf::Abs(s) <= r;
}

bool Geometry::TestSphereAABB(const Sphere &s, const AABB &b)
{
    AABB aabb;
    float sqDist = aabb.SqrDistPointAABB(s.getCenter(), b);
    return sqDist <= (s.getRadius() * s.getRadius());
}

bool Geometry::TestSphereAABB(const Sphere &s, const AABB &b, Vec3 &p)
{
    AABB aabb;
    aabb.ClosestPtPointAABB(s.getCenter(), b, p);
    Vec3 v = p - s.getCenter();
    return Vec3::Dot(v,v) <= (s.getRadius() * s.getRadius());
}

bool Geometry::TestTriAABB(const Tri& tri, const AABB &b)
{
    float p0, p1, p2, r;
    // compute edge vectors for triangle
    Tri tempTri;
    tempTri.setPoints(tri.getPoint(0) - b.getCenter(), 
                    tri.getPoint(1) - b.getCenter(), 
                    tri.getPoint(2) - b.getCenter());

    Vec3 f0 = tempTri.getPoint(1) - tempTri.getPoint(0);
    Vec3 f1 = tempTri.getPoint(2) - tempTri.getPoint(1);
    Vec3 f2 = tempTri.getPoint(0) - tempTri.getPoint(2);

    // test axes a00..a22 (category 3)
    // test axis a00
    p0 = tempTri.getPoint(0).z * tempTri.getPoint(1).y - tempTri.getPoint(0).y * tempTri.getPoint(1).z;
    p2 = tempTri.getPoint(2).z * (tempTri.getPoint(1).y - tempTri.getPoint(0).y) - tempTri.getPoint(2).y * (tempTri.getPoint(1).z - tempTri.getPoint(0).z);
    r = b.getExtent().y * Mathf::Abs(f0.z) + b.getExtent().z * Mathf::Abs(f0.y);
    if (Mathf::Max(-Mathf::Max(p0, p2), Mathf::Min(p0, p2)) > r)
        return false;

    // test axis a01
    p0 = tempTri.getPoint(0).z * tempTri.getPoint(1).x - tempTri.getPoint(0).x * tempTri.getPoint(1).z;
    p2 = tempTri.getPoint(2).z * (tempTri.getPoint(1).x - tempTri.getPoint(0).x) - tempTri.getPoint(2).x * (tempTri.getPoint(1).z - tempTri.getPoint(0).z);
    r = b.getExtent().x * Mathf::Abs(f0.z) + b.getExtent().z * Mathf::Abs(f0.x);
    if (Mathf::Max(-Mathf::Max(p0, p2), Mathf::Min(p0, p2)) > r)
        return false;

    // test axis a02
    p1 = tempTri.getPoint(0).y * tempTri.getPoint(1).x - tempTri.getPoint(0).x * tempTri.getPoint(1).y;
    p2 = tempTri.getPoint(2).y * (tempTri.getPoint(1).x - tempTri.getPoint(0).x) - tempTri.getPoint(2).x * (tempTri.getPoint(1).y - tempTri.getPoint(0).y);
    r = b.getExtent().x * Mathf::Abs(f0.y) + b.getExtent().y * Mathf::Abs(f0.x);
    if (Mathf::Max(-Mathf::Max(p0, p2), Mathf::Min(p0, p2)) > r)
        return false;

    // test axis a10
    p0 = tempTri.getPoint(0).z * tempTri.getPoint(2).y - tempTri.getPoint(0).y * tempTri.getPoint(2).z;
    p2 = tempTri.getPoint(1).z * (tempTri.getPoint(2).y - tempTri.getPoint(0).y) - tempTri.getPoint(1).y * (tempTri.getPoint(2).z - tempTri.getPoint(0).z);
    r = b.getExtent().y * Mathf::Abs(f1.z) + b.getExtent().z * Mathf::Abs(f1.y);
    if (Mathf::Max(-Mathf::Max(p0, p2), Mathf::Min(p0, p2)) > r)
        return false;

    // test axis a11
    p0 = tempTri.getPoint(0).z * tempTri.getPoint(2).x - tempTri.getPoint(0).x * tempTri.getPoint(2).z;
    p2 = tempTri.getPoint(1).z * (tempTri.getPoint(2).x - tempTri.getPoint(0).x) - tempTri.getPoint(1).x * (tempTri.getPoint(2).z - tempTri.getPoint(0).z);
    r = b.getExtent().x * Mathf::Abs(f1.z) + b.getExtent().z * Mathf::Abs(f1.x);
    if (Mathf::Max(-Mathf::Max(p0, p2), Mathf::Min(p0, p2)) > r)
        return false;

    // test axis a12
    p0 = tempTri.getPoint(0).y * tempTri.getPoint(2).x - tempTri.getPoint(0).x * tempTri.getPoint(2).y;
    p1 = tempTri.getPoint(1).y * (tempTri.getPoint(2).x - tempTri.getPoint(0).x) - tempTri.getPoint(1).x * (tempTri.getPoint(2).y - tempTri.getPoint(0).y);
    r = b.getExtent().x * Mathf::Abs(f1.y) + b.getExtent().y * Mathf::Abs(f1.x);
    if (Mathf::Max(-Mathf::Max(p0, p1), Mathf::Min(p0, p1)) > r)
        return false;

    // test axis a20
    p0 = tempTri.getPoint(1).z * tempTri.getPoint(2).y - tempTri.getPoint(1).y * tempTri.getPoint(2).z;
    p1 = tempTri.getPoint(0).z * (tempTri.getPoint(2).y - tempTri.getPoint(1).y) - tempTri.getPoint(0).y * (tempTri.getPoint(2).z - tempTri.getPoint(1).z);
    r = b.getExtent().y * Mathf::Abs(f2.z) + b.getExtent().z * Mathf::Abs(f2.y);
    if (Mathf::Max(-Mathf::Max(p0, p1), Mathf::Min(p0, p1)) > r)
        return false;

    // test axis a21
    p0 = tempTri.getPoint(1).z * tempTri.getPoint(2).x - tempTri.getPoint(1).x * tempTri.getPoint(2).z;
    p1 = tempTri.getPoint(0).z * (tempTri.getPoint(2).x - tempTri.getPoint(1).x) - tempTri.getPoint(0).x * (tempTri.getPoint(2).z - tempTri.getPoint(1).z);
    r = b.getExtent().x * Mathf::Abs(f2.z) + b.getExtent().z * Mathf::Abs(f2.x);
    if (Mathf::Max(-Mathf::Max(p0, p1), Mathf::Min(p0, p1)) > r)
        return false;

    // test axis a22
    p0 = tempTri.getPoint(1).y * tempTri.getPoint(2).x - tempTri.getPoint(1).x * tempTri.getPoint(2).y;
    p1 = tempTri.getPoint(0).y * (tempTri.getPoint(2).x - tempTri.getPoint(1).x) - tempTri.getPoint(0).x * (tempTri.getPoint(2).y - tempTri.getPoint(1).y);
    r = b.getExtent().x * Mathf::Abs(f2.y) + b.getExtent().y * Mathf::Abs(f2.x);
    if (Mathf::Max(-Mathf::Max(p0, p1), Mathf::Min(p0, p1)) > r)
        return false;

    // test the three axes corresponding to the face normals of AABB b (category 1)
    // exit if...
    // ... [-extents[0], extents[0]] and [min[0], max[0]] do not overlap
    if (Mathf::Max(tempTri.getPoint(0).x, tempTri.getPoint(1).x, tempTri.getPoint(2).x) < -b.getExtent().x || Mathf::Min(tempTri.getPoint(0).x, tempTri.getPoint(1).x, tempTri.getPoint(2).x) > b.getExtent().x)
        return false;

    // ... [-extents[1], extents[1]] and [min[1], max[1]] do not overlap
    if (Mathf::Max(tempTri.getPoint(0).y, tempTri.getPoint(1).y, tempTri.getPoint(2).y) < -b.getExtent().y || Mathf::Min(tempTri.getPoint(0).y, tempTri.getPoint(1).y, tempTri.getPoint(2).y) > b.getExtent().y)
        return false;

    // ... [-extents[2], extents[2]] and [min[2], max[2]] do not overlap
    if (Mathf::Max(tempTri.getPoint(0).z, tempTri.getPoint(1).z, tempTri.getPoint(2).z) < -b.getExtent().z || Mathf::Min(tempTri.getPoint(0).z, tempTri.getPoint(1).z, tempTri.getPoint(2).z) > b.getExtent().z)
        return false;

    // test separating axis corresponding to triangle face normal (category 2)
    Plane p;
    p.setNormal(Vec3::Cross(f0, f1));
    p.setD(Vec3::Dot(p.getNormal(), tempTri.getPoint(0)));
    return TestAABBPlane(b, p);   
}

bool Geometry::TestTriTri(const Tri &V, const Tri &U)
{
    Vec3 E1, E2;
    Vec3 N1, N2;
    float d1, d2;
    float du0, du1, du2, dv0, dv1, dv2;
    Vec3 D;
    float isect1[2], isect2[2];
    float du0du1, du0du2, dv0dv1, dv0dv2;
    short index;
    float vp0, vp1, vp2;
    float up0, up1, up2;
    float bb, cc, max;
    
    // compute plane equation of triangle(V0,V1,V2)
    E1 = V.getPoint(1) - V.getPoint(0);
    E2 = V.getPoint(2) - V.getPoint(0);
    N1 = Vec3::Cross(E1, E2);
    d1 = -Vec3::Dot(N1, V.getPoint(0));
    // plane equation 1: N1.X+d1=0

    // put U0,U1,U2 into plane equation 1 to compute signed distances to the plane
    du0 = Vec3::Dot(N1, U.getPoint(0)) + d1;
    du1 = Vec3::Dot(N1, U.getPoint(1)) + d1;
    du2 = Vec3::Dot(N1, U.getPoint(2)) + d1;

    // coplanarity robustness check
    if (Mathf::Abs(du0) < Mathf::Epsilon) du0 = 0.0f;
    if (Mathf::Abs(du1) < Mathf::Epsilon) du1 = 0.0f;
    if (Mathf::Abs(du2) < Mathf::Epsilon) du2 = 0.0f;
    du0du1 = du0 * du1;
    du0du2 = du0 * du2;

    if (du0du1 > 0.0f && du0du2 > 0.0f) // same sign on all of them + not equal 0 ?
        return false; // no intersection occurs

    // compute plane of triangle (U0,U1,U2)
    E1 = U.getPoint(1) - U.getPoint(0);
    E2 = U.getPoint(2) - U.getPoint(0);
    N2 = Vec3::Cross(E1, E2);
    d2 = -Vec3::Dot(N2, U.getPoint(0));
    // plane equation 2: N2.X+d2=0

    // put V0,V1,V2 into plane equation 2
    dv0 = Vec3::Dot(N2, V.getPoint(0)) + d2;
    dv1 = Vec3::Dot(N2, V.getPoint(1)) + d2;
    dv2 = Vec3::Dot(N2, V.getPoint(2)) + d2;

    if (Mathf::Abs(dv0) < Mathf::Epsilon) dv0 = 0.0f;
    if (Mathf::Abs(dv1) < Mathf::Epsilon) dv1 = 0.0f;
    if (Mathf::Abs(dv2) < Mathf::Epsilon) dv2 = 0.0f;

    dv0dv1 = dv0 * dv1;
    dv0dv2 = dv0 * dv2;

    if (dv0dv1 > 0.0f && dv0dv2 > 0.0f) // same sign on all of them + not equal 0 ?
        return false; // no intersection occurs

    // compute direction of intersection line
    D = Vec3::Cross(N1, N2);

    // compute and index to the largest component of D
    max = Mathf::Abs(D[0]);
    index = 0;
    bb = Mathf::Abs(D[1]);
    cc = Mathf::Abs(D[2]);
    if (bb > max) max = bb, index = 1;
    if (cc > max) max = cc, index = 2;

    // this is the simplified projection onto L
    vp0 = V.getPoint(0)[index];
    vp1 = V.getPoint(1)[index];
    vp2 = V.getPoint(2)[index];

    up0 = U.getPoint(0)[index];
    up1 = U.getPoint(1)[index];
    up2 = U.getPoint(2)[index];

    // compute interval for triangle 1
    float a, b, c, x0, x1;
    if (Tri::ComputeInterval(vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, a, b, c, x0, x1) == true)
    {
        if (Tri::CoplanarTri(N1, V, U)) return true;
    }
    // compute interval for triangle 2
    float d, e, f, y0, y1;
    if (Tri::ComputeInterval(up0, up1, up2, du0, du1, du2, du0du1, du0du2, d, e, f, y0, y1) == true)
    {
        if (Tri::CoplanarTri(N1, V, U)) return true;
    }

    float xx, yy, xxyy, tmp;
    xx = x0 * x1;
    yy = y0 * y1;
    xxyy = xx * yy;

    tmp = a * xxyy;
    isect1[0] = tmp + b * x1 * yy;
    isect1[1] = tmp + c * x0 * yy;

    tmp = d * xxyy;
    isect2[0] = tmp + e * xx * y1;
    isect2[1] = tmp + f * xx * y0;

    if (isect1[0] > isect1[1])
    {
        float tmp1 = isect1[0];
        isect1[0] = isect1[1];
        isect1[1] = tmp1;
    }

    if (isect2[0] > isect2[1])
    {
        float tmp2 = isect2[0];
        isect2[0] = isect2[1];
        isect2[1] = tmp2;
    }

    if (isect1[1] < isect2[0] || isect2[1] < isect1[0]) return false;
    return true;
    
}

bool Geometry::TestSphereSphere(const Sphere &sphere1, const Sphere &sphere2)
{
    // Calculate squared distance between centers
    Vec3 diff = sphere1.getCenter() - sphere2.getCenter();
    float sqDist = Vec3::Dot(diff, diff);
    // Spheres intersect if squared distance is less than squared sum of radii
    float sumRadii = sphere1.getRadius() + sphere2.getRadius();
    return sqDist <= sumRadii * sumRadii;
}

bool Geometry::IntersectRaySphere(const Ray &ray, const Sphere &sphere, float &tmin, Vec3 &q)
{
    Vec3 m = ray.getOrigin() - sphere.getCenter();
    float c = Vec3::Dot(m, m) - sphere.getRadius() * sphere.getRadius();
    // If there is definitely at least one real root, there must be an intersection
    if (c <= 0.0f) return true;
    float b = Vec3::Dot(m, ray.getDirection());
    // Early exit if ray origin outside sphere and ray pointing away from sphere
    if (b > 0.0f) return false;
    float disc = b * b - c;
    // A negative discriminant corresponds to ray missing sphere
    if (disc < 0.0f) return false;
    // Ray now found to intersect sphere, compute smallest t value of intersection
    tmin = -b - Mathf::Sqrt(disc);
    // If tmin is negative, ray started inside sphere so clamp t to zero
    if (tmin < 0.0f) tmin = 0.0f;
    q = ray.getOrigin() + ray.getDirection() * tmin;
    return true;
}

bool Geometry::IntersectRayAABB(const Ray &ray, const AABB &aabb, float& tmin, Vec3& q)
{
    tmin = 0.0f;
    float tmax = Mathf::Infinity;
    for (int i = 0; i < 3; i++)
    {
        if (Mathf::Abs(ray.getDirection()[i]) < Mathf::Epsilon)
        {
            // Ray is parallel to slab. No hit if origin not within slab
            if (ray.getOrigin()[i] < aabb.getMin()[i] || ray.getOrigin()[i] > aabb.getMax()[i])
                return false;
        }
        else
        {
            // Compute intersection t value of ray with near and far plane of slab
            float ood = 1.0f / ray.getDirection()[i];
            float t1 = (aabb.getMin()[i] - ray.getOrigin()[i]) * ood;
            float t2 = (aabb.getMax()[i] - ray.getOrigin()[i]) * ood;
            // Make t1 be intersection with near plane, t2 with far plane
            if (t1 > t2)
            {
                float temp = t1;
                t1 = t2;
                t2 = temp;
            }
            // Compute the intersection of slab intersection intervals
            if (t1 > tmin) tmin = t1;
            if (t2 < tmax) tmax = t2;
            // Exit with no collision as soon as slab intersection becomes empty
            if (tmin > tmax) return false;
        }
    }
    // Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin)
    q = ray.getOrigin() + ray.getDirection() * tmin;
    return true;
}

bool Geometry::IntersectSegmentPlane(const Vec3 &a, const Vec3 &b, const Plane &p, float &t, Vec3 &q)
{
    // Compute the t value for the directed line ab intersecting the plane
    Vec3 ab = b - a;
    t = (p.getD() - Vec3::Dot(p.getNormal(), a)) / Vec3::Dot(p.getNormal(), ab);
    // If t in [0..1] compute and return intersection point
    if (t >= 0.0f && t <= 1.0f)
    {
        q = a + ab * t;
        return true;
    }
    // Else no intersection
    return false;
}

bool Geometry::IntersectSegmentAABB(const Vec3& p0, const Vec3& p1, const AABB& b)
{
    // Get line midpoint and extents
    Vec3 m = p0 + p1 - b.getMin() - b.getMax();
    Vec3 d = p1 - p0;
    // try world coordinate axes as separating axes
    float adx = Mathf::Abs(d.x);
    if (Mathf::Abs(m.x) > b.getExtent().x + adx) return false;
    float ady = Mathf::Abs(d.y);
    if (Mathf::Abs(m.y) > b.getExtent().y + ady) return false;
    float adz = Mathf::Abs(d.z);
    if (Mathf::Abs(m.z) > b.getExtent().z + adz) return false;
    // Add in an epsilon term to counteract arithmetic errors when segment is
    // (near) parallel to a coordinate axis (see text for detail)
    adx += Mathf::Epsilon; ady += Mathf::Epsilon; adz += Mathf::Epsilon;
    // Try cross products of segment direction vector with coordinate axes
    if (Mathf::Abs(m.y * d.z - m.z * d.y) > b.getExtent().y * adz + b.getExtent().z * ady) return false;
    if (Mathf::Abs(m.z * d.x - m.x * d.z) > b.getExtent().x * adz + b.getExtent().z * adx) return false;
    if (Mathf::Abs(m.x * d.y - m.y * d.x) > b.getExtent().x * ady + b.getExtent().y * adx) return false;
    // No separating axis found; segment must be overlapping AABB
    return true;
}

bool Geometry::IntersectLineTriangle(const Vec3 &p, const Vec3 &q, const Tri &tri, Vec3 &intersectPt)
{
    intersectPt = Vec3::zero();
    Vec3 pq = q - p;
    Vec3 pa = tri.getPoint(0) - p;
    Vec3 pb = tri.getPoint(1) - p;
    Vec3 pc = tri.getPoint(2) - p;
    // Test if pq is inside the edges bc, ca and ab.
    Vec3 m = Vec3::Cross(pq, q);
    float s = Vec3::Dot(m, tri.getPoint(2) - tri.getPoint(1));
    float t = Vec3::Dot(m, tri.getPoint(0) - tri.getPoint(2));
    float u = Vec3::Dot(pq, Vec3::Cross(tri.getPoint(2), tri.getPoint(1))) + s;
    if (u < 0.0f) return false;
    float v = Vec3::Dot(pq, Vec3::Cross(tri.getPoint(0), tri.getPoint(2))) + t;
    if (v < 0.0f) return false;
    float w = Vec3::Dot(pq, Vec3::Cross(tri.getPoint(1), tri.getPoint(0))) -s -t;
    if (w < 0.0f) return false;

    // compute the barycentric coordinates (u, v, w) determining the
    // intersection point r, r = u*a + v*b + w*c
    float denom = 1.0f / (u + v + w);
    u *= denom;
    v *= denom;
    w *= denom; // w = 1.0f - u - v;
    intersectPt = u * tri.getPoint(0) + v * tri.getPoint(1) + w * tri.getPoint(2);
    return true;
}

bool Geometry::IntersectRayTriangle(const Ray& ray, const Tri& tri, Vec3& intersectPt, float& t)
{
    intersectPt = Vec3::zero();
    t = 0.0f;
    Vec3 pq = ray.getDirection();
    Vec3 ab = tri.getPoint(1) - tri.getPoint(0);
    Vec3 ac = tri.getPoint(2) - tri.getPoint(0);

    // Compute triangle normal. Can be precalculated or cached if
    // intersecting multiple segments against the same triangle
    Vec3 n = Vec3::Cross(ab, ac);

    // Compute denominator d. If d <= 0, segment is parallel to or points
    // away from triangle, so exit early
    float d = Vec3::Dot(pq, n);
    if (d <= 0.0f) return false;

    // Compute intersection t value of pq with plane of triangle. A ray
    // intersects iff 0 <= t. Segment intersects iff 0 <= t <= 1. Delay
    // dividing by d until intersection has been found to pierce triangle
    Vec3 ap = ray.getOrigin() - tri.getPoint(0);
    t = Vec3::Dot(ap, n);
    if (t < 0.0f) return false;

    // Compute barycentric coordinate components and test if within bounds
    Vec3 e = Vec3::Cross(pq, ap);
    float v = Vec3::Dot(ac, e);
    if (v < 0.0f || v > d) return false;
    float w = -Vec3::Dot(ab, e);
    if (w < 0.0f || v + w > d) return false;

    // Segment/ray intersects triangle. Perform delayed division and
    // compute the last barycentric coordinate component
    float ood = 1.0f / d;
    t *= ood; 
    v *= ood;
    w *= ood;
    float u = 1.0f - v - w;
    intersectPt = u * tri.getPoint(0) + v * tri.getPoint(1) + w * tri.getPoint(2);
    return true;

}

bool Geometry::IntersectMovingSphereSphere(const Sphere &s0, const Sphere &s1, const Vec3 &dir, float t0, float t1,
                                           float &t)
{
    // Compute sphere bounding motion of s0 during time interval [t0, t1]
    Sphere b;
    float mid = (t0 + t1) * 0.5f;
    b.setCenter(s0.getCenter() + dir * mid);
    b.setRadius((mid - t0) * Vec3::Magnitude(dir) + s0.getRadius());
    // If bounding spheres do not overlap, no collision and no intersection
    if (!TestSphereSphere(b, s1)) return false;

    // Recursive termination criterion. If the bounding spheres overlap at time
    // t0, then the spheres intersect at time t0
    if (t1 - t0 < Mathf::Epsilon)
    {
        t = t0;
        return true;
    }

    // Recursively test first half of interval, return collision if detected
    if (IntersectMovingSphereSphere(s0, s1, dir, t0, mid, t)) return true;

    // Recursively test second half of interval, return collision if detected
    return IntersectMovingSphereSphere(s0, s1, dir, mid, t1, t);
}

bool Geometry::IntersectMovingSphereSphere(const Sphere &s0, const Sphere &s1, const Vec3 &dir0, const Vec3 &dir1,
                                           float &t)
{
    // Vector between sphere centers at t = 0
    Vec3 s = s1.getCenter() - s0.getCenter();
    // Vector between sphere centers in relative motion
    Vec3 v = dir1 - dir0;
    float r = s1.getRadius() + s0.getRadius();
    float c = Vec3::Dot(s, s) - r * r;
    if (c < 0.0f)
    {
        // Spheres initially overlapping, exit directly
        t = 0.0f;
        return true;
    }
    float a = Vec3::Dot(v, v);
    if (a < Mathf::Epsilon)
        return false; // Spheres not moving relative each other
    float b = Vec3::Dot(v, s);
    if (b >= 0.0f)
        return false; // Spheres not moving towards each other
    float d = b * b - a * c;
    if (d < 0.0f)
        return false; // No real-valued root, spheres do not intersect
    t = (-b - Mathf::Sqrt(d)) / a;
    return true;

}

bool Geometry::IntersectMovingSpherePlane(const Sphere& s, const Vec3& dir, const Plane& p, float& t, Vec3& q)
{
    // Compute distance of sphere center to plane
    float dist = Vec3::Dot(p.getNormal(), s.getCenter()) - p.getD();
    if (Mathf::Abs(dist) <= s.getRadius())
    {
        // The sphere is already overlapping the plane. Set time of
        // intersection to zero and q to sphere center
        t = 0.0f;
        q = s.getCenter();
        return true;
    }
    else
    {
        float denom = Vec3::Dot(p.getNormal(), dir);
        if (denom * dist >= 0.0f)
        {
            // No intersection as sphere moving parallel to or away from plane
            return false;
        }
        else
        {
            // Sphere is moving towards the plane
            // Use +r in computations if sphere in front of plane, else -r
            float r = dist > 0.0f ? s.getRadius() : -s.getRadius();
            t = (r - dist) / denom;
            q = s.getCenter() + dir * t - p.getNormal() * r;
            return true;
        }
    }
}

bool Geometry::IntersectMovingSpherePlane(const Vec3 &a, const Vec3 &b, const Sphere &s, const Plane &p)
{
    // get the distance for both a and b from plane p
    float adist = Vec3::Dot(a, p.getNormal()) - p.getD();
    float bdist = Vec3::Dot(b, p.getNormal()) - p.getD();
    // Intersects if on different sides of plane (distances have different signs)
    if (adist * bdist < 0.0f)
        return true;
    // Intersects if start or end position within radius from plane
    if (Mathf::Abs(adist) <= s.getRadius() || Mathf::Abs(bdist) <= s.getRadius())
        return true;
    return false;
}

bool Geometry::IntersectMovingAABBAABB(const AABB &a, const Vec3 &va, const AABB &b, const Vec3 &vb, float &tfirst,
                                       float &tlast)
{
    // Exit early if the two AABBs are already overlapping
    if (TestAABBAABB(a, b))
    {
        tfirst = tlast = 0.0f;
        return true;
    }
    // Use relative velocity; effectively treating 'a' as stationary
    Vec3 v = vb - va;
    // Initialize times of first and last contact
    tfirst = 0.0f;
    tlast = 1.0f;
    // For each axis, determine times of first and last contact, if any
    for (int i = 0; i < 3; i++)
    {
        if (v[i] < 0.0f)
        {
            if (b.getMax()[i] < a.getMin()[i])
                return false; // Nonintersecting and moving apart
            if (a.getMax()[i] < b.getMin()[i])
                tfirst = Mathf::Max((a.getMax()[i] - b.getMin()[i]) / v[i], tfirst);
            if (b.getMax()[i] > a.getMin()[i])
                tlast = Mathf::Min((a.getMin()[i] - b.getMax()[i]) / v[i], tlast);
        }
        if (v[i] > 0.0f)
        {
            if (b.getMin()[i] > a.getMax()[i])
                return false; // Nonintersecting and moving apart
            if (b.getMax()[i] < a.getMin()[i])
                tfirst = Mathf::Max((a.getMin()[i] - b.getMax()[i]) / v[i], tfirst);
            if (a.getMax()[i] > b.getMin()[i])
                tlast = Mathf::Min((a.getMax()[i] - b.getMin()[i]) / v[i], tlast);
        }
        // No overlap possible if time of first contact occurs after time of last contact
        if (tfirst > tlast)
            return false;
    }
    return true;
}

} // namespace TDS