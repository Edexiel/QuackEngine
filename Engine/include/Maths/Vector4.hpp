//
// Created by a.figueiredo on 25/01/2021.
//

#ifndef QUACKENGINE_VECTOR4_HPP
#define QUACKENGINE_VECTOR4_HPP

#include <cmath>
#include <string>
#include "Vector3.hpp"

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

  float Length()
  {
    return sqrtf(x * x + y * y + z * z + w * w);
  }

  float SqrLength()
  {
    return x * x + y * y + z * z + w * w;
  }

  Vector4 Homogenize()
  {
    if (w == 0 || w == 1)
      return *this;

    x /= w;
    y /= w;
    z /= w;

    return *this;
  }
  static Vector3 homogenize(Vector4& v)
  {
    if (v.w == 0 || v.w == 1)
      return v.xyz;

    return { v.x /= v.w, v.y /= v.w, v.z /= v.w };
  }



  static float DotProduct(Vector4 v1, Vector4 v2)
  {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
  }

  std::string ToString()
  {
    return "x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z) + ", w = " + std::to_string(w);
  }
};

Vector4 operator+(Vector4 v1, Vector4 v2)
{
  return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}

Vector4 operator-(Vector4 v1, Vector4 v2)
{
  return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}

Vector4 operator*(Vector4 v, float f)
{
  return { v.x * f, v.y * f, v.z * f, v.w * f };
}


#endif // QUACKENGINE_VECTOR4_HPP
