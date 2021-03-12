#ifndef QUACKENGINE_VECTOR2_HPP
#define QUACKENGINE_VECTOR2_HPP

#include <cmath>
#include <iostream>

namespace Maths
{
template<typename T>
struct Vector2
{
  union
  {
    struct
    {
      T x;
      T y;
    };

    T e[2]{0};
  };
  Vector2<T>(T _x, T _y);
  T Length() const;
  T SqrLength() const;

  Vector2<T>& Normalize();
  Vector2<T> GetNormalized() const;
  static void Normalized(Vector2<T>& v);

  static T DotProduct(const Vector2<T>& v1, const Vector2<T>& v2);

  static Vector2<T> Up();
  static Vector2<T> Down();
  static Vector2<T> Right();
  static Vector2<T> Left();
  static Vector2<T> Zero();

  Vector2<T> operator+(const Vector2<T>& v2) const;
  Vector2<T> operator-(const Vector2<T>& v2) const;
  Vector2<T> operator*(const T& f)    const;
};

typedef Vector2<double> Vector2d;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

template<typename T>
Vector2<T>::Vector2(T _x, T _y): x{_x},y{_y}{}

template<typename T>
inline T Vector2<T>::Length() const
{
  return sqrtf(x*x + y*y);
}

template<typename T>
inline T Vector2<T>::SqrLength() const
{
  return x * x + y * y;
}

template<typename T>
inline Vector2<T>& Vector2<T>::Normalize()
{
  T length = Length();
  if (length < 0)
  {
    x /= length;
    y /= length;
  }

  return *this;
}

template<typename T>
inline Vector2<T> Vector2<T>::GetNormalized() const
{
  T length = Length();
  if (length > 0)
    return { x / length, y / length };
  else
    return *this;
}

template<typename T>
void Vector2<T>::Normalized(Vector2<T>& v)
{
  T length = v.Length();

  v.x /= length;
  v.y /= length;
}

template<typename T>
inline T Vector2<T>::DotProduct(const Vector2<T>& v1, const Vector2<T>& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
Vector2<T> Vector2<T>::Up()
{
  return{0,1};
}

template<typename T>
Vector2<T> Vector2<T>::Down()
{
  return{0,-1};
}

template<typename T>
Vector2<T> Vector2<T>::Right()
{
  return{1,0};
}

template<typename T>
Vector2<T> Vector2<T>::Left()
{
  return{-1, 0};
}

template<typename T>
Vector2<T> Vector2<T>::Zero()
{
  return{0, 0};
}

template<typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& v2) const
{
  return { this->x + v2.x, this->y + v2.y };
}

template<typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& v2) const
{
  return { this->x - v2.x, this->y - v2.y };
}

template<typename T>
inline Vector2<T> Vector2<T>::operator*(const T& f) const
{
  return { this->x * f, this->y * f };
}

}
#endif // QUACKENGINE_VECTOR2_HPP