#ifndef QUACKENGINE_QUATERNION_HPP
#define QUACKENGINE_QUATERNION_HPP

#include <cmath>
#include "Common.hpp"

#include "Matrix4.hpp"
#include "cereal/cereal.hpp"


namespace Maths
{
    struct Quaternion
    {
        union
        {
            struct
            {
                float w;
                float x;
                float y;
                float z;
            };

            float e[4]{0};
        };

        Quaternion() : w{1}, x{0}, y{0}, z{0}
        {};
        Quaternion(float _w,
                   float _x,
                   float _y,
                   float _z);
        Quaternion(float _w, const Vector3f &_axis);
        Quaternion(const Vector3f &axis, float angle);

        static Quaternion AngleAxis(float angle, Vector3f axis);
        static Quaternion Identity();

        float GetMagnitude() const;
        Quaternion GetConjugate() const;
        Quaternion GetInverse() const;
        Quaternion &Normalize();
        Quaternion GetNormalized() const;
        static void Normalize(Quaternion &q);
        static float NormalizeAxis(float angle);
        Matrix4 ToMatrix() const;
        Vector3f ToEuler() const;
        static Quaternion EulerToQuaternion(Vector3f rot);

        static float DotProduct(const Quaternion &q1, const Quaternion &q);
        static Quaternion Slerp(const Quaternion &q1,
                                const Quaternion &q,
                                float completion);
        static Quaternion Lerp(const Quaternion &q1,
                               const Quaternion &q,
                               float t);
        static Quaternion Nlerp(const Quaternion &q1,
                                const Quaternion &q,
                                float t);
        static Quaternion LookAt(const Vector3f& origin, const Vector3f& target);

        Vector3f XYZVector() const;

        ~Quaternion() = default;

        Quaternion operator+(const Quaternion &q) const;
        Quaternion operator-(const Quaternion &q) const;
        Quaternion operator*(const Quaternion &q) const;
        Quaternion operator*(float scalar) const;
        Quaternion operator/(float scalar) const;
        Vector3f operator*(const Vector3f &v) const;
        bool operator==(const Quaternion &q) const;

        template<class Archive>
        void serialize(Archive &archive)
        {
            archive(CEREAL_NVP(w),CEREAL_NVP(x),CEREAL_NVP(y),CEREAL_NVP(z));
        }
    };

#include "Maths/Quaternion.inl"

}

#endif