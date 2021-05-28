#ifndef QUACKENGINE_CHARACTERCONTROLLER_HPP
#define QUACKENGINE_CHARACTERCONTROLLER_HPP

#include "Maths/Vector3.hpp"
#include "Scene/Component/ComponentBase.hpp"

namespace Component
{
    struct CharacterController : public ComponentBase
    {
        float speed {1};
        float left{0};
        float right{0};
        float forward{0};
        float backward{0};
        Maths::Vector3f direction{0, 0, 0};
    };
}

#endif //QUACKENGINE_CHARACTERCONTROLLER_HPP
