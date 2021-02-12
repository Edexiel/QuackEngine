#ifndef QUACKENGINE_MATRIX4_HPP
#define QUACKENGINE_MATRIX4_HPP

#include "string.h"
namespace Maths
{
  struct Matrix4
  {
    union
    {
      Vector4 v[4];
      float e[16]{ 0 };
    };

    static Matrix4 Identity();
    static Matrix4 Scale(const float& s);
    static Matrix4 Scale(const Vector3& v);
    static Matrix4 Translate(const Vector3& v);
    static Matrix4 RotateX(const float& angle);
    static Matrix4 RotateY(const float& angle);
    static Matrix4 RotateZ(const float& angle);
    static Matrix4 Rotation(const Vector3& rotation);
    static Matrix4 AxisRotation(const float angle, const Vector3& axis);
    static Matrix4 Perspective(const int& width,
                               const int& height,
                               const float& near,
                               const float& far,
                               const float& fov);
    static Matrix4 OrthoMatrix(const int& width,
                               const int& height,
                               const float& near,
                               const float& far);

    Matrix4 GetTranspose() const;

    std::string ToString() const;
  };
}

using namespace Maths;

inline Matrix4 operator*(const Matrix4& a, const Matrix4& b)
{
    Matrix4 result;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                result.e[i + j * 4] += a.e[i + k * 4] * b.e[k + j * 4];

    return result;
}

inline Matrix4& operator*=(Matrix4& a, const Matrix4& b) { a = a * b; return a; }

inline Matrix4 operator*(const Matrix4& m, const float& f)
{
    Matrix4 result;

    for (unsigned int i = 0 ; i < 16 ; i++)
        result.e[i] = m.e[i] * f;

    return result;
}

inline Matrix4 operator+(const Matrix4& m1, const Matrix4& m2)
{
    Matrix4 result;

    for (unsigned int i = 0; i < 16 ; i++)
        result.e[i] = m1.e[i] + m2.e[i];

    return result;
}

inline Matrix4 Matrix4::Identity()
{
    Matrix4 mat;

    mat.e[0] = 1;
    mat.e[5] = 1;
    mat.e[10] = 1;
    mat.e[15] = 1;

  return mat;
}


inline Matrix4 Matrix4::Scale(const float& s)
{
    Matrix4 mat;
    mat.e[0] = s;
    mat.e[5] = s;
    mat.e[10] = s;
    mat.e[15] = 1;

    return mat;
}

inline Matrix4 Matrix4::Scale(const Vector3& v)
{
    Matrix4 mat;
    mat.e[0] = v.x;
    mat.e[5] = v.y;
    mat.e[10] = v.z;
    mat.e[15] = 1;

    return mat;
}

inline Matrix4 Matrix4::Translate(const Vector3& v)
{
    Matrix4 mat;
    mat.e[12] = v.x;
    mat.e[13] = v.y;
    mat.e[14] = v.z;

    mat.e[0] = 1;
    mat.e[5] = 1;
    mat.e[10] = 1;
    mat.e[15] = 1;

    return mat;
}

inline Matrix4 Matrix4::RotateX(const float& angle)
{
    Matrix4 rotX;
    rotX.e[0] = 1;
    rotX.e[5] = cosf(angle);
    rotX.e[9] = -sinf(angle);
    rotX.e[6] = sinf(angle);
    rotX.e[10] = cosf(angle);
    rotX.e[15] = 1;

    return rotX;
}
inline Matrix4 Matrix4::RotateY(const float& angle)
{
    Matrix4 rotY;
    rotY.e[0] = cosf(angle);
    rotY.e[8] = sinf(angle);
    rotY.e[5] = 1;
    rotY.e[2] = -sinf(angle);
    rotY.e[10] = cosf(angle);
    rotY.e[15] = 1;

    return rotY;
}
inline Matrix4 Matrix4::RotateZ(const float& angle)
{
    Matrix4 rotZ;
    rotZ.e[0] = cosf(angle);
    rotZ.e[4] = -sinf(angle);
    rotZ.e[1] = sinf(angle);
    rotZ.e[5] = cosf(angle);
    rotZ.e[10] = 1;
    rotZ.e[15] = 1;

    return rotZ;
}

inline Matrix4 Matrix4::Rotation(const Vector3 &rotation)
{
  return RotateY(rotation.y) * RotateX(rotation.x) * RotateZ(rotation.z);
}

inline Matrix4 Matrix4::AxisRotation(const float angle, const Vector3 &axis)
{
    Matrix4 first;

    first.e[0]  = axis.x * axis.x;
    first.e[1]  = axis.y * axis.x;
    first.e[2]  = axis.z * axis.x;

    first.e[4]  = axis.x * axis.y;
    first.e[5]  = axis.y * axis.y;
    first.e[6]  = axis.z * axis.y;

    first.e[8]  = axis.x * axis.z;
    first.e[9]  = axis.y * axis.z;
    first.e[10] = axis.z * axis.z;

    first.e[15] = 1;

    first = first * (1 - cosf(angle));

    Matrix4 second = Identity() * cosf(angle);

    Matrix4 third;

    third.e[1] = axis.z;
    third.e[2] = -axis.y;
    third.e[4] = -axis.z;
    third.e[6] = axis.x;
    third.e[8] = axis.y;
    third.e[9] = -axis.x;

    third = third * sinf(angle);

    return first + second + third;
}

inline Matrix4 Matrix4::Perspective(const int& width, const int& height, const float& near, const float& far, const float& fov)
{
    Matrix4 projection;
    float yMax = tanf(fov * M_PI / 360);
    float xMax = yMax * ((float)width / height);

    projection.e[0] = 1 / xMax;

    projection.e[5] = 1 / yMax;

    projection.e[10] = - (float)(near + far) / (far - near);
    projection.e[11] = - 1;

    projection.e[14] = - (float)(2 * far * near) / (far - near);

    return projection;
}

inline Matrix4 Matrix4::OrthoMatrix(const int& width, const int& height, const float& near, const float& far)
{
    Matrix4 ortho;

    ortho.e[0]  = (float)height / width ;
    ortho.e[5]  = 1;
    ortho.e[10] = -2 / (far - near);

    ortho.e[12] = 0;
    ortho.e[13] = 0;
    ortho.e[14] = - (far + near) / (far - near);
    ortho.e[15] = 1;

    return ortho;
}

inline Matrix4 Matrix4::GetTranspose() const
{
  return {
    v[0].e[0], v[1].e[0], v[2].e[0], v[3].e[0],
    v[0].e[1], v[1].e[1], v[2].e[1], v[3].e[1],
    v[0].e[2], v[1].e[2], v[2].e[2], v[3].e[2],
    v[0].e[3], v[1].e[3], v[2].e[3], v[3].e[3],
  };
}


std::string Matrix4::ToString() const
{

    return std::to_string(e[0]) + ", " + std::to_string(e[4]) + ", " + std::to_string(e[8]) + ", "+ std::to_string( e[12]) + "\n"
           +std::to_string(e[1]) + ", " + std::to_string(e[5]) + ", " + std::to_string(e[9]) + ", "+ std::to_string( e[13])+ "\n"
           +std::to_string(e[2]) + ", " + std::to_string(e[6]) + ", " + std::to_string(e[10]) + ", "+ std::to_string( e[14])+ "\n"
           +std::to_string(e[3]) + ", " + std::to_string(e[7]) + ", " + std::to_string(e[11]) + ", "+ std::to_string( e[15])+ "\n";
}


#endif // QUACKENGINE_MATRIX4_HPP