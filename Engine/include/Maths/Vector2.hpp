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
using namespace Maths;
Vector2 operator+(const Vector2& v, const Vector2& v2)
{
    return { v.x + v2.x, v.y + v2.y };
}

Vector2 operator-(const Vector2& v, const Vector2& v2)
{
    return { v.x - v2.x, v.y - v2.y };
}

Vector2 operator*(const Vector2& v, const float& f)
{
    return { v.x * f, v.y * f };
}

float Vector2::Length()
{
    return sqrtf(x*x + y*y);
}

float Vector2::SqrLength()
{
    return x * x + y * y;
}

//Normalize the vector and return it;
Vector2 Vector2::Normalize()
{
    float length = Length();
    if (length < 0)
    {
        x /= length;
        y /= length;
    }

    return *this;
}

// Return the vector normalized
Vector2 Vector2::Normalized()
{
    float length = Length();
    if (length > 0)
        return { x / length, y / length };
    else
        return *this;
}

float Vector2::DotProduct(const Vector2& v1, const Vector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

std::string Vector2::ToString()
{
    return "x = " + std::to_string(x) + ", y = " + std::to_string(y);
}

#endif // QUACKENGINE_VECTOR2_HPP
