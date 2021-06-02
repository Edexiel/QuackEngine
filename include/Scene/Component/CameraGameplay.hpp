#ifndef QUACKENGINE_CAMERAGAMEPLAY_HPP
#define QUACKENGINE_CAMERAGAMEPLAY_HPP

#include "Scene/Component/ComponentBase.hpp"
#include "Scene/Core/Types.hpp"
#include "Maths/Vector3.hpp"

namespace Component
{
    struct CameraGameplay : public ComponentBase
    {
        Entity entityToFollow{0};
        Maths::Vector3f distance{0,0,0};// distance between entityToFollow and the cam

        template<class Archive>
        void serialize(Archive &archive)
        {
            archive(distance);
        }
    };
}

#endif //QUACKENGINE_CAMERAGAMEPLAY_HPP
