#ifndef QUACKENGINE_VECTOR4_HPP
#define QUACKENGINE_VECTOR4_HPP

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
        Vector4(T n);

        T Length() const;
        T SqrLength() const;

        Vector4<T> &Homogenize();
        Vector3<T> GetHomogenized() const;
        static void Homogenize(Vector4<T> &v);

        static T DotProduct(const Vector4<T> &v1, const Vector4<T> &v2);

        static Vector4<T> Zero();
        static Vector4<T> One();

        Vector4<T> operator+(const Vector4<T> &v2) const;
        Vector4<T> operator-(const Vector4<T> &v2) const;
        Vector4<T> operator*(const T &f) const;
    };

#include "Maths/Vector4.inl"

}
#endif // QUACKENGINE_VECTOR4_HPP
