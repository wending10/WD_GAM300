#include "Line.h"


namespace TDS
{
    Line::Line() : start(0.0), end(0.0) {}
    Line::~Line() {}
    Line::Line(const Vec3& newStart, const Vec3& newEnd) : start(newStart), end(newEnd) {}
    Line::Line(const Line& line) : start(line.start), end(line.end) {}

    bool Line::contains(const Vec3& point, float* t) const
    {
        Vec3 dir = end - start;
        float len = dir.magnitude();
        dir = dir.normalize();

        Vec3 diff = point - start;
        float dot = Vec3::Dot(diff, dir);

        if (t != NULL)
            *t = dot;

        return (dot >= 0.0f && dot <= len);
    }


} // namespace TDS