#ifndef _SHADOWCIRCLE_HPP
#define _SHADOWCIRCLE_HPP

#include "Scene/Component/ComponentBase.hpp"

namespace Component
{
    struct SimpleShadow : public ComponentBase
    {
        SimpleShadow() = default;

        enum ShadowType {S_SQUARE, S_CIRCLE};

        Maths::Vector2f scale {1.f, 1.f};
        Maths::Vector3f offset {0.f, 0.f, 0.f};
        float yRotation {0.f};
        ShadowType type {ShadowType::S_CIRCLE};

        template<class Archive>
        void save(Archive &archive) const
        {
            archive(CEREAL_NVP(scale), CEREAL_NVP(offset),
                    CEREAL_NVP(type), CEREAL_NVP(yRotation));

        }

        template<class Archive>
        void load(Archive &archive)
        {
            archive(CEREAL_NVP(scale), CEREAL_NVP(offset),
                    CEREAL_NVP(type), CEREAL_NVP(yRotation));
        }
    };
}

#endif //_SHADOWCIRCLE_HPP
