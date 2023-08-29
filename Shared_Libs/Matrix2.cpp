#include "Matrix2.h"

namespace TDS
{
    Mat2::Mat2()
    {
        m[0][0] = 1; m[1][0] = 0;
        m[0][1] = 0; m[1][1] = 1;
    }

    Mat2::Mat2(const Mat2& matrix)
    {
        m[0][0] = matrix.m[0][0]; m[1][0] = matrix.m[1][0];
        m[0][1] = matrix.m[0][1]; m[1][1] = matrix.m[1][1];
    }

    Mat2::Mat2(float value)
    {
        m[0][0] = value; m[1][0] = value;
        m[0][1] = value; m[1][1] = value;
    }

    Mat2::Mat2(float data[])
    {
        m[0][0] = data[0]; m[1][0] = data[2];
        m[0][1] = data[1]; m[1][1] = data[3];
    }

    Mat2::Mat2(float m00, float m01, float m10, float m11)
    {
        m[0][0] = m00; m[1][0] = m10;
        m[0][1] = m01; m[1][1] = m11;
    }


    Mat2::Mat2(Vec2 v0, Vec2 v1)
    {
        m[0][0] = v0.x; m[1][0] = v1.x;
        m[0][1] = v0.y; m[1][1] = v1.y;
    }

    Mat2::~Mat2() {}

    Mat2 Mat2::identity() 
    {
        return Mat2(1, 0, 0, 1);
    }

    Mat2 Mat2::zero()
    {
        return Mat2(0, 0, 0, 0);
    }

