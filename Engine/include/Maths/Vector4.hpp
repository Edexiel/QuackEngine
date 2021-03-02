#ifndef QUACKENGINE_VECTOR4_HPP
#define QUACKENGINE_VECTOR4_HPP

#include <cmath>
#include "Vector3.hpp"

namespace Maths
{
  struct Vector4
  {
    union
    {
      struct
      {
        float x, y, z, w;
      };

      struct
      {
        float r, g, b, a;
      };
      float e[4];
      Vector3 xyz;
    };

    float Length() const;
    float SqrLength() const;

    Vector4 Homogenize();
    Vector3 Homogenized() const;

    static float DotProduct(const Vector4& v1, const Vector4& v2);

    Vector4 operator+(const Vector4& v2) const;
    Vector4 operator-(const Vector4& v2) const;
    Vector4 operator*(const float& f) const;

//    std::ostream& operator<<(std::ostream& os);
  };


inline float Vector4::Length() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

inline float Vector4::SqrLength() const
{
    return x * x + y * y + z * z + w * w;
}

inline Vector4 Vector4::Homogenize()
{
    if (w == 0 || w == 1)
        return *this;

    return {x /= w, y /= w, z /= w, w};
}
inline Maths::Vector3 Vector4::Homogenized() const
{
    if (w == 0 || w == 1)
        return xyz;

    return { x / w, y / w, z / w };
}



inline float Vector4::DotProduct(const Vector4& v1, const Vector4& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline Vector4 Vector4::operator+(const Vector4& v2) const
{
  return { this->x + v2.x, this->y + v2.y, this->z + v2.z, this->w + v2.w };
}

inline Vector4 Vector4::operator-(const Vector4& v2) const
{
  return { this->x - v2.x, this->y - v2.y, this->z - v2.z, this->w - v2.w };
}

inline Vector4 Vector4::operator*(const float& f) const
{
  return { this->x * f, this->y * f, this->z * f, this->w * f };
}
/*
std::ostream& operator<<(std::ostream &os, Vector4 v)
{
  os << "x = " << v.x << "y = " << v.y << "z = " << v.z << "w = " << v.w << std::endl;
  return os;
}*/
}
#endif // QUACKENGINE_VECTOR4_HPP
