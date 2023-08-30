#include "Matrix3.h"

namespace TDS
{
    Mat3::Mat3() 
    {
        m[0][0] = 1; m[1][0] = 0; m[2][0] = 0;
        m[0][1] = 0; m[1][1] = 1; m[2][1] = 0;
        m[0][2] = 0; m[1][2] = 0; m[2][2] = 1;
    }

    Mat3::Mat3(const Mat3& var)
    {
        m[0][0] = var.m[0][0]; m[1][0] = var.m[1][0]; m[2][0] = var.m[2][0];
        m[0][1] = var.m[0][1]; m[1][1] = var.m[1][1]; m[2][1] = var.m[2][1];
        m[0][2] = var.m[0][2]; m[1][2] = var.m[1][2]; m[2][2] = var.m[2][2];
    }

    Mat3::Mat3(float value)
    {
        m[0][0] = value; m[1][0] = value; m[2][0] = value;
        m[0][1] = value; m[1][1] = value; m[2][1] = value;
        m[0][2] = value; m[1][2] = value; m[2][2] = value;
    }

    Mat3::Mat3(float data[])
    {
        m[0][0] = data[0]; m[1][0] = data[3]; m[2][0] = data[6];
        m[0][1] = data[1]; m[1][1] = data[4]; m[2][1] = data[7];
        m[0][2] = data[2]; m[1][2] = data[5]; m[2][2] = data[8];
    }

    Mat3::Mat3(float m00, float m01, float m02,
               float m10, float m11, float m12,
               float m20, float m21, float m22)
    {
        m[0][0] = m00; m[1][0] = m10; m[2][0] = m20;
        m[0][1] = m01; m[1][1] = m11; m[2][1] = m21;
        m[0][2] = m02; m[1][2] = m12; m[2][2] = m22;
    }

    Mat3::Mat3(Vec3 v0, Vec3 v1, Vec3 v2)
    {
        m[0][0] = v0.x; m[1][0] = v1.x; m[2][0] = v2.x;
        m[0][1] = v0.y; m[1][1] = v1.y; m[2][1] = v2.y;
        m[0][2] = v0.z; m[1][2] = v1.z; m[2][2] = v2.z;
    }

    Mat3::~Mat3() {}

    Mat3 Mat3::identity()
    {
        return Mat3(1, 0, 0,
                    0, 1, 0,
                    0, 0, 1);
    }

    Mat3 Mat3::one()
    {
        return Mat3(1, 1, 1,
                    1, 1, 1,
                    1, 1, 1);
    }

    Mat3 Mat3::zero()
    {
        return Mat3(0, 0, 0,
                    0, 0, 0,
                    0, 0, 0);
    }

    float Mat3::determinant()
    {
        return m[0][0] * m[1][1] * m[2][2] +
               m[0][1] * m[1][2] * m[2][0] +
               m[0][2] * m[1][0] * m[2][1] -
               m[0][2] * m[1][1] * m[2][0] -
               m[0][1] * m[1][0] * m[2][2] -
               m[0][0] * m[1][2] * m[2][1];
    }

    bool Mat3::Equals(const Mat3& var)
    {
        return m[0][0] == var.m[0][0] && m[1][0] == var.m[1][0] && m[2][0] == var.m[2][0] &&
               m[0][1] == var.m[0][1] && m[1][1] == var.m[1][1] && m[2][1] == var.m[2][1] &&
               m[0][2] == var.m[0][2] && m[1][2] == var.m[1][2] && m[2][2] == var.m[2][2];
    }

    Vec3 Mat3::GetColumn(int index)
    {
        switch (index)
        {
        case 0: return Vec3(m[0][0], m[0][1], m[0][2]);
        case 1: return Vec3(m[1][0], m[1][1], m[1][2]);
        case 2: return Vec3(m[2][0], m[2][1], m[2][2]);
        default:
            throw std::out_of_range("Mat3 column index out of range");
        }
    }

