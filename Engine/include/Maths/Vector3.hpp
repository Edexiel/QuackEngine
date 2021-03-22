#ifndef QUACKENGINE_VECTOR3_HPP
#define QUACKENGINE_VECTOR3_HPP

#include <iostream>
#include <cmath>
#include "Maths/Vector2.hpp"

namespace Maths
{
template<typename T>
  struct Vector3
  {
    union
    {
      struct
      {
        T x;
        T y;
        T z;
      };

      struct
      {
        T r;
        T g;
        T b;
      };
      T e[3];
    };

    Vector3<T>() = default;
    Vector3<T>(T _x, T _y, T _z);
    Vector3<T>(Vector2<T> v, T _z);

    T Length() const;
    T SqrLength() const;

    Vector3<T>& Normalize();
    Vector3<T> GetNormalized() const;
    static void Normalized(Vector3<T>& v);

    static T DotProduct(const Vector3<T>& v1, const Vector3<T>& v2);
    static Vector3<T> CrossProduct(const Vector3<T>& v1, const Vector3<T>& v2);

    static Vector3<T> Up();
    static Vector3<T> Down();
    static Vector3<T> Right();
    static Vector3<T> Left();
    static Vector3<T> Forward();
    static Vector3<T> Backward();

    static Vector3<T> Zero();

    Vector3<T> operator+(const Vector3<T>& v2) const;
    Vector3<T> operator-(const Vector3<T>& v2) const;
    Vector3<T> operator*(const T& f) const;
  };

  typedef Vector3<float> Vector3f;
  typedef Vector3<double> Vector3d;
  typedef Vector3<int> Vector3i;
  typedef Vector3<unsigned char> Color3;
  typedef Vector3<float> Color3f;

template<typename T>
inline Vector3<T>::Vector3(T _x, T _y, T _z):x{_x},y{_y},z{_z}{}

template<typename T>
inline Vector3<T>::Vector3(Vector2<T> v, T _z):x{v.x},y{v.y},z{_z}{}

template<typename T>
inline T Vector3<T>::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

template<typename T>
inline T Vector3<T>::SqrLength() const
{
    return x * x + y * y + z * z;
}

template<typename T>
inline Vector3<T>& Vector3<T>::Normalize()
{
    T length = Length();
    if (length > 0)
    {
        x /= length;
        y /= length;
        z /= length;
    }

    return *this;
}

template<typename T>
inline Vector3<T> Vector3<T>::GetNormalized() const
{
    T length = Length();
    if (length > 0)
        return { x / length, y / length, z / length };
    else
        return *this;
}

template<typename T>
inline void Vector3<T>::Normalized(Vector3<T>& v)
{
  T length = v.Length();

  v.x /= length;
  v.y /= length;
  v.z /= length;
}

template<typename T>
inline T Vector3<T>::DotProduct(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<typename T>
inline Vector3<T> Vector3<T>::CrossProduct(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)};
}

template<typename T>
inline Vector3<T> Vector3<T>::Up()
{
  return{0,1,0};
}

template<typename T>
inline Vector3<T> Vector3<T>::Down()
{
  return{0,-1,0};
}

template<typename T>
inline Vector3<T> Vector3<T>::Right()
{
  return{1,0,0};
}

template<typename T>
inline Vector3<T> Vector3<T>::Left()
{
  return{-1, 0, 0};
}

template<typename T>
inline Vector3<T> Vector3<T>::Forward()
{
  return{0, 0, 1};
}

template<typename T>
inline Vector3<T> Vector3<T>::Backward()
{
  return{0, 0, -1};
}

template<typename T>
inline Vector3<T> Vector3<T>::Zero()
{
  return{0, 0, 0};
}

template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& v2) const
{
  return { this->x + v2.x, this->y + v2.y, this->z + v2.z };
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& v2) const
{
  return { this->x - v2.x, this->y - v2.y, this->z - v2.z };
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(const T& f) const
{
  return { this->x * f, this->y * f, this->z * f };
}
}
#endif // QUACKENGINE_VECTOR3_HPP
