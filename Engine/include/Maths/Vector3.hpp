//
// Created by a.figueiredo on 25/01/2021.
//

#ifndef QUACKENGINE_VECTOR3_HPP
#define QUACKENGINE_VECTOR3_HPP

#include <cmath>
#include <string>

struct Vector3
{
  union
  {
    struct
    {
      float x;
      float y;
      float z;
    };

    struct
    {
      float r;
      float g;
      float b;
    };
    float e[3];
  };

  float Length()
  {
    return sqrtf(x * x + y * y + z * z);
  }

  float SqrLength()
  {
    return x * x + y * y + z * z;
  }

  //Normalize the vector and return it;
  Vector3 Normalize()
  {
    float length = Length();
    if (length > 0)
    {
      x /= length;
      y /= length;
      z /= length;
    }

    return *this;
  }

  // Return the vector normalized
  Vector3 Normalized()
  {
    float length = Length();
    if (length > 0)
      return { x / length, y / length, z / length };
    else
      return *this;
  }

  static float DotProduct(Vector3 v1, Vector3 v2)
  {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  std::string ToString()
  {
    return "x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z);
  }
};

Vector3 operator+(Vector3 v1, Vector3 v2)
{
  return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vector3 operator-(Vector3 v1, Vector3 v2)
{
  return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

Vector3 operator*(Vector3 v, float f)
{
  return { v.x * f, v.y * f, v.z * f };
}

#endif // QUACKENGINE_VECTOR3_HPP
