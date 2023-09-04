#include "Triangle.h"

namespace TDS
{
Tri::Tri()
{
    p[0] = Vec3::zero();
    p[1] = Vec3::zero();
    p[2] = Vec3::zero();
}
Tri::~Tri()
{
}
Tri::Tri(const Vec3 &p1, const Vec3 &p2, const Vec3 &p3)
{
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
}

bool Tri::contains(const Vec3 &point) const
{
    Vec3 planeNormal = Vec3::Cross(p[1] - p[0], p[2] - p[0]);
    Vec3 edge1, edge2, edge3;
    edge1 = Vec3::Cross(planeNormal, p[1] - p[0]);
    edge2 = Vec3::Cross(planeNormal, p[2] - p[1]);
    edge3 = Vec3::Cross(planeNormal, p[0] - p[2]);
    if (Vec3::Dot(point - p[0], edge1) >= 0.0f && Vec3::Dot(point - p[1], edge2) >= 0.0f &&
        Vec3::Dot(point - p[2], edge3) >= 0.0f)
        return true;
    return false;
}

Vec3 Tri::closestPointOnTri(const Vec3 &point) const
{
    // Check if P in vertex region outside point P0
    Vec3 ab = p[1] - p[0];
    Vec3 ac = p[2] - p[0];
    Vec3 ap = point - p[0];
    float d1 = Vec3::Dot(ab, ap);
    float d2 = Vec3::Dot(ac, ap);
    if (d1 <= 0.0f && d2 <= 0.0f)
        return p[0];

    // Check if P in vertex region outside point P1
    Vec3 bp = point - p[1];
    float d3 = Vec3::Dot(ab, bp);
    float d4 = Vec3::Dot(ac, bp);
    if (d3 >= 0.0f && d4 <= d3)
        return p[1];

    // Check if P in edge region of edge P0-P1
    float vc = d1 * d4 - d3 * d2;
    if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
    {
        float v = d1 / (d1 - d3);
        return p[0] + v * ab;
    }

    // Check if P in vertex region outside point P2
    Vec3 cp = point - p[2];
    float d5 = Vec3::Dot(ab, cp);
    float d6 = Vec3::Dot(ac, cp);
    if (d6 >= 0.0f && d5 <= d6)
        return p[2];

    // Check if P in edge region of edge P0-P2
    float vb = d5 * d2 - d1 * d6;
    if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
    {
        float w = d2 / (d2 - d6);
        return p[0] + w * ac;
    }

    // Check if P in edge region of edge P1-P2, if it is, return projection of P onto edge
    float va = d3 * d6 - d5 * d4;
    if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
    {
        float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
        return p[1] + w * (p[2] - p[1]);
    }

    // P inside face region. Compute Q through its barycentric coordinates (u, v, w)
    float denom = 1.0f / (va + vb + vc);
    float v = vb * denom;
    float w = vc * denom;
    return p[0] + ab * v + ac * w;
}

bool Tri::CoplanarTri(const Vec3 &N, const Tri &V, const Tri &U)
{
    Vec3 A;
    short i0, i1;
    // first project onto an axis-aligned plane, that maximizes the area
    // of the triangles, compute indices: i0,i1.
    A[0] = Mathf::Abs(N[0]);
    A[1] = Mathf::Abs(N[1]);
    A[2] = Mathf::Abs(N[2]);
    if (A[0] > A[1])
    {
        if (A[0] > A[2])
        {
            i0 = 1; // A[0] is greatest
            i1 = 2;
        }
        else
        {
            i0 = 0; // A[2] is greatest
            i1 = 1;
        }
    }
    else // A[0]<=A[1]
    {
        if (A[2] > A[1])
        {
            i0 = 0; // A[2] is greatest
            i1 = 1;
        }
        else
        {
            i0 = 0; // A[1] is greatest
            i1 = 2;
        }
    }

    // test all edges of triangle 1 against the edges of triangle 2
    if (TriEdgeAgainstTriEdge(V.getPoint(0), V.getPoint(1), U.getPoint(0), U.getPoint(1), U.getPoint(2), i0, i1) &&
        TriEdgeAgainstTriEdge(V.getPoint(1), V.getPoint(2), U.getPoint(0), U.getPoint(1), U.getPoint(2), i0, i1) &&
        TriEdgeAgainstTriEdge(V.getPoint(2), V.getPoint(0), U.getPoint(0), U.getPoint(1), U.getPoint(2), i0, i1) == true)
    {
        return true;
    }
    // finally, test if tri1 is totally contained in tri2 or vice versa
    if (TriPointInTri(V.getPoint(0), U.getPoint(0), U.getPoint(1), U.getPoint(2), i0, i1) &&
        TriPointInTri(U.getPoint(0), V.getPoint(0), V.getPoint(1), V.getPoint(2), i0, i1) == true)

    {
        return true;
    }

    return false;
}

bool Tri::TriEdgeEdgeTest(const Vec3 &V0, const Vec3 &U0, const Vec3 &U1, const float Ax, const float Ay,
                          const short i0, const short i1)
{
    float Bx, By;
    float Cx, Cy;
    float e, d, f;

    Bx = U0[i0] - U1[i0];
    By = U0[i1] - U1[i1];
    Cx = V0[i0] - U0[i0];
    Cy = V0[i1] - U0[i1];
    f = Ay * Bx - Ax * By;
    d = By * Cx - Bx * Cy;
    if ((f > 0 && d >= 0 && d <= f) || (f < 0 && d <= 0 && d >= f))
    {
        e = Ax * Cy - Ay * Cx;
        if (f > 0)
        {
            if (e >= 0 && e <= f)
                return true;
        }
        else
        {
            if (e <= 0 && e >= f)
                return true;
        }
    }
    return false;
}

bool Tri::TriEdgeAgainstTriEdge(const Vec3 &V0, const Vec3 &V1, const Vec3 &U0, const Vec3 &U1, const Vec3 &U2,
                                short i0, short i1)
{
    float Ax, Ay;
    Ax = V1[i0] - V0[i0];
    Ay = V1[i1] - V0[i1];

    if (TriEdgeEdgeTest(V0, U0, U1, Ax, Ay, i0, i1) && 
        TriEdgeEdgeTest(V0, U1, U2, Ax, Ay, i0, i1) &&
        TriEdgeEdgeTest(V0, U2, U0, Ax, Ay, i0, i1) == true)
        return true;

    return false;
}

bool Tri::TriPointInTri(const Vec3 &V0, const Vec3 &U0, const Vec3 &U1, const Vec3 &U2, const short i0, const short i1)
{
    float a, b, c, d0, d1, d2;
    // is T1 completly inside T2?
    // check if V0 is inside tri(U0,U1,U2)
    a = U1[i1] - U0[i1];
    b = -(U1[i0] - U0[i0]);
    c = -a * U0[i0] - b * U0[i1];
    d0 = a * V0[i0] + b * V0[i1] + c;

    a = U2[i1] - U1[i1];
    b = -(U2[i0] - U1[i0]);
    c = -a * U1[i0] - b * U1[i1];
    d1 = a * V0[i0] + b * V0[i1] + c;

    a = U0[i1] - U2[i1];
    b = -(U0[i0] - U2[i0]);
    c = -a * U2[i0] - b * U2[i1];
    d2 = a * V0[i0] + b * V0[i1] + c;
    if (d0 * d1 > 0.0f)
    {
        if (d0 * d2 > 0.0f)
            return true;
    }
    return false;
}

bool Tri::ComputeInterval(const float &VV0, const float &VV1, const float &VV2, const float &D0, const float &D1,
                          const float &D2, const float &D0D1, const float &D0D2, float &a, float &b, float &c,
                          float &x0, float &x1)
{
    if (D0D1 > 0.0f)
    {
        // here we know that D0D2<=0.0
        // that is D0, D1 are on the same side, D2 on the other or on the plane
        a = VV2;
        b = (VV0 - VV2) * D2;
        c = (VV1 - VV2) * D2;
        x0 = D2 - D0;
        x1 = D2 - D1;
    }
    else if (D0D2 > 0.0f)
    {
        // here we know that d0d1<=0.0
        a = VV1;
        b = (VV0 - VV1) * D1;
        c = (VV2 - VV1) * D1;
        x0 = D1 - D0;
        x1 = D1 - D2;
    }
    else if (D1 * D2 > 0.0f || D0 != 0.0f)
    {
        // here we know that d0d1<=0.0 or that D0!=0.0
        a = VV0;
        b = (VV1 - VV0) * D0;
        c = (VV2 - VV0) * D0;
        x0 = D0 - D1;
        x1 = D0 - D2;
    }
    else if (D1 != 0.0f)
    {
        a = VV1;
        b = (VV0 - VV1) * D1;
        c = (VV2 - VV1) * D1;
        x0 = D1 - D0;
        x1 = D1 - D2;
    }
    else if (D2 != 0.0f)
    {
        a = VV2;
        b = (VV0 - VV2) * D2;
        c = (VV1 - VV2) * D2;
        x0 = D2 - D0;
        x1 = D2 - D1;
    }
    else
    {
        // triangles are coplanar
        return true;
    }
    return false;
}

} // namespace TDS