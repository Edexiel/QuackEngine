//
// Created by a.figueiredo on 25/01/2021.
//

#ifndef QUACKENGINE_VECTOR4_HPP
#define QUACKENGINE_VECTOR4_HPP

#include <cmath>
#include <string>
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
    std::string ToString() const;

    static float DotProduct(const Vector4& v1, const Vector4& v2);
  };
}


inline Maths::Vector4 operator+(const Maths::Vector4& v1, const Maths::Vector4& v2)
{
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}

inline Maths::Vector4 operator-(const Maths::Vector4& v1, const Maths::Vector4& v2)
{
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}

inline Maths::Vector4 operator*(const Maths::Vector4& v, const float& f)
{
    return { v.x * f, v.y * f, v.z * f, v.w * f };
}


inline float Maths::Vector4::Length() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

inline float Maths::Vector4::SqrLength() const
{
    return x * x + y * y + z * z + w * w;
}

inline Maths::Vector4 Maths::Vector4::Homogenize()
{
    if (w == 0 || w == 1)
        return *this;

    return {x /= w, y /= w, z /= w, w};
}
inline Maths::Vector3 Maths::Vector4::Homogenized() const
{
    if (w == 0 || w == 1)
        return xyz;

    return { x / w, y / w, z / w };
}



inline float Maths::Vector4::DotProduct(const Maths::Vector4& v1, const Maths::Vector4& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline std::string Maths::Vector4::ToString() const
{
    return "x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z) + ", w = " + std::to_string(w);
}

#endif // QUACKENGINE_VECTOR4_HPP
