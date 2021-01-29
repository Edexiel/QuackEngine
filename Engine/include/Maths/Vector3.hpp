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



  float Length() const;
  float SqrLength() const;


  //Normalize the vector and return it;
  Vector3 Normalize();

  // Return the vector normalized
  Vector3 Normalized();

  static float DotProduct(Vector3 v1, Vector3 v2);
  static Vector3 CrossProduct(Vector3 v1, Vector3 v2);

  std::string ToString();
 };

Vector3 operator+(const Vector3& v1,const Vector3& v2)
{
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

Vector3 operator*(const Vector3& v, const float& f)
{
    return { v.x * f, v.y * f, v.z * f };
}

inline float Vector3::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

inline float Vector3::SqrLength() const
{
    return x * x + y * y + z * z;
}



inline Vector3 Vector3::Normalize()
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

inline Vector3 Vector3::Normalized()
{
    float length = Length();
    if (length > 0)
        return { x / length, y / length, z / length };
    else
        return *this;
}

inline float Vector3::DotProduct(Vector3 v1, Vector3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3 Vector3::CrossProduct(Vector3 v1, Vector3 v2)
{
    return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)};
}

inline std::string Vector3::ToString()
{
    return "x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", z = " + std::to_string(z);
}

#endif // QUACKENGINE_VECTOR3_HPP
