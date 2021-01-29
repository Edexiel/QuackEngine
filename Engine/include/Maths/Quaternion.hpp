#ifndef Quaternion_HPP
#define Quaternion_HPP

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"
#include <cmath>
#include "string"

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

      float e[4];
  };
  

  Quaternion();
  Quaternion(const float& _w, const float& _x, const float& _y, const float& _z);
  Quaternion(const float& _w, const Vector3& _axis);
  Quaternion(const Vector3& Axe, const float& angle);



  float GetMagnitude() const;
  Quaternion GetConjugate() const;
  Quaternion GetInverse() const;
  void Normalize();
  Quaternion Normalized() const;
  Matrix4 QuaternionToMatrix() const;

  static float DotProduct(const Quaternion& quat1, const Quaternion& quat2);
  static Quaternion Slerp(const Quaternion& quat1, const Quaternion& quat2, const float& completion);
  static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
  static Quaternion Nlerp(const Quaternion& q1, const Quaternion& q2, float t);

  Vector3 XYZVector() const;

  std::string ToString() const;

  ~Quaternion() = default;
};

Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
    return {q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z};
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
{
    return {q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z};
}
Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
    return {(q1.w * q2.w) - Vector3::DotProduct(q1.XYZVector(), q2.XYZVector()), (q2.XYZVector() * q1.w) + (q1.XYZVector() * q2.w) + Vector3::CrossProduct(q1.XYZVector(), q2.XYZVector())};
}

Quaternion operator*(const Quaternion& q, const float& scalar)
{
    return {q.w * scalar, {q.x * scalar, q.y * scalar, q.z * scalar}};
}

Quaternion operator/(const Quaternion& quat, const float& scalar)
{
    Quaternion result(quat.w / scalar, quat.x / scalar, quat.y / scalar, quat.z / scalar);
    return result;
}

Vector3 operator*(const Quaternion& q, const Vector3& v)
{
    return {(v * (2 * (q.w * q.w) - 1)) + (q.XYZVector() * Vector3::DotProduct(v, q.XYZVector()) * 2) + (Vector3::CrossProduct(q.XYZVector(), v) * q.w * 2)};
}

bool operator==(const Quaternion& quat1, const Quaternion& quat2)
{
    return (quat1.x == quat2.x && quat1.y == quat2.y && quat1.z == quat2.z && quat1.w == quat2.w);
}

Quaternion::Quaternion(){}

Quaternion::Quaternion(const float& _w, const float& _x, const float& _y, const float& _z) : x{_x}, y{ _y }, z{ _z }, w{ _w }{}

Quaternion::Quaternion(const float& _w, const Vector3& _axis) : x{ _axis.x }, y{ _axis.y }, z{_axis.z}, w{ _w } {}

Quaternion::Quaternion(const Vector3& Axe, const float& angle)
{
    w = cosf(angle / 2);

    x = sinf(angle / 2) * Axe.x;
    y = sinf(angle / 2) * Axe.y;
    z = sinf(angle / 2) * Axe.z;
}


float Quaternion::GetMagnitude() const
{
  return sqrtf(w * w + x * x + y * y + z * z);
}
Quaternion Quaternion::GetConjugate() const
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

Quaternion Quaternion::Normalized() const
{
    float size = GetMagnitude();

    return{w / size, x  / size, y  / size,z / size};
}

Matrix4 Quaternion::QuaternionToMatrix() const
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

    if (sin == 0 || std::isnan(sin)) // Both Quaternion are equal
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

std::string Quaternion::ToString() const
{
    return "w = " + std::to_string(w) + ", x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z);
}

Quaternion Quaternion::GetInverse() const
{
    return *this / (w * w + x * x + y * y + z * z);
}

#endif