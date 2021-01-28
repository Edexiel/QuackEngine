#ifndef Quaternion_HPP
#define Quaternion_HPP

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"
#include <cmath>

struct Quaternion
{
  union
  {
      struct
      {
          float w;
          float x;
          float y;
          float z;
      };

      struct
      {
          float a;
          float b;
          float c;
          float d;
      };
      Vector4 v;

      float e[4];

  };
  

  Quaternion();
  Quaternion(const float& _w, const float& _x, const float& _y, const float& _z);
  Quaternion(const float& _w, const Vector3& _axis);
  Quaternion(const Vector3& Axe, const float& angle);



  float GetMagnitude();
  Quaternion GetConjugate();
  void Normalize();
  Quaternion Normalized();
  Matrix4 QuaternionToMatrix();

  static float DotProduct(const Quaternion& quat1, const Quaternion& quat2);
  static Quaternion Slerp(const Quaternion& quat1, const Quaternion& quat2, const float& completion);
  static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
  static Quaternion Nlerp(const Quaternion& q1, const Quaternion& q2, float t);

  Vector3 XYZVector() const;

  ~Quaternion() = default;
};


Quaternion::Quaternion(){}

Quaternion::Quaternion(const float& _w, const float& _x, const float& _y, const float& _z) : x{_x}, y{ _y }, z{ _z }, w{ _w }{}

Quaternion::Quaternion(const float& _w, const Vector3& _axis) : x{ _axis.x }, y{ _axis.y }, z{_axis.z}, w{ _w } {}

Quaternion::Quaternion(const Vector3& Axe, const float& angle)
{
    w = cos(angle / 2);

    x = sin(angle / 2) * Axe.x;
    y = sin(angle / 2) * Axe.y;
    z = sin(angle / 2) * Axe.z;
}


float Quaternion::GetMagnitude()
{
  return sqrtf(w * w + x * x + y * y + z * z);
}
Quaternion Quaternion::GetConjugate()
{
  return {w, -x, -y, -z};
}

void Quaternion::Normalize()
{
    float size = GetMagnitude();

    w  /= size;
    x  /= size;
    y  /= size;
    z  /= size;

}

Quaternion Quaternion::Normalized()
{
    float size = GetMagnitude();

    return{w  /= size, x  /= size, y  /= size,z /= size};
}

Matrix4 Quaternion::QuaternionToMatrix()
{
    Matrix4 result;

    result.e[0] = 1 - (2 * y * y) - (2 * z * z);
    result.e[1] = (2 * x * y) + (2 * w * z);
    result.e[2] = (2 * x * z) - (2 * w * y);

    result.e[4] = (2 * x * y) - (2 * w * z);
    result.e[5] = 1 - (2 * x * x) - (2 * z * z);
    result.e[6] = (2 * y * z) + (2 * w * x);

    result.e[8]  = (2 * x * z) + (2 * w * y);
    result.e[9]  = (2 * y * z) - (2 * w * x);
    result.e[10] = 1 - (2 * x * x) - (2 * y * y);

    result.e[15] = 1;

    return result;
}

float Quaternion::DotProduct(const Quaternion& q1, const Quaternion& q2)
{
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

Quaternion Quaternion::Slerp(const Quaternion& quat1, const Quaternion& quat2, const float& completion)
{
    if (quat1 == quat2 || completion <= 0.f)
    {
        return quat1;
    }
    else if (completion >= 1.0f)
    {
        return quat2;
    }


    float dot = DotProduct(quat1, quat2);

    Quaternion newQ1 = quat1;

    if (dot < 0.0f)
    {
        dot = -dot;
        newQ1 = { -newQ1.w, -newQ1.x, -newQ1.y, -newQ1.z };
    }

    float omega = acosf(dot);
    float sin = sinf(omega);

    if (sin == 0 || isnan(sin)) // Both Quaternion are equal
    {
        return quat1;
    }


    return newQ1 * (sinf((1.0f - completion) * omega) / sin) + quat2 * (sinf(completion * omega) / sin);
}

Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    return q1 * (1 - t) + q2 * t;
}
Quaternion Quaternion::Nlerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    return Lerp(q1, q2, t).Normalized();
}

Vector3 Quaternion::XYZVector() const
{
    return { x, y, z };
}

Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
    return {q1.a + q2.a, q1.b + q2.b, q1.c + q2.c, q1.d + q2.d};
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
{
  return {q1.a - q2.a, q1.b - q2.b, q1.c - q2.c, q1.d - q2.d};
}
Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
  return
    {
      q1.a * q2.a - q1.b * q2.b - q1.c * q2.c - q1.d * q2.d,
      q1.a * q2.b + q1.b * q2.a + q1.c * q2.d - q1.d * q2.c,
      q1.a * q2.c + q1.c * q2.a + q1.b * q2.d - q1.d * q2.b,
      q1.a * q2.d + q1.d * q2.a + q1.b * q2.c - q1.c * q2.b
    };
}

Quaternion operator*(const Quaternion& q, const float& scalar)
{
    return {q.w * scalar, {q.x * scalar, q.y * scalar, q.z * scalar}};
}

Vector3 operator*(const Quaternion& q, const Vector3& v)
{
    return {(v * (2 * (q.w * q.w) - 1)) + (q.XYZVector() * Vector3::DotProduct(v, q.XYZVector()) * 2) + (Vector3::CrossProduct(q.XYZVector(), v) * q.w * 2)};
}
#endif