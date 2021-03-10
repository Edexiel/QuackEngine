#ifndef QUACKENGINE_VECTOR2_HPP
#define QUACKENGINE_VECTOR2_HPP

#include <cmath>
#include <iostream>

namespace Maths
{
  struct Vector2
  {
    union
    {
      struct
      {
        float x;
        float y;
      };

      float e[2];
    };

    float Length();
    float SqrLength();

    Vector2 Normalize();
    Vector2 Normalized();

    static float DotProduct(const Vector2& v1, const Vector2& v2);

    Vector2 operator+(const Vector2& v2) const;
    Vector2 operator-(const Vector2& v2) const;
    Vector2 operator*(const float& f)    const;
  };

inline float Vector2::Length()
{
    return sqrtf(x*x + y*y);
}

inline float Vector2::SqrLength()
{
    return x * x + y * y;
}

//Normalize the Maths::Vector and return it;
inline Vector2 Vector2::Normalize()
{
    float length = Length();
    if (length < 0)
    {
        x /= length;
        y /= length;
    }

    return *this;
}

// Return the Maths::Vector normalized
inline Vector2 Vector2::Normalized()
{
    float length = Length();
    if (length > 0)
        return { x / length, y / length };
    else
        return *this;
}

inline float Vector2::DotProduct(const Vector2& v1, const Vector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

inline Vector2 Vector2::operator+(const Vector2& v2) const
{
  return { this->x + v2.x, this->y + v2.y };
}

inline Vector2 Vector2::operator-(const Vector2& v2) const
{
  return { this->x - v2.x, this->y - v2.y };
}

inline Vector2 Vector2::operator*(const float& f) const
{
  return { this->x * f, this->y * f };
}
/*
std::ostream& operator<<(std::ostream& os, Vector2 v)
{
  os << "x = " << v.x << "y = " << v.y << std::endl;
  return os;
}*/
}
#endif // QUACKENGINE_VECTOR2_HPP
