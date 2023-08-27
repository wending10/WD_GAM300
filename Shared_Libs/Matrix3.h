#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vector3.h"
#include <iomanip>


namespace TDS
{
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
    // Quaternion ToQuaternion(const Mat3& m);
    //static Mat3 FromQuaternion(const Quaternion& q);
    // Return string representation of the matrix.
    std::string ToString();

    // Operators
    Mat3 operator+(const Mat3& var) const;
    Mat3 operator-(const Mat3& var) const;
    Mat3 operator*(const Mat3& var) const;
    Mat3 operator*(float value) const; // Scalar multiplication
    Mat3 operator/(float value) const; // Scalar division
    Mat3& operator=(const Mat3& var);
    Mat3& operator+=(const Mat3& var);
    Mat3& operator-=(const Mat3& var);
    Mat3& operator*=(const Mat3& var);
    Mat3& operator*=(float value);
    Mat3& operator/=(float value);
    Mat3 operator-() const; // Unary minus
    Vec3 operator*(const Vec3& v) const; // Matrix-vector multiplication

    bool operator==(const Mat3& var) const;
    bool operator!=(const Mat3& var) const;
    float operator[](int index) const; // Indexing operator
    float& operator[](int index); // Indexing operator

    // Variables
    float m[3][3];
};
std::ostream& operator<<(std::ostream& os, const Mat3& m);





} // namespace WD


#endif // MATRIX3_H
