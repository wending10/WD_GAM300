#include "Sphere.h"

namespace TDS
{
    Sphere::Sphere()
    {
        m_center = Vec3(0.0);
        m_radius = 0.0f;
    }

    Sphere::Sphere(const Vec3& center, float radius)
    {
        m_center = center;
        m_radius = radius;
    }

    Sphere::~Sphere() {}

    void Sphere::extend(const Vec3& point)
    {
        Vec3 dist = (point - m_center).normalize();
        float new_radius = (m_radius + dist.magnitude()) * 0.5f;
        Vec3 new_center = m_center + (dist * (new_radius - m_radius));
        m_radius = new_radius;
        m_center = new_center;
    }

    bool Sphere::contains(const Vec3 &point) const
    {
        return (point - m_center).magnitude() <= m_radius;
    }

    void Sphere::ExtremePointsAlongDirection(const Vec3 &dir, const Vec3 *points, int numPoints, int *imin, int *imax)
    {
        float minProj = Mathf::Infinity;
        float maxProj = -Mathf::Infinity;
        for (int i = 0; i < numPoints; i++)
        {
            float proj = Vec3::Dot(points[i], dir);
            if (proj < minProj)
            {
                minProj = proj;
                *imin = i;
            }
            if (proj > maxProj)
            {
                maxProj = proj;
                *imax = i;
            }
        }
    }

    void Sphere::MostSeparatedPointsOnAABB(int &min, int &max, const Vec3 *points, int numPoints)
    {
        // First find most extreme points along principal axes
        int minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0;
        for (int i = 1; i < numPoints; i++)
        {
            if (points[i].x < points[minx].x) minx = i;
            if (points[i].x > points[maxx].x) maxx = i;
            if (points[i].y < points[miny].y) miny = i;
            if (points[i].y > points[maxy].y) maxy = i;
            if (points[i].z < points[minz].z) minz = i;
            if (points[i].z > points[maxz].z) maxz = i;
        }

        // Compute the squared distances for the three pairs of points
        float dist2x = (points[maxx] - points[minx]).sqrMagnitude();
        float dist2y = (points[maxy] - points[miny]).sqrMagnitude();
        float dist2z = (points[maxz] - points[minz]).sqrMagnitude();

        // Pick the pair (min,max) of points most distant
        min = minx;
        max = maxx;
        if (dist2y > dist2x && dist2y > dist2z)
        {
            max = maxy;
            min = miny;
        }

        if (dist2z > dist2x && dist2z > dist2y)
        {
            max = maxz;
            min = minz;
        }
    }

    void Sphere::SphereFromDistantPoints(Sphere &s, const Vec3 *points, int numPoints)
    {
        int min{}, max{};
        Vec3 newCenter{};
        MostSeparatedPointsOnAABB(min, max, points, numPoints);

        newCenter = (points[min] + points[max]) * 0.5f;
        s.setCenter(newCenter);

        float newRadius = (points[max] - s.getCenter()).sqrMagnitude();
        newRadius = Mathf::Sqrt(newRadius);
        s.setRadius(newRadius);
    }

    void Sphere::SphereOfSphereAndPt(Sphere& s, const Vec3& p)
    {
        Vec3 d = p - s.getCenter();
        float dist2 = d.sqrMagnitude();
        // Only update s if p is outside it
        if (dist2 > s.getRadius() * s.getRadius())
        {
            float dist = Mathf::Sqrt(dist2);
            float newRadius = (s.getRadius() + dist) * 0.5f;
            float k = (newRadius - s.getRadius()) / dist;
            s.setRadius(newRadius);
            s.setCenter(s.getCenter() + d * k);
        }
    }

    void Sphere::RitterSphere(Sphere&s, const Vec3* points, int numPoints)
    {
        // Get sphere encompassing two approximately most distant points
        SphereFromDistantPoints(s, points, numPoints);

        // Grow sphere to include all points
        for (int i = 0; i < numPoints; i++)
            SphereOfSphereAndPt(s, points[i]);
    }

    float Sphere::Variance(const float *x, int n)
    {
        float u = 0.0f;
        for (int i = 0; i < n; i++)
            u += x[i];
        u /= n;
        float s2 = 0.0f;
        for (int i = 0; i < n; i++)
            s2 += (x[i] - u) * (x[i] - u);
        return s2 / n;
    }

