#ifndef QUACKENGINE_VECTOR4_HPP
#define QUACKENGINE_VECTOR4_HPP

#include <cmath>
#include "Vector3.hpp"

namespace Maths
{
template<typename T>
  struct Vector4
  {
    union
    {
      struct
      {
        T x, y, z, w;
      };

      struct
      {
        T r, g, b, a;
      };
      T e[4];
      Vector3<T> xyz;
    };

    Vector4() = default;
    Vector4(T _x, T _y, T _z, T _w);
    Vector4(Vector3<T> v, T _w);

    T Length() const;
    T SqrLength() const;

    Vector4<T>& Homogenize();
    Vector3<T> GetHomogenized() const;
    static void Homogenize(Vector4<T>& v);

    static T DotProduct(const Vector4<T>& v1, const Vector4<T>& v2);
    static Vector4<T> Lerp(const Vector4<T>& v1, const Vector4<T>& v2, float t);

    static Vector4<T> Zero();
    static Vector4<T> One();

    Vector4<T> operator+(const Vector4<T>& v2) const;
    Vector4<T> operator-(const Vector4<T>& v2) const;
    Vector4<T> operator*(const T& f) const;
  };

  typedef Vector4<float> Vector4f;
  typedef Vector4<float> Color4f;
  typedef Vector4<double> Vector4d;

template<typename T>
inline Vector4<T>::Vector4(T _x, T _y, T _z, T _w):x{_x}, y{_y}, z{_z}, w{_w}{}

template<typename T>
inline Vector4<T>::Vector4(Vector3<T> v, T _w):x{v.x}, y{v.y}, z{v.z}, w{_w}{}
template<typename T>
inline T Vector4<T>::Length() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

template<typename T>
inline T Vector4<T>::SqrLength() const
{
    return x * x + y * y + z * z + w * w;
}

template<typename T>
inline Vector4<T>& Vector4<T>::Homogenize()
{
  if (w != 0 && w != 1)
  {
    x /= w;
    y /= w;
    z /= w;
  }

  return *this;
}

template<typename T>
inline Vector3<T> Vector4<T>::GetHomogenized() const
{
    if (w == 0 || w == 1)
        return xyz;

    return { x / w, y / w, z / w };
}

template<typename T>
void Vector4<T>::Homogenize(Vector4<T>& v)
{
  if (v.w != 0 && v.w != 1)
  {
    v.x /= v.w;
    v.y /= v.w;
    v.z /= v.w;
  }
}

template<typename T>
inline T Vector4<T>::DotProduct(const Vector4<T>& v1, const Vector4<T>& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template<typename T>
inline Vector4<T> Vector4<T>::Zero()
{
  return {0, 0, 0, 0};
}

template<typename T>
inline Vector4<T> Vector4<T>::One()
{
  return {1, 1, 1, 1};
}

template<typename T>
inline Vector4<T> Vector4<T>::operator+(const Vector4<T>& v2) const
{
  return { this->x + v2.x, this->y + v2.y, this->z + v2.z, this->w + v2.w };
}

template<typename T>
inline Vector4<T> Vector4<T>::operator-(const Vector4<T>& v2) const
{
  return { this->x - v2.x, this->y - v2.y, this->z - v2.z, this->w - v2.w };
}

template<typename T>
inline Vector4<T> Vector4<T>::operator*(const T& f) const
{
  return { this->x * f, this->y * f, this->z * f, this->w * f };
}

    template<typename T>
    Vector4<T> Vector4<T>::Lerp(const Vector4<T> &v1, const Vector4<T> &v2, float t)
    {
        return v1 * (1 - t) + v2 * t;
    }
}
#endif // QUACKENGINE_VECTOR4_HPP