    Vec3 Mat3::GetRow(int index)
    {
        switch (index)
        {
        case 0: return Vec3(m[0][0], m[1][0], m[2][0]);
        case 1: return Vec3(m[0][1], m[1][1], m[2][1]);
        case 2: return Vec3(m[0][2], m[1][2], m[2][2]);
        default:
            throw std::out_of_range("Mat3 row index out of range");
        }
    }

    void Mat3::SetColumn(int index, Vec3 v)
    {
        switch (index)
        {
        case 0: m[0][0] = v.x; m[0][1] = v.y; m[0][2] = v.z; break;
        case 1: m[1][0] = v.x; m[1][1] = v.y; m[1][2] = v.z; break;
        case 2: m[2][0] = v.x; m[2][1] = v.y; m[2][2] = v.z; break;
        default:
            throw std::out_of_range("Mat3 column index out of range");
        }
    }

    void Mat3::SetRow(int index, Vec3 v)
    {
        switch (index)
        {
        case 0: m[0][0] = v.x; m[1][0] = v.y; m[2][0] = v.z; break;
        case 1: m[0][1] = v.x; m[1][1] = v.y; m[2][1] = v.z; break;
        case 2: m[0][2] = v.x; m[1][2] = v.y; m[2][2] = v.z; break;
        default:
            throw std::out_of_range("Mat3 row index out of range");
        }
    }

