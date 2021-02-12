//
// Created by a.figueiredo on 25/01/2021.
//

#ifndef QUACKENGINE_VECTOR2_HPP
#define QUACKENGINE_VECTOR2_HPP

#include <cmath>
#include <string>

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

    // Normalize the vector and return it;
    Vector2 Normalize();

    // Return the vector normalized
    Vector2 Normalized();

    static float DotProduct(const Vector2& v1, const Vector2& v2);

    std::string ToString();
  };
}


Maths::Vector2 operator+(const Maths::Vector2& v, const Maths::Vector2& v2)
{
    return { v.x + v2.x, v.y + v2.y };
}

Maths::Vector2 operator-(const Maths::Vector2& v, const Maths::Vector2& v2)
{
    return { v.x - v2.x, v.y - v2.y };
}

Maths::Vector2 operator*(const Maths::Vector2& v, const float& f)
{
    return { v.x * f, v.y * f };
}

float Maths::Vector2::Length()
{
    return sqrtf(x*x + y*y);
}

float Maths::Vector2::SqrLength()
{
    return x * x + y * y;
}

//Normalize the Maths::Vector and return it;
Maths::Vector2 Maths::Vector2::Normalize()
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
Maths::Vector2 Maths::Vector2::Normalized()
{
    float length = Length();
    if (length > 0)
        return { x / length, y / length };
    else
        return *this;
}

float Maths::Vector2::DotProduct(const Maths::Vector2& v1, const Maths::Vector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

std::string Maths::Vector2::ToString()
{
    return "x = " + std::to_string(x) + ", y = " + std::to_string(y);
}

#endif // QUACKENGINE_VECTOR2_HPP
