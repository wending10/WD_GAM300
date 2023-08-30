#include "MathCommon.h"
namespace TDS
{
    float Mathf::Clamp(float value, float min, float max)
    {
        if (value < min)
            return min;
        else if (value > max)
            return max;
        else
            return value;
    }

    float Mathf::Clamp(int value, int min, int max)
    {
        if (value < min)
            return static_cast<float>(min);
        else if (value > max)
            return static_cast<float>(max);
        else
            return static_cast<float>(value);
    }

    float Mathf::Clamp01(float value)
    {
        if (value < 0.f)
            return 0.f;
        else if (value > 1.f)
            return 1.f;
        else
            return value;
    }

    float Mathf::Lerp(float a, float b, float t)
    {
        return a + (b - a) * Clamp01(t);
    }

    float Mathf::LerpUnclamped(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    float Mathf::LerpAngle(float a, float b, float t) {
        float delta = Mathf::Repeat((b - a), 360.f);
        if (delta > 180.f)
            delta -= 360.f;
        return a + delta * Clamp01(t);
    }

    float Mathf::MoveTowards(float current, float target, float maxDelta)
    {
        if (Abs(target - current) <= maxDelta)
            return target;
        return current + Sign(target - current) * maxDelta;
    }

    float Mathf::MoveTowardsAngle(float current, float target, float maxDelta)
    {
        float deltaAngle = DeltaAngle(current, target);
        if (-maxDelta < deltaAngle && deltaAngle < maxDelta)
            return target;
        target = current + deltaAngle;
        return MoveTowards(current, target, maxDelta);
    }

    float Mathf::SmoothStep(float from, float to, float t)
    {
        t = Clamp01(t);
        t = -2.f * t * t * t + 3.f * t * t;
        return to * t + from * (1.f - t);
    }

    float Mathf::Gamma(float value, float absmax, float gamma)
    {
        bool negative = value < 0.f;
        float absval = Abs(value);
        if (absval > absmax)
            return negative ? -absval : absval;

        float result = Pow(absval / absmax, gamma) * absmax;
        return negative ? -result : result;
    }

    bool Mathf::Approximately(float a, float b)
    {
        //return Abs(b - a) < Max(0.000001f * Max(Abs(a), Abs(b)), Mathf::Epsilon * 100);
        return Abs(a - b ) < Mathf::Epsilon * (1 + (std::max)( Abs(a), Abs(b) ) );
    }

    float Mathf::Repeat(float t, float length)
    {
        return Clamp(t - Floor(t / length) * length, 0.f, length);
    }

    float Mathf::PingPong(float t, float length)
    {
        t = Repeat(t, length * 2.f);
        return length - Abs(t - length);
    }

    float Mathf::InverseLerp(float a, float b, float value)
    {
        if (a != b)
            return Clamp01((value - a) / (b - a));
        else
            return 0.f;
    }

    float Mathf::DeltaAngle(float current, float target)
    {
        float delta = Repeat((target - current), 360.f);
        if (delta > 180.f)
            delta -= 360.f;
        return delta;
    }

    bool Mathf::LineIntersection(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, Vec2& result)
    {
        float bx = p2.x - p1.x;
        float by = p2.y - p1.y;
        float dx = p4.x - p3.x;
        float dy = p4.y - p3.y;
        float bDotDPerp = bx * dy - by * dx;
        if (bDotDPerp == 0)
            return false;

        float cx = p3.x - p1.x;
        float cy = p3.y - p1.y;
        float t = (cx * dy - cy * dx) / bDotDPerp;

        result.Set(p1.x + t * bx, p1.y + t * by);
        return true;
    }
    
    bool Mathf::LineSegmentIntersection(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, Vec2& result)
    {
        float bx = p2.x - p1.x;
        float by = p2.y - p1.y;
        float dx = p4.x - p3.x;
        float dy = p4.y - p3.y;
        float bDotDPerp = bx * dy - by * dx;
        if (bDotDPerp == 0)
            return false;

        float cx = p3.x - p1.x;
        float cy = p3.y - p1.y;
        float t = (cx * dy - cy * dx) / bDotDPerp;
        if (t < 0 || t > 1)
            return false;

        float u = (cx * by - cy * bx) / bDotDPerp;
        if (u < 0 || u > 1)
            return false;

        result.Set(p1.x + t * bx, p1.y + t * by);
        return true;
    }
} // namespace WD