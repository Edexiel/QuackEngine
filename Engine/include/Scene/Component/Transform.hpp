#ifndef QUACKENGINE_TRANSFORM_HPP
#define QUACKENGINE_TRANSFORM_HPP

#include <Maths/Quaternion.hpp>
#include <Maths/Vector3.hpp>
#include "Scene/Core/System.hpp"

namespace Component
{
    struct Transform
    {
        Maths::Vector3f position{0, 0, 0};
        Maths::Vector3f scale{1, 1, 1};
        Maths::Quaternion rotation{1, 0, 0, 0};

//        Maths::Vector3f forward{0, 0, 1};
//        Maths::Vector3f right{1, 0, 0};

        inline Maths::Matrix4 GetMatrix() const
        {
            return Maths::Matrix4::Translate(position) * rotation.ToMatrix() * Maths::Matrix4::Scale(scale);
        };

        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(CEREAL_NVP(position),CEREAL_NVP(scale),CEREAL_NVP(rotation));
        }
    };
}


#endif // QUACKENGINE_TRANSFORM_HPP
