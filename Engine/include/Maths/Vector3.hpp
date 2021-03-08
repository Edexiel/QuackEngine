#ifndef QUACKENGINE_VECTOR3_HPP
#define QUACKENGINE_VECTOR3_HPP

#include <iostream>
#include <cmath>

namespace Maths
{
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

    // Normalize the vector and return it;
    Vector3 Normalize();

    // Return the vector normalized
    Vector3 Normalized();

    static float DotProduct(const Vector3& v1, const Vector3& v2);
    static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);

    Vector3 operator+(const Vector3& v2) const;
    Vector3 operator-(const Vector3& v2) const;
    Vector3 operator*(const float& f) const;

    friend std::ostream& operator<<(std::ostream &os, Vector3 v);
  };



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

inline float Vector3::DotProduct(const Vector3& v1, const Vector3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3 Vector3::CrossProduct(const Vector3& v1, const Vector3& v2)
{
    return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)};
}

inline Vector3 Vector3::operator+(const Vector3& v2) const
{
  return { this->x + v2.x, this->y + v2.y, this->z + v2.z };
}

inline Vector3 Vector3::operator-(const Vector3& v2) const
{
  return { this->x - v2.x, this->y - v2.y, this->z - v2.z };
}

inline Vector3 Vector3::operator*(const float& f) const
{
  return { this->x * f, this->y * f, this->z * f };
}
/*
std::ostream& operator<<(std::ostream &os, Vector3 v)
{
  os << "x = " << v.x << "y = " << v.y << "z = " << v.z << std::endl;
  return os;
}*/
}
#endif // QUACKENGINE_VECTOR3_HPP
