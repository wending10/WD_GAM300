#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vector3.h"
#include "Quaternion.h"


namespace TDS
{
class Quat;
class Mat3
{
public:
    // memory layout: (column-major order)
    //
    //                row no (=vertical)
    //               |  0   1   2  
    //            ---+------------
    //            0  | m00[0] m10[3] m20[6] 
    // column no  1  | m01[1] m11[4] m21[7]
    // (=horiz)   2  | m02[2] m12[5] m22[8]
    //            
    // Constructors and destructors
    Mat3();
    Mat3(const Mat3& m); // Copy constructor
    Mat3(float value); // Constructor with one value
    Mat3(float data[]); // Constructor with array of values
    Mat3(float m00, float m01, float m02,
         float m10, float m11, float m12,
         float m20, float m21, float m22); // Constructor with nine values
    Mat3(Vec3 v1, Vec3 v2, Vec3 v3); // Constructor with three vectors
    ~Mat3();

    // Properties
    static Mat3 identity();
    static Mat3 one();
    static Mat3 zero();
    float determinant();
    Mat3 inverse();
    bool isInvertible();
    Mat3 transpose();

    // Methods
    bool Equals(const Mat3& m);
    Vec3 GetColumn(int index);
    Vec3 GetRow(int index);
    void SetColumn(int index, Vec3 v);
    void SetRow(int index, Vec3 v);

    // Create a rotation matrix. (Counter-clockwise)
    static Mat3 RotateX(float angleRadians);
    static Mat3 RotateY(float angleRadians);
    static Mat3 RotateZ(float angleRadians);
    // Create a scaling matrix.
    static Mat3 Scale(float scaleX, float scaleY, float scaleZ);
    static Quat toQuat(Mat3 const& m);

    std::string ToString();

    // Operators
    Mat3& operator=(const Mat3& var);
    Mat3& operator+=(float value);
    Mat3& operator+=(const Mat3& var);
    Mat3& operator-=(float value);
    Mat3& operator-=(const Mat3& var);
    Mat3& operator*=(float value);
    Mat3& operator*=(const Mat3& var);
    Mat3& operator/=(float value);

    float& operator[](int index); // Indexing operator
    float const& operator[](int index) const; // Indexing operator
    // Variables
    float m[3][3];
};
// unary operators
Mat3 operator-(const Mat3& var);

// binary operators
Mat3 operator+(Mat3 const& var, float const& value);
Mat3 operator+(float const& value, Mat3 const& var);
Mat3 operator+(Mat3 const& var1, Mat3 const& var2);
Mat3 operator-(Mat3 const& var, float const& value);
Mat3 operator-(float const& value, Mat3 const& var);
Mat3 operator-(Mat3 const& var1, Mat3 const& var2);
Mat3 operator*(Mat3 const& var, float const& value);
Mat3 operator*(float const& value, Mat3 const& var);
Mat3 operator*(Mat3 const& var1, Mat3 const& var2);
Mat3 operator/(Mat3 const& var, float const& value);
Mat3 operator/(float const& value, Mat3 const& var);

// boolean operators
bool operator==(Mat3 const& var1, Mat3 const& var2);
bool operator!=(Mat3 const& var1, Mat3 const& var2);

std::ostream& operator<<(std::ostream& os, const Mat3& m);
} // namespace WD


#endif // MATRIX3_H
