#ifndef QUACKENGINE_MATRIX4_HPP
#define QUACKENGINE_MATRIX4_HPP

#include "Maths/Vector4.hpp"
#include <iostream>

namespace Maths
{
  struct Matrix4
  {
    union
    {
      float e[16]{ 0 };
      Vector4f v[4];
    };

    static Matrix4 Identity();
    static Matrix4 Scale(const float& s);
    static Matrix4 Scale(const Vector3f& v);
    static Matrix4 Translate(const Vector3f& v);
    static Matrix4 RotateX(const float& angle);
    static Matrix4 RotateY(const float& angle);
    static Matrix4 RotateZ(const float& angle);
    static Matrix4 Rotation(const Vector3f& rotation);
    static Matrix4 AxisRotation(const float angle, const Vector3f& axis);
    static Matrix4 Perspective(const int& width,
                               const int& height,
                               const float& near,
                               const float& far,
                               const float& fov);
    static Matrix4 OrthoMatrix(const int& width,
                               const int& height,
                               const float& near,
                               const float& far);

    static Matrix4 ViewportMatrix(const int& x,
                                  const int& y,
                                  const int &width,
                                  const int &height);

    Matrix4 GetTranspose() const;

    Matrix4 operator*(const Matrix4& m);
    Matrix4& operator*=(const Matrix4& m);
    Matrix4 operator*(float f);
    Vector4f operator*(const Vector4f& v) const;
    Matrix4 operator+(const Matrix4& m2);
  };

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

inline Matrix4 Matrix4::Scale(const Maths::Vector3f& v)
{
    Matrix4 mat;
    mat.e[0] = v.x;
    mat.e[5] = v.y;
    mat.e[10] = v.z;
    mat.e[15] = 1;

    return mat;
}

inline Matrix4 Matrix4::Translate(const Maths::Vector3f& v)
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

inline Matrix4 Matrix4::Rotation(const Vector3f &rotation)
{
  return RotateY(rotation.y) * RotateX(rotation.x) * RotateZ(rotation.z);
}

inline Matrix4 Matrix4::AxisRotation(const float angle, const Vector3f &axis)
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
  float const a = 1.f / tanf(fov / 2.f);
  float const aspect = width / height;
  projection.e[0] = a / aspect;

  projection.e[5] = a;

  projection.e[10] = -((far + near) / (far - near));
  projection.e[14] = -1.f;

  projection.e[11] = -((2.f * far * near) / (far - near));


  return projection;
}

inline Matrix4 Matrix4::OrthoMatrix(const int& width, const int& height, const float& near, const float& far)
{
    Matrix4 ortho;

    ortho.e[0]  = (float)height / width;
    ortho.e[5]  = 1;
    ortho.e[10] = -2 / (far - near);

    ortho.e[12] = 0;
    ortho.e[13] = 0;
    ortho.e[14] = - (far + near) / (far - near);
    ortho.e[15] = 1;

    return ortho;
}

inline Matrix4 Matrix4::ViewportMatrix(const int& x, const int& y, const int &width, const int &height)
{
    Matrix4 view;

    view.e[0] = (float)width/2;
    view.e[5] = (float)height/2;

    view.e[12] = x + (float)width/2;
    view.e[13] = y + (float)height/2;

    view.e[10] = 1;

    view.e[15] = 1;

    return view;
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

inline Matrix4 Matrix4::operator*(const Matrix4& m)
{
  Matrix4 result;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        result.e[i + j * 4] += this->e[i + k * 4] * m.e[k + j * 4];

  return result;
}
inline Matrix4& Matrix4::operator*=(const Matrix4& m)
{
  *this = *this * m;
  return *this;
}

inline Matrix4 Matrix4::operator*(float f)
{
  Matrix4 result;

  for (unsigned int i = 0 ; i < 16 ; i++)
    result.e[i] = this->e[i] * f;

  return result;
}

inline Vector4f Matrix4::operator*(const Vector4f& v) const
{
  Vector4f result;

  result.x = v.x * e[0] + v.y * e[1] + v.z * e[2] + v.w * e[3];
  result.y = v.x * e[4] + v.y * e[5] + v.z * e[6] + v.w * e[7];
  result.z = v.x * e[8] + v.y * e[9] + v.z * e[10] + v.w * e[11];
  result.w = v.x * e[12] + v.y * e[13] + v.z * e[14] + v.w * e[15];

  return result;
}

inline Matrix4 Matrix4::operator+(const Matrix4& m2)
{
  Matrix4 result;

  for (unsigned int i = 0; i < 16 ; i++)
    result.e[i] = this->e[i] + m2.e[i];

  return result;
}

/*std::ostream& operator<<(std::ostream &os, const Matrix4& m)
{
  os << m.e[0] << ", " << m.e[4] << ", " << m.e[8] << ", " << m.e[12] << "\n"
     << m.e[1] << ", " << m.e[5] << ", " << m.e[9] << ", " << m.e[13] << "\n"
     << m.e[2] << ", " << m.e[6] << ", " << m.e[10] << ", " << m.e[14] << "\n"
     << m.e[3] << ", " << m.e[7] << ", " << m.e[11] << ", " << m.e[15] << "\n";

  return os;
}*/
}


#endif // QUACKENGINE_MATRIX4_HPP