#ifndef QUACKENGINE_QUATERNION_HPP
#define QUACKENGINE_QUATERNION_HPP

#include "Matrix4.hpp"
#include <cmath>
#include <string>

namespace Maths
{
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

      float e[4]{ 0 };
    };

    Quaternion();
    Quaternion(const float& _w,
               const float& _x,
               const float& _y,
               const float& _z);
    Quaternion(const float& _w, const Vector3& _axis);
    Quaternion(const Vector3& Axe, const float& angle);

    float GetMagnitude() const;
    Quaternion GetConjugate() const;
    Quaternion GetInverse() const;
    void Normalize();
    Quaternion Normalized() const;
    Matrix4 QuaternionToMatrix() const;

    static float DotProduct(const Quaternion& q1, const Quaternion& q2);
    static Quaternion Slerp(const Quaternion& q1,
                            const Quaternion& q2,
                            const float& completion);
    static Quaternion Lerp(const Quaternion& q1,
                           const Quaternion& q2,
                           const float& t);
    static Quaternion Nlerp(const Quaternion& q1,
                            const Quaternion& q2,
                            const float& t);

    Vector3 XYZVector() const;

    std::string ToString() const;

    ~Quaternion() = default;
  };
}
Maths::Quaternion operator+(const Maths::Quaternion& q1, const Maths::Quaternion& q2)
{
    return {q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z};
}

Maths::Quaternion operator-(const Maths::Quaternion& q1, const Maths::Quaternion& q2)
{
    return {q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z};
}
Maths::Quaternion operator*(const Maths::Quaternion& q1, const Maths::Quaternion& q2)
{
    return {(q1.w * q2.w) - Maths::Vector3::DotProduct(q1.XYZVector(), q2.XYZVector()), (q2.XYZVector() * q1.w) + (q1.XYZVector() * q2.w) + Maths::Vector3::CrossProduct(q1.XYZVector(), q2.XYZVector())};
}

Maths::Quaternion operator*(const Maths::Quaternion& q, const float& scalar)
{
    return {q.w * scalar, {q.x * scalar, q.y * scalar, q.z * scalar}};
}

Maths::Quaternion operator/(const Maths::Quaternion& q, const float& scalar)
{
    Maths::Quaternion result(q.w / scalar, q.x / scalar, q.y / scalar, q.z / scalar);
    return result;
}

Maths::Vector3 operator*(const Maths::Quaternion& q, const Maths::Vector3& v)
{
    return {(v * (2 * (q.w * q.w) - 1)) + (q.XYZVector() * Maths::Vector3::DotProduct(v, q.XYZVector()) * 2) + (Maths::Vector3::CrossProduct(q.XYZVector(), v) * q.w * 2)};
}

bool operator==(const Maths::Quaternion& q1, const Maths::Quaternion& q2)
{
    return (q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w);
}

Maths::Quaternion::Quaternion(){}

Maths::Quaternion::Quaternion(const float& _w, const float& _x, const float& _y, const float& _z) : x{_x}, y{ _y }, z{ _z }, w{ _w }{}

Maths::Quaternion::Quaternion(const float& _w, const Vector3& _axis) : x{ _axis.x }, y{ _axis.y }, z{_axis.z}, w{ _w } {}

Maths::Quaternion::Quaternion(const Vector3& Axe, const float& angle)
{
    w = cosf(angle / 2);

    x = sinf(angle / 2) * Axe.x;
    y = sinf(angle / 2) * Axe.y;
    z = sinf(angle / 2) * Axe.z;
}


float Maths::Quaternion::GetMagnitude() const
{
  return sqrtf(w * w + x * x + y * y + z * z);
}
Maths::Quaternion Maths::Quaternion::GetConjugate() const
{
  return {w, -x, -y, -z};
}

void Maths::Quaternion::Normalize()
{
    float size = GetMagnitude();

    w  /= size;
    x  /= size;
    y  /= size;
    z  /= size;

}

Maths::Quaternion Maths::Quaternion::Normalized() const
{
    float size = GetMagnitude();

    return{w / size, x  / size, y  / size,z / size};
}

Maths::Matrix4 Maths::Quaternion::QuaternionToMatrix() const
{
    Maths::Matrix4 result;

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

float Maths::Quaternion::DotProduct(const Maths::Quaternion& q1, const Maths::Quaternion& q2)
{
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

Maths::Quaternion Maths::Quaternion::Slerp(const Maths::Quaternion& q1, const Maths::Quaternion& q2, const float& completion)
{
    if (q1 == q2 || completion <= 0.f)
    {
        return q1;
    }
    else if (completion >= 1.0f)
    {
        return q2;
    }


    float dot = DotProduct(q1, q2);

    Maths::Quaternion newQ1 = q1;

    if (dot < 0.0f)
    {
        dot = -dot;
        newQ1 = { -newQ1.w, -newQ1.x, -newQ1.y, -newQ1.z };
    }

    float omega = acosf(dot);
    float sin = sinf(omega);

    if (sin == 0 || std::isnan(sin)) // Both Maths::Quaternion are equal
    {
        return q1;
    }


    return newQ1 * (sinf((1.0f - completion) * omega) / sin) + q2 * (sinf(completion * omega) / sin);
}

Maths::Quaternion Maths::Quaternion::Lerp(const Maths::Quaternion& q1, const Maths::Quaternion& q2, const float& t)
{
    return q1 * (1 - t) + q2 * t;
}
Maths::Quaternion Maths::Quaternion::Nlerp(const Maths::Quaternion& q1, const Maths::Quaternion& q2, const float& t)
{
    return Lerp(q1, q2, t).Normalized();
}

Maths::Vector3 Maths::Quaternion::XYZVector() const
{
    return { x, y, z };
}

std::string Maths::Quaternion::ToString() const
{
    return "w = " + std::to_string(w) + ", x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z);
}

Maths::Quaternion Maths::Quaternion::GetInverse() const
{
    return *this / (w * w + x * x + y * y + z * z);
}

#endif