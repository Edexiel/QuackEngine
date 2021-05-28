#ifndef QUACKENGINE_TRANSFORM_HPP
#define QUACKENGINE_TRANSFORM_HPP

#include "Scene/Component/ComponentBase.hpp"

#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>
#include "Scene/Core/System.hpp"

namespace Component
{
    struct Transform : public ComponentBase
    {
        Maths::Vector3f position{0, 0, 0};
        Maths::Vector3f scale{1, 1, 1};
        Maths::Quaternion rotation{1, 0, 0, 0};

    public:
        Transform() = default;
        Transform(const Maths::Vector3f& position, const Maths::Vector3f& scale, const Maths::Quaternion& rotation)
        : position(position), scale(scale), rotation(rotation){};

        inline Maths::Matrix4 GetMatrix() const
        {
            return Maths::Matrix4::Translate(position) * rotation.ToMatrix() * Maths::Matrix4::Scale(scale);
        };

        inline Maths::Vector3f Forward() const
        {
            Maths::Vector4f forward = rotation.ToMatrix().GetInvert() * Maths::Vector4f{0,0,1,0};
            return {forward.x, forward.y, forward.z};
        }

        inline Maths::Vector3f Side() const
        {
            Maths::Vector4f side = rotation.ToMatrix().GetInvert() * Maths::Vector4f{1,0,0,0};
            return {side.x, side.y, side.z};
        }

        inline Maths::Vector3f Up() const
        {
            Maths::Vector4f up = rotation.ToMatrix().GetInvert() * Maths::Vector4f{0,1,0,0};
            return {up.x, up.y, up.z};
        }

        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(CEREAL_NVP(position),CEREAL_NVP(scale),CEREAL_NVP(rotation));
        }
    };
}


#endif // QUACKENGINE_TRANSFORM_HPP
