//
// Created by a.figueiredo on 25/01/2021.
//

#ifndef QUACKENGINE_VECTOR2_HPP
#define QUACKENGINE_VECTOR2_HPP

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

  float Length()
  {
    return sqrtf(x*x + y*y);
  }

  float SqrLength()
  {
    return x * x + y * y;
  }

  //Normalize the vector and return it;
  Vector2 Normalize()
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
  Vector2 Normalized()
  {
    float length = Length();
    if (length > 0)
      return { x / length, y / length };
    else
      return *this;
  }

  static float DotProduct(Vector2 v1, Vector2 v2)
  {
    return v1.x * v2.x + v1.y * v2.y;
  }

  std::string ToString()
  {
    return "x = " + std::to_string(x) + ", y = " + std::to_string(y);
  }
};

Vector2 operator+(Vector2 v, Vector2 v2)
{
  return { v.x + v2.x, v.y + v2.y };
}

Vector2 operator-(Vector2 v, Vector2 v2)
{
  return { v.x - v2.x, v.y - v2.y };
}

Vector2 operator*(Vector2 v, float f)
{
  return { v.x * f, v.y * f };
}

#endif // QUACKENGINE_VECTOR2_HPP
