#ifndef MATRIX2_H
#define MATRIX2_H

#include "Vector2.h"

namespace TDS
{
class Mat2
{     
    // Variables (column-major order)
    // memory layout:
    //
    //                row no (=vertical)
    //               |  0   1 
    //  column no ---+--------
    //  (=horiz)  0  | m00 m10
    //            1  | m01 m11

    public:
    // Constructors and destructors
    Mat2();
    Mat2(const Mat2& m); // Copy constructor
    Mat2(float value); // Constructor with one value
    Mat2(float data[]); // Constructor with array of values
    Mat2(float m00, float m01, float m10, float m11); // Constructor with four values
    Mat2(Vec2 v1, Vec2 v2); // Constructor with two vectors
    ~Mat2();

    // Properties
    static Mat2 identity();
    static Mat2 zero();
    float determinant();
    Mat2 inverse();
    Mat2 transpose();

    // Methods
    bool Equals(const Mat2& m);
    Vec2 GetColumn(int index);
    Vec2 GetRow(int index);

    void SetColumn(int index, Vec2 v);
    void SetRow(int index, Vec2 v);

    // Create a rotation matrix. (Counter-clockwise)
    static Mat2 Rotate(float angleRadians);
    // Create a scaling matrix.
    static Mat2 Scale(float scaleX, float scaleY);
    // Return string representation of the matrix.
    std::string ToString();

    // unary arithmetic operators
    Mat2& operator=(const Mat2& var);
    Mat2& operator+=(float value);
    Mat2& operator+=(const Mat2& var);
    Mat2& operator-=(float value);
    Mat2& operator-=(const Mat2& var);
    Mat2& operator*=(float value);
    Mat2& operator*=(const Mat2& var);
    Mat2& operator/=(float value);

    float& operator[](int index);
    float const& operator[](int index) const;
    // Access using 2D indices
    //  (0,0) (0,1)
    //  (1,0) (1,1)

    float m[2][2];
};
// unary operators
Mat2 operator-(const Mat2& var);

// binary operators
Mat2 operator+(Mat2 const& var, float const& value);
Mat2 operator+(float const& value, Mat2 const& var);
Mat2 operator+(Mat2 const& var1, Mat2 const& var2);
Mat2 operator-(Mat2 const& var, float const& value);
Mat2 operator-(float const& value, Mat2 const& var);
Mat2 operator-(Mat2 const& var1, Mat2 const& var2);
Mat2 operator*(Mat2 const& var, float const& value);
Mat2 operator*(float const& value, Mat2 const& var);
Mat2 operator*(Mat2 const& var1, Mat2 const& var2);
Mat2 operator/(Mat2 const& var, float const& value);
Mat2 operator/(float const& value, Mat2 const& var);

// boolean operators
bool operator==(Mat2 const& var1, Mat2 const& var2);
bool operator!=(Mat2 const& var1, Mat2 const& var2);

std::ostream& operator<<(std::ostream& os, const Mat2& m);


} // namespace WD


#endif // MATRIX2_H
