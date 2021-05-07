#ifndef QUACKENGINE_VECTOR3_HPP
#define QUACKENGINE_VECTOR3_HPP

#include "Maths/Vector2.hpp"
#include <iostream>

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

        Vector3<T> &Normalize();

        Vector3<T> GetNormalized() const;

        static void Normalize(Vector3<T> &v);

        static T DotProduct(const Vector3<T> &v1, const Vector3<T> &v2);

        static Vector3<T> CrossProduct(const Vector3<T> &v1, const Vector3<T> &v2);

        static Vector3<T> Up();

        static Vector3<T> Down();

        static Vector3<T> Right();

        static Vector3<T> Left();

        static Vector3<T> Forward();

        static Vector3<T> Backward();

        static Vector3<T> Zero();

        static Vector3<T> One();

        Vector3<T> operator+(const Vector3<T> &v2) const;

        Vector3<T> operator-(const Vector3<T> &v2) const;

        Vector3<T> operator*(const T &f) const;

        bool operator==(const Vector3<T>& v2) const;

        bool operator!=(const Vector3<T>& v2) const;
    };

#include "Maths/Vector3.inl"

} // namespace Maths
#endif // QUACKENGINE_VECTOR3_HPP