    float Mat2::determinant()
    {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    bool Mat2::Equals(const Mat2& matrix)
    {
        return m[0][0] == matrix.m[0][0] && m[1][0] == matrix.m[1][0] &&
               m[0][1] == matrix.m[0][1] && m[1][1] == matrix.m[1][1];
    }

    Vec2 Mat2::GetColumn(int index)
    {
        switch (index)
        {
            case 0: return Vec2(m[0][0], m[0][1]);
            case 1: return Vec2(m[1][0], m[1][1]);
            default: throw std::out_of_range("Index out of range.");
        }
    }

    Vec2 Mat2::GetRow(int index)
    {
        switch (index)
        {
            case 0: return Vec2(m[0][0], m[1][0]);
            case 1: return Vec2(m[0][1], m[1][1]);
            default: throw std::out_of_range("Index out of range.");
        }
    }

    void Mat2::SetColumn(int index, Vec2 v)
    {
        switch (index)
        {
            case 0: m[0][0] = v.x; m[0][1] = v.y; break;
            case 1: m[1][0] = v.x; m[1][1] = v.y; break;
        }
    }

    void Mat2::SetRow(int index, Vec2 v)
    {
        switch (index)
        {
            case 0: m[0][0] = v.x; m[1][0] = v.y; break;
            case 1: m[0][1] = v.x; m[1][1] = v.y; break;
        }
    }

    Mat2 Mat2::transpose()
    {
        return Mat2(m[0][0], m[1][0], m[0][1], m[1][1]);
    }

    Mat2 Mat2::inverse()
    {
        float det = determinant();
        if (det == 0) return Mat2::zero();
        return Mat2(m[1][1] / det, -m[0][1] / det, -m[1][0] / det, m[0][0] / det);
    }

    Mat2 Mat2::Rotate(float angleRadians)
    {
        float c = Mathf::Cos(angleRadians);
        float s = Mathf::Sin(angleRadians);
        return Mat2(c, s, -s, c);
    }

    Mat2 Mat2::Scale(float scaleX, float scaleY)
    {
        return Mat2(scaleX, 0, 0, scaleY);
    }

    std::string Mat2::ToString()
    {
        std::stringstream ss;
        ss << "Mat2(" << m[0][0] << ", " << m[0][1] << ", " << m[1][0] << ", " << m[1][1] << ")";
        return ss.str();
    }

    Mat2 Mat2::operator+(const Mat2& matrix) const
    {
        return Mat2(m[0][0] + matrix.m[0][0], m[0][1] + matrix.m[0][1], m[1][0] + matrix.m[1][0], m[1][1] + matrix.m[1][1]);
    }

    Mat2 Mat2::operator-(const Mat2& matrix) const
    {
        return Mat2(m[0][0] - matrix.m[0][0], m[0][1] - matrix.m[0][1], m[1][0] - matrix.m[1][0], m[1][1] - matrix.m[1][1]);
    }

    Mat2 Mat2::operator*(const Mat2& matrix) const
    {
        // column-major order
        float temp00 = m[0][0] * matrix.m[0][0] + m[1][0] * matrix.m[0][1];
        float temp01 = m[0][1] * matrix.m[0][0] + m[1][1] * matrix.m[0][1];
        float temp10 = m[0][0] * matrix.m[1][0] + m[1][0] * matrix.m[1][1];
        float temp11 = m[0][1] * matrix.m[1][0] + m[1][1] * matrix.m[1][1];
        return Mat2(temp00, temp01, temp10, temp11);
    }

    Mat2 Mat2::operator*(float value) const
    {
        return Mat2(m[0][0] * value, m[0][1] * value, m[1][0] * value, m[1][1] * value);
    }

    Mat2 Mat2::operator/(float value) const
    {
        return Mat2(m[0][0] / value, m[0][1] / value, m[1][0] / value, m[1][1] / value);
    }

    Mat2& Mat2::operator=(const Mat2& matrix)
    {
        m[0][0] = matrix.m[0][0]; m[1][0] = matrix.m[1][0];
        m[0][1] = matrix.m[0][1]; m[1][1] = matrix.m[1][1];
        return *this;
    }

    Mat2& Mat2::operator+=(const Mat2& matrix)
    {
        m[0][0] += matrix.m[0][0]; m[1][0] += matrix.m[1][0];
        m[0][1] += matrix.m[0][1]; m[1][1] += matrix.m[1][1];
        return *this;
    }

    Mat2& Mat2::operator-=(const Mat2& matrix)
    {
        m[0][0] -= matrix.m[0][0]; m[1][0] -= matrix.m[1][0];
        m[0][1] -= matrix.m[0][1]; m[1][1] -= matrix.m[1][1];
        return *this;
    }

    Mat2& Mat2::operator*=(const Mat2& matrix)
    {
        float temp00 = m[0][0] * matrix.m[0][0] + m[1][0] * matrix.m[0][1];
        float temp01 = m[0][1] * matrix.m[0][0] + m[1][1] * matrix.m[0][1];
        float temp10 = m[0][0] * matrix.m[1][0] + m[1][0] * matrix.m[1][1];
        float temp11 = m[0][1] * matrix.m[1][0] + m[1][1] * matrix.m[1][1];
        m[0][0] = temp00; m[1][0] = temp10;
        m[0][1] = temp01; m[1][1] = temp11;
        return *this;
    }

    Mat2& Mat2::operator*=(float value)
    {
        m[0][0] *= value; m[0][1] *= value;
        m[1][0] *= value; m[1][1] *= value;
        return *this;
    }

    Mat2& Mat2::operator/=(float value) {
        m[0][0] /= value; m[0][1] /= value;
        m[1][0] /= value; m[1][1] /= value;
        return *this;
    }

    Mat2 Mat2::operator-() const
    {
        return Mat2(-m[0][0], -m[0][1], -m[1][0], -m[1][1]);
    }

    Vec2 Mat2::operator*(const Vec2& v) const
    {
        return Vec2(m[0][0] * v.x + m[1][0] * v.y, m[0][1] * v.x + m[1][1] * v.y);
    }

    bool Mat2::operator==(const Mat2& matrix) const
    {
        return m[0][0] == matrix.m[0][0] && m[0][1] == matrix.m[0][1] && m[1][0] == matrix.m[1][0] && m[1][1] == matrix.m[1][1];
    }

    bool Mat2::operator!=(const Mat2& matrix) const
    {
        return m[0][0] != matrix.m[0][0] || m[0][1] != matrix.m[0][1] || m[1][0] != matrix.m[1][0] || m[1][1] != matrix.m[1][1];
    }

    float WD::Mat2::operator[](int index) const 
    {
        switch (index)
        {
        case 0: return m[0][0];
        case 1: return m[0][1];
        case 2: return m[1][0];
        case 3: return m[1][1];
        default:
            throw std::out_of_range("Mat2 index out of range");
        }
    }

    float& Mat2::operator[](int index) 
    {
        switch (index)
        {
        case 0: return m[0][0];
        case 1: return m[0][1];
        case 2: return m[1][0];
        case 3: return m[1][1];
        default:
            throw std::out_of_range("Mat2 index out of range");
        }
    }


    std::ostream& operator<<(std::ostream& os, const Mat2& matrix) {
        // ensure "|"" is perfectly aligned with the matrix regardless of the value
        // of the matrix
        std::stringstream m00, m01, m10, m11;
        m00 << matrix.m[0][0]; m10 << matrix.m[1][0];
        m01 << matrix.m[0][1]; m11 << matrix.m[1][1];
        float maxLength[] = {(float)m00.str().size(), (float)m01.str().size(), (float)m10.str().size(), (float)m11.str().size()};

        int maxLen = Mathf::Max(maxLength, 4);
        os  << std::left 
            << "| "  << std::setw(maxLen) << matrix.m[0][0]  << " " << std::setw(maxLen) << matrix.m[1][0] << " |\n"
            << "| "  << std::setw(maxLen) << matrix.m[0][1]  << " " << std::setw(maxLen) << matrix.m[1][1] << " |";

        return os;
    }

} // namespace WD