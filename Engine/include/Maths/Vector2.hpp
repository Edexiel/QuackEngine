#ifndef QUACKENGINE_VECTOR2_HPP
#define QUACKENGINE_VECTOR2_HPP

#include <cmath>
#include "cereal/cereal.hpp"

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
  Vector2<T>() = default;
  Vector2<T>(T _x, T _y);
  T Length() const;
  T SqrLength() const;

  Vector2<T>& Normalize();
  Vector2<T> GetNormalized() const;
  static void Normalize(Vector2<T>& v);

    static T DotProduct(const Vector2<T>& v1, const Vector2<T>& v2);
    static Vector2<T> Lerp(const Vector2<T>& v1, const Vector2<T>& v2, float t);
    static Vector2<T> Rotate(const Vector2<T>& vector, float angle);

  static Vector2<T> Up();
  static Vector2<T> Down();
  static Vector2<T> Right();
  static Vector2<T> Left();
  static Vector2<T> Zero();

  Vector2<T> operator+(const Vector2<T>& v2)   const;
  Vector2<T> operator-(const Vector2<T>& v2)   const;
  Vector2<T> operator*(const T& f)             const;

    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(x),CEREAL_NVP(y));
    }
};
#include "Maths/Vector2.inl"
}
#endif // QUACKENGINE_VECTOR2_HPP