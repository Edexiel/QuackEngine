#ifndef QUACKENGINE_QUATERNION_HPP
#define QUACKENGINE_QUATERNION_HPP

#include "Matrix4.hpp"
#include <cmath>

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

    Quaternion():w{1}, x{0},y{0},z{0}{};
    Quaternion(float _w,
               float _x,
               float _y,
               float _z);
    Quaternion(float _w, const Vector3f& _axis);
    Quaternion(const Vector3f& Axe, float angle);

    float GetMagnitude() const;
    Quaternion GetConjugate() const;
    Quaternion GetInverse() const;
    Quaternion& Normalize();
    Quaternion GetNormalized() const;
    static void Normalize(Quaternion& q);
    Matrix4 ToMatrix() const;

    static float DotProduct(const Quaternion& q1, const Quaternion& q);
    static Quaternion Slerp(const Quaternion& q1,
                            const Quaternion& q,
                            const float& completion);
    static Quaternion Lerp(const Quaternion& q1,
                           const Quaternion& q,
                           const float& t);
    static Quaternion Nlerp(const Quaternion& q1,
                            const Quaternion& q,
                            const float& t);

    Vector3f XYZVector() const;

    ~Quaternion() = default;

    Quaternion operator+ (const Quaternion& q) const;
    Quaternion operator- (const Quaternion& q) const;
    Quaternion operator* (const Quaternion& q) const;
    Quaternion operator* (float scalar) const;
    Quaternion operator/ (float scalar) const;
    Vector3f   operator* (const Vector3f& v)   const;
    bool       operator==(const Quaternion& q) const;
  };

inline Quaternion::Quaternion(float _w, float _x, float _y, float _z) : x{_x}, y{ _y }, z{ _z }, w{ _w }{}

inline Quaternion::Quaternion(float _w, const Vector3f& _axis) : x{ _axis.x }, y{ _axis.y }, z{_axis.z}, w{ _w } {}

inline Quaternion::Quaternion(const Vector3f& Axe, float angle)
{
    w = cosf(angle / 2);

    x = sinf(angle / 2) * Axe.x;
    y = sinf(angle / 2) * Axe.y;
    z = sinf(angle / 2) * Axe.z;
}


inline float Quaternion::GetMagnitude() const
{
  return sqrtf(w * w + x * x + y * y + z * z);
}
inline Quaternion Quaternion::GetConjugate() const
{
  return {w, -x, -y, -z};
}

inline Quaternion& Quaternion::Normalize()
{
    float size = GetMagnitude();

    w  /= size;
    x  /= size;
    y  /= size;
    z  /= size;

    return *this;
}

inline Quaternion Quaternion::GetNormalized() const
{
    float size = GetMagnitude();

    return{w / size, x  / size, y  / size,z / size};
}

inline void Quaternion::Normalize(Quaternion& q)
{
  float size = q.GetMagnitude();

  q.w  /= size;
  q.x  /= size;
  q.y  /= size;
  q.z  /= size;
}

inline Maths::Matrix4 Quaternion::ToMatrix() const
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

inline float Quaternion::DotProduct(const Quaternion& q1, const Quaternion& q)
{
    return q1.x * q.x + q1.y * q.y + q1.z * q.z + q1.w * q.w;
}

inline Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, const float& completion)
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

    Quaternion newQ1 = q1;

    if (dot < 0.0f)
    {
        dot = -dot;
        newQ1 = { -newQ1.w, -newQ1.x, -newQ1.y, -newQ1.z };
    }

    float omega = acosf(dot);
    float sin = sinf(omega);

    if (sin == 0 || std::isnan(sin)) // Both Quaternion are equal
    {
        return q1;
    }


    return newQ1 * (sinf((1.0f - completion) * omega) / sin) + q2 * (sinf(completion * omega) / sin);
}

inline Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, const float& t)
{
    return q1 * (1 - t) + q2 * t;
}
inline Quaternion Quaternion::Nlerp(const Quaternion& q1, const Quaternion& q2, const float& t)
{
    return Lerp(q1, q2, t).GetNormalized();
}

inline Maths::Vector3f Quaternion::XYZVector() const
{
    return { x, y, z };
}

inline Quaternion Quaternion::GetInverse() const
{
  Quaternion q = *this;
  return q / (w * w + x * x + y * y + z * z);
}

inline Quaternion Quaternion::operator+(const Quaternion& q) const
{
  return {this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z};
}

inline Quaternion Quaternion::operator-(const Quaternion& q) const
{
  return {this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z};
}
inline Quaternion Quaternion::operator*(const Quaternion& q) const
{
  return {(this->w * q.w) - Maths::Vector3f::DotProduct(this->XYZVector(), q.XYZVector()), (q.XYZVector() * this->w) + (this->XYZVector() * q.w) + Maths::Vector3f::CrossProduct(this->XYZVector(), q.XYZVector())};
}

inline Quaternion Quaternion::operator*(float scalar) const
{
  return {this->w * scalar, {this->x * scalar, this->y * scalar, this->z * scalar}};
}

inline Quaternion Quaternion::operator/(float scalar) const
{
  return {this->w / scalar, this->x / scalar, this->y / scalar, this->z / scalar};
}

inline Vector3f Quaternion::operator*(const Vector3f& v) const
{
  Vector3f u = XYZVector();
  return u * 2 *(Vector3f::DotProduct(u, v)) + v * (w * w - Vector3f::DotProduct(u, u)) + Vector3f::CrossProduct(u,v) * 2 * w;
}

inline bool Quaternion::operator==(const Quaternion& q) const
{
  return (this->x == q.x && this->y == q.y && this->z == q.z && this->w == q.w);
}
}

#endif