    void Sphere::CovarianceMatrix(Mat3 &cov, const Vec3 *points, int numPoints)
    {
        float oon = 1.0f / (float)numPoints;
        Vec3 c = Vec3(0.0f);
        float e00{}, e11{}, e22{}, e01{}, e02{}, e12{};

        // Compute the center of mass (centroid) of the points
        for (int i = 0; i < numPoints; i++)
            c += points[i];
        c *= oon;
        
        // Compute covariance elements
        for (int i = 0; i < numPoints; i++)
        {
            Vec3 p = points[i] - c;
            e00 += p.x * p.x;
            e11 += p.y * p.y;
            e22 += p.z * p.z;
            e01 += p.x * p.y;
            e02 += p.x * p.z;
            e12 += p.y * p.z;
        }

        // Fill in the covariance matrix elements
        cov.m[0][0] = e00 * oon;
        cov.m[1][1] = e11 * oon;
        cov.m[2][2] = e22 * oon;
        cov.m[0][1] = cov.m[1][0] = e01 * oon;
        cov.m[0][2] = cov.m[2][0] = e02 * oon;
        cov.m[1][2] = cov.m[2][1] = e12 * oon;
    }

    void Sphere::SymSchur2(Mat3 &A, int p, int q, float &c, float &s)
    {
        // row = p and col = q
        if (Mathf::Abs(A.m[q][p]) > 0.0001f)
        {
            float beta = (A.m[p][p] - A.m[q][q]) / (2.0f * A.m[q][p]);
            float t = Mathf::Sign(beta) / (Mathf::Abs(beta) + Mathf::Sqrt(beta * beta + 1.0f));
            c = 1.0f / Mathf::Sqrt(t * t + 1.0f);
            s = t * c;
        }
        else
        {
            c = 1.0f;
            s = 0.0f;
        }
    }

    void Sphere::Jacobi(Mat3 &a, Mat3 &v)
    {
        // p&i = row, q&j = col
        int i,j,p,q,n;
        float prevoff{}, c{}, s{};
        Mat3 J, b, t;

        // Initialize v to the identity matrix
        v = Mat3::identity();

        // Repeat for some maximum number of iterations
        const int maxIterations = 50;
        for (n = 0; n < maxIterations; n++)
        {   
            // Find largest off-diagonal absolute element a[q][p]
            q = 0; p = 1;
            for (j = 0; j < 3; j++){
                for (i = 0; i < 3; i++){
                    if (i == j) continue;
                    if (Mathf::Abs(a.m[j][i]) > Mathf::Abs(a.m[q][p]))
                    {
                        q = j;
                        p = i;
                    }
                }
            }
        
            // Compute the Jacobi rotation matrix J(p, q, theta)
            SymSchur2(a, p, q, c, s);
            J = Mat3::identity();
            J.m[p][p] = c;
            J.m[q][q] = c;
            J.m[p][q] = -s;
            J.m[q][p] = s;

            // Cumulate rotations into what will contain the eigenvectors
            v = v * J;

            // Transform matrix a to its similar diagonal form by J
            a = (J.transpose()) * a * J;

            // Compute norm of off-diagonal elements
            float off = 0.0f;

            for (j = 0; j < 3; j++)
            {
                for (i = 0; i < 3; i++)
                {
                    if (i == j) continue;
                    off += a.m[j][i] * a.m[j][i];
                }
            }

            // Stop when norm no longer decreasing
            if (n > 2 && off >= prevoff) return;
            prevoff = off;
        }
    }

    void Sphere::EigenSphere(Sphere &eigSphere, const Vec3 *points, int numPoints)
    {
        Mat3 m,v;

        // Compute the covariance matrix
        CovarianceMatrix(m, points, numPoints);
        // Determine eigenvalues and eigenvectors of covariance matrix
        Jacobi(m, v);

        // Find the component with the largest eigenvalue
        Vec3 e;
        int maxc = 0;
        float maxf, maxe = Mathf::Abs(m.m[0][0]);
        if ((maxf = Mathf::Abs(m.m[1][1])) > maxe)
        {
            maxc = 1;
            maxe = maxf;
        }
        if ((maxf = Mathf::Abs(m.m[2][2])) > maxe)
        {
            maxc = 2;
            maxe = maxf;
        }
        e.x = v.m[maxc][0];
        e.y = v.m[maxc][1];
        e.z = v.m[maxc][2];

        // Find the most extreme points along direction e
        int imin{}, imax{};
        ExtremePointsAlongDirection(e, points, numPoints, &imin, &imax);
        Vec3 minpt = points[imin];
        Vec3 maxpt = points[imax];

        float dist = (maxpt - minpt).magnitude();
        float newRadius = dist * 0.5f;
        Vec3 newCenter = (minpt + maxpt) * 0.5f;
        eigSphere.setCenter(newCenter);
        eigSphere.setRadius(newRadius);
    }

    void Sphere::RitterEigenSphere(Sphere &s, const Vec3 *points, int numPoints)
    {
        // Start with sphere from maximum spread
        EigenSphere(s, points, numPoints);
        
        // Grow sphere to include all points
        for (int i = 0; i < numPoints; i++)
            SphereOfSphereAndPt(s, points[i]);
    }

} // namespace TDS