    Mat3 Mat3::inverse() 
    {
        if (!isInvertible())
            throw std::invalid_argument("Matrix is not invertible.");
        float det = determinant();
        float m00 = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) / det;
        float m01 = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) / det;
        float m02 = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;
        float m10 = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) / det;
        float m11 = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
        float m12 = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) / det;
        float m20 = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) / det;
        float m21 = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) / det;
        float m22 = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det;
        return Mat3(m00, m01, m02, m10, m11, m12, m20, m21, m22);
    }

    bool Mat3::isInvertible()
    {
        return determinant() != 0;
    }

    Mat3 Mat3::transpose()
    {
        return Mat3(m[0][0], m[1][0], m[2][0],
                    m[0][1], m[1][1], m[2][1],
                    m[0][2], m[1][2], m[2][2]);
    }

    Mat3 Mat3::RotateX(float angleRadians)
    {
        float c = cos(angleRadians);
        float s = sin(angleRadians);
        Vec3 v0 = Vec3(1, 0, 0);
        Vec3 v1 = Vec3(0, c, s);
        Vec3 v2 = Vec3(0, -s, c);
        return Mat3(v0, v1, v2);
    }

    Mat3 Mat3::RotateY(float angleRadians)
    {
        float c = cos(angleRadians);
        float s = sin(angleRadians);
        Vec3 v0 = Vec3(c, 0, -s);
        Vec3 v1 = Vec3(0, 1, 0);
        Vec3 v2 = Vec3(s, 0, c);
        return Mat3(v0, v1, v2);
    }

    Mat3 Mat3::Scale(float scaleX, float scaleY, float scaleZ)
    {
        Vec3 v0 = Vec3(scaleX, 0, 0);
        Vec3 v1 = Vec3(0, scaleY, 0);
        Vec3 v2 = Vec3(0, 0, scaleZ);
        return Mat3(v0, v1, v2);
    }

	Quat Mat3::toQuat(Mat3 const& m)
	{
		float fourXSquareMinus1 = m.m[0][0] - m.m[1][1] - m.m[2][2];
		float fourYSquareMinus1 = m.m[1][1] - m.m[0][0] - m.m[2][2];
		float fourZSquareMinus1 = m.m[2][2] - m.m[0][0] - m.m[1][1];
		float fourWSquareMinus1 = m.m[0][0] + m.m[1][1] + m.m[2][2];

		int biggestIndex = 0;
		float fourBiggestSquareMinus1 = fourWSquareMinus1;
		if (fourXSquareMinus1 > fourBiggestSquareMinus1)
		{
			fourBiggestSquareMinus1 = fourXSquareMinus1;
			biggestIndex = 1;
		}
		if (fourYSquareMinus1 > fourBiggestSquareMinus1)
		{
			fourBiggestSquareMinus1 = fourYSquareMinus1;
			biggestIndex = 2;
		}
		if (fourZSquareMinus1 > fourBiggestSquareMinus1)
		{
			fourBiggestSquareMinus1 = fourZSquareMinus1;
			biggestIndex = 3;
		}

		float biggestVal = Mathf::Sqrt(fourBiggestSquareMinus1 + 1.f) * 0.5f;
		float mult = 0.25f / biggestVal;

		switch (biggestIndex)
		{
		case 0:
			return Quat(biggestVal, (m.m[1][2] - m.m[2][1]) * mult, (m.m[2][0] - m.m[0][2]) * mult, (m.m[0][1] - m.m[1][0]) * mult);
		case 1:
			return Quat((m.m[1][2] - m.m[2][1]) * mult, biggestVal, (m.m[0][1] + m.m[1][0]) * mult, (m.m[2][0] + m.m[0][2]) * mult);
		case 2:
			return Quat((m.m[2][0] - m.m[0][2]) * mult, (m.m[0][1] + m.m[1][0]) * mult, biggestVal, (m.m[1][2] + m.m[2][1]) * mult);
		case 3:
			return Quat((m.m[0][1] - m.m[1][0]) * mult, (m.m[2][0] + m.m[0][2]) * mult, (m.m[1][2] + m.m[2][1]) * mult, biggestVal);
		default:
			return Quat();
        }
	}

    std::string Mat3::ToString()
    {
        std::ostringstream ss;
        ss << m[0][0] << " " << m[1][0] << " " << m[2][0] << "\n"
           << m[0][1] << " " << m[1][1] << " " << m[2][1] << "\n"
           << m[0][2] << " " << m[1][2] << " " << m[2][2] << "\n";
        return ss.str();
    }

    Mat3 Mat3::RotateZ(float angleRadians)
    {
        float c = cos(angleRadians);
        float s = sin(angleRadians);
        Vec3 v0 = Vec3(c, s, 0);
        Vec3 v1 = Vec3(-s, c, 0);
        Vec3 v2 = Vec3(0, 0, 1);
        return Mat3(v0, v1, v2);
    }

    Mat3& Mat3::operator=(const Mat3& var)
    {
        m[0][0] = var.m[0][0]; m[1][0] = var.m[1][0]; m[2][0] = var.m[2][0];
        m[0][1] = var.m[0][1]; m[1][1] = var.m[1][1]; m[2][1] = var.m[2][1];
        m[0][2] = var.m[0][2]; m[1][2] = var.m[1][2]; m[2][2] = var.m[2][2];
        return *this;
    }

    Mat3& Mat3::operator+=(float value) 
    {
        m[0][0] += value; m[1][0] += value; m[2][0] += value;
        m[0][1] += value; m[1][1] += value; m[2][1] += value;
        m[0][2] += value; m[1][2] += value; m[2][2] += value;
        return *this;
    }

    Mat3& Mat3::operator+=(const Mat3& var)
    {
        m[0][0] += var.m[0][0]; m[1][0] += var.m[1][0]; m[2][0] += var.m[2][0];
        m[0][1] += var.m[0][1]; m[1][1] += var.m[1][1]; m[2][1] += var.m[2][1];
        m[0][2] += var.m[0][2]; m[1][2] += var.m[1][2]; m[2][2] += var.m[2][2];
        return *this;
    }

    Mat3& Mat3::operator-=(float value) 
    {
        m[0][0] -= value; m[1][0] -= value; m[2][0] -= value;
        m[0][1] -= value; m[1][1] -= value; m[2][1] -= value;
        m[0][2] -= value; m[1][2] -= value; m[2][2] -= value;
        return *this;
    }

    Mat3& Mat3::operator-=(const Mat3& var)
    {
        m[0][0] -= var.m[0][0]; m[1][0] -= var.m[1][0]; m[2][0] -= var.m[2][0];
        m[0][1] -= var.m[0][1]; m[1][1] -= var.m[1][1]; m[2][1] -= var.m[2][1];
        m[0][2] -= var.m[0][2]; m[1][2] -= var.m[1][2]; m[2][2] -= var.m[2][2];
        return *this;
    }

    Mat3& Mat3::operator*=(const Mat3& var)
    {
        float m00, m01, m02, m10, m11, m12, m20, m21, m22;
        m00 = m[0][0] * var.m[0][0] + m[1][0] * var.m[0][1] + m[2][0] * var.m[0][2];
        m01 = m[0][1] * var.m[0][0] + m[1][1] * var.m[0][1] + m[2][1] * var.m[0][2];
        m02 = m[0][2] * var.m[0][0] + m[1][2] * var.m[0][1] + m[2][2] * var.m[0][2];
        m10 = m[0][0] * var.m[1][0] + m[1][0] * var.m[1][1] + m[2][0] * var.m[1][2];
        m11 = m[0][1] * var.m[1][0] + m[1][1] * var.m[1][1] + m[2][1] * var.m[1][2];
        m12 = m[0][2] * var.m[1][0] + m[1][2] * var.m[1][1] + m[2][2] * var.m[1][2];
        m20 = m[0][0] * var.m[2][0] + m[1][0] * var.m[2][1] + m[2][0] * var.m[2][2];
        m21 = m[0][1] * var.m[2][0] + m[1][1] * var.m[2][1] + m[2][1] * var.m[2][2];
        m22 = m[0][2] * var.m[2][0] + m[1][2] * var.m[2][1] + m[2][2] * var.m[2][2];
        
        m[0][0] = m00; m[1][0] = m10; m[2][0] = m20;
        m[0][1] = m01; m[1][1] = m11; m[2][1] = m21;
        m[0][2] = m02; m[1][2] = m12; m[2][2] = m22;
        return *this;
    }

    Mat3& Mat3::operator*=(float value)
    {
        m[0][0] *= value; m[1][0] *= value; m[2][0] *= value;
        m[0][1] *= value; m[1][1] *= value; m[2][1] *= value;
        m[0][2] *= value; m[1][2] *= value; m[2][2] *= value;
        return *this;
    }

    Mat3& Mat3::operator/=(float value)
    {
        if (value == 0)
            throw std::invalid_argument("Division by zero.");
        m[0][0] /= value; m[1][0] /= value; m[2][0] /= value;
        m[0][1] /= value; m[1][1] /= value; m[2][1] /= value;
        m[0][2] /= value; m[1][2] /= value; m[2][2] /= value;
        return *this;
    }

    float& Mat3::operator[](int index)
    {
        switch (index)
        {
        case 0: return m[0][0];
        case 1: return m[0][1];
        case 2: return m[0][2];
        case 3: return m[1][0];
        case 4: return m[1][1];
        case 5: return m[1][2];
        case 6: return m[2][0];
        case 7: return m[2][1];
        case 8: return m[2][2];
        default:
            throw std::out_of_range("Mat3 index out of range");
        }
    }

    float const& Mat3::operator[](int index) const 
    {
        switch (index)
        {
        case 0: return m[0][0];
        case 1: return m[0][1];
        case 2: return m[0][2];
        case 3: return m[1][0];
        case 4: return m[1][1];
        case 5: return m[1][2];
        case 6: return m[2][0];
        case 7: return m[2][1];
        case 8: return m[2][2];
        default:
            throw std::out_of_range("Mat3 index out of range");
        }
    }

    Mat3 operator-(const Mat3& var)
    {
        return Mat3(-var.m[0][0], -var.m[0][1], -var.m[0][2],
                    -var.m[1][0], -var.m[1][1], -var.m[1][2],
                    -var.m[2][0], -var.m[2][1], -var.m[2][2]);
    }

    Mat3 operator+(Mat3 const& var, float const& value)
    {
        return Mat3(
            var.m[0][0] + value, var.m[0][1] + value, var.m[0][2] + value,
            var.m[1][0] + value, var.m[1][1] + value, var.m[1][2] + value,
            var.m[2][0] + value, var.m[2][1] + value, var.m[2][2] + value
        );
    }

    Mat3 operator+(float const& value, Mat3 const& var)
    {
        return Mat3(
            var.m[0][0] + value, var.m[0][1] + value, var.m[0][2] + value, 
            var.m[1][0] + value, var.m[1][1] + value, var.m[1][2] + value,
            var.m[2][0] + value, var.m[2][1] + value, var.m[2][2] + value
        );
    }

    Mat3 operator+(Mat3 const& var1, Mat3 const& var2)
    {
        return Mat3(
            var1.m[0][0] + var2.m[0][0], var1.m[0][1] + var2.m[0][1], var1.m[0][2] + var2.m[0][2], 
            var1.m[1][0] + var2.m[1][0], var1.m[1][1] + var2.m[1][1], var1.m[1][2] + var2.m[1][2], 
            var1.m[2][0] + var2.m[2][0], var1.m[2][1] + var2.m[2][1], var1.m[2][2] + var2.m[2][2]
        );
    }

    Mat3 operator-(Mat3 const& var, float const& value)
    {
        return Mat3(
            var.m[0][0] - value, var.m[0][1] - value, var.m[0][2] - value, 
            var.m[1][0] - value, var.m[1][1] - value, var.m[1][2] - value, 
            var.m[2][0] - value, var.m[2][1] - value, var.m[2][2] - value
        );
    }

    Mat3 operator-(float const& value, Mat3 const& var)
    {
        return Mat3(
            value - var.m[0][0], value - var.m[0][1], value - var.m[0][2], 
            value - var.m[1][0], value - var.m[1][1], value - var.m[1][2], 
            value - var.m[2][0], value - var.m[2][1], value - var.m[2][2]
        );
    }

    Mat3 operator-(Mat3 const& var1, Mat3 const& var2)
    {
        return Mat3(
            var1.m[0][0] - var2.m[0][0], var1.m[0][1] - var2.m[0][1], var1.m[0][2] - var2.m[0][2], 
            var1.m[1][0] - var2.m[1][0], var1.m[1][1] - var2.m[1][1], var1.m[1][2] - var2.m[1][2], 
            var1.m[2][0] - var2.m[2][0], var1.m[2][1] - var2.m[2][1], var1.m[2][2] - var2.m[2][2]
        );
    }

    Mat3 operator*(Mat3 const& var, float const& value)
    {
        return Mat3(
            var.m[0][0] * value, var.m[0][1] * value, var.m[0][2] * value, 
            var.m[1][0] * value, var.m[1][1] * value, var.m[1][2] * value, 
            var.m[2][0] * value, var.m[2][1] * value, var.m[2][2] * value
        );
    }

    Mat3 operator*(float const& value, Mat3 const& var)
    {
        return Mat3(
            value * var.m[0][0], value * var.m[0][1], value * var.m[0][2], 
            value * var.m[1][0], value * var.m[1][1], value * var.m[1][2],
            value * var.m[2][0], value * var.m[2][1], value * var.m[2][2]
        );
    }

    Mat3 operator*(Mat3 const& lhs, Mat3 const& rhs)
    {
        float m00, m01, m02,
            m10, m11, m12, 
            m20, m21, m22;
        m00 = lhs.m[0][0] * rhs.m[0][0] + lhs.m[1][0] * rhs.m[0][1] + lhs.m[2][0] * rhs.m[0][2];
        m01 = lhs.m[0][1] * rhs.m[0][0] + lhs.m[1][1] * rhs.m[0][1] + lhs.m[2][1] * rhs.m[0][2];
        m02 = lhs.m[0][2] * rhs.m[0][0] + lhs.m[1][2] * rhs.m[0][1] + lhs.m[2][2] * rhs.m[0][2];
        m10 = lhs.m[0][0] * rhs.m[1][0] + lhs.m[1][0] * rhs.m[1][1] + lhs.m[2][0] * rhs.m[1][2];
        m11 = lhs.m[0][1] * rhs.m[1][0] + lhs.m[1][1] * rhs.m[1][1] + lhs.m[2][1] * rhs.m[1][2];
        m12 = lhs.m[0][2] * rhs.m[1][0] + lhs.m[1][2] * rhs.m[1][1] + lhs.m[2][2] * rhs.m[1][2];
        m20 = lhs.m[0][0] * rhs.m[2][0] + lhs.m[1][0] * rhs.m[2][1] + lhs.m[2][0] * rhs.m[2][2];
        m21 = lhs.m[0][1] * rhs.m[2][0] + lhs.m[1][1] * rhs.m[2][1] + lhs.m[2][1] * rhs.m[2][2];
        m22 = lhs.m[0][2] * rhs.m[2][0] + lhs.m[1][2] * rhs.m[2][1] + lhs.m[2][2] * rhs.m[2][2];
        return Mat3(
            m00, m01, m02,
            m10, m11, m12,
            m20, m21, m22
        );
    }

    Mat3 operator/(Mat3 const& var, float const& value)
    {
        return Mat3(
            var.m[0][0] / value, var.m[0][1] / value, var.m[0][2] / value, 
            var.m[1][0] / value, var.m[1][1] / value, var.m[1][2] / value, 
            var.m[2][0] / value, var.m[2][1] / value, var.m[2][2] / value
        );
    }

    Mat3 operator/(float const& value, Mat3 const& var)
    {
        return Mat3(
            value / var.m[0][0], value / var.m[0][1], value / var.m[0][2], 
            value / var.m[1][0], value / var.m[1][1], value / var.m[1][2], 
            value / var.m[2][0], value / var.m[2][1], value / var.m[2][2]
        );
    }

    bool operator==(Mat3 const& var1, Mat3 const& var2)
    {
        return (
            var1.m[0][0] == var2.m[0][0] && var1.m[0][1] == var2.m[0][1] && var1.m[0][2] == var2.m[0][2] &&
            var1.m[1][0] == var2.m[1][0] && var1.m[1][1] == var2.m[1][1] && var1.m[1][2] == var2.m[1][2] &&
            var1.m[2][0] == var2.m[2][0] && var1.m[2][1] == var2.m[2][1] && var1.m[2][2] == var2.m[2][2]
        );
    }

    bool operator!=(Mat3 const& var1, Mat3 const& var2)
    {
        return !(var1 == var2);
    }


    std::ostream& operator<<(std::ostream& os, const Mat3& var)
    {
        std::stringstream m00, m01, m02, m10, m11, m12, m20, m21, m22;
        m00 << var.m[0][0]; m10 << var.m[1][0]; m20 << var.m[2][0];
        m01 << var.m[0][1]; m11 << var.m[1][1]; m21 << var.m[2][1];
        m02 << var.m[0][2]; m12 << var.m[1][2]; m22 << var.m[2][2];
        float maxLength[] = {(float)m00.str().size(), (float)m01.str().size(), (float)m02.str().size(),
                             (float)m10.str().size(), (float)m11.str().size(), (float)m12.str().size(),
                             (float)m20.str().size(), (float)m21.str().size(), (float)m22.str().size()};

        int maxLen = Mathf::Max(maxLength, 9);
        os << std::left
           << "| " << std::setw(maxLen) << var.m[0][0] << " " << std::setw(maxLen) << var.m[1][0] << " " << std::setw(maxLen) << var.m[2][0] << " |\n"
           << "| " << std::setw(maxLen) << var.m[0][1] << " " << std::setw(maxLen) << var.m[1][1] << " " << std::setw(maxLen) << var.m[2][1] << " |\n"
           << "| " << std::setw(maxLen) << var.m[0][2] << " " << std::setw(maxLen) << var.m[1][2] << " " << std::setw(maxLen) << var.m[2][2] << " |";
        return os;
    }

}  // namespace WD