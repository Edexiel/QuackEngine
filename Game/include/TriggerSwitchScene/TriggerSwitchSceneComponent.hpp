#ifndef QUACKENGINE_TRIGGERSWITCHSCENECOMPONENT_HPP
#define QUACKENGINE_TRIGGERSWITCHSCENECOMPONENT_HPP

#include "Scene/Component/ComponentBase.hpp"


struct TriggerSwitchSceneComponent : public Component::ComponentBase
{
    std::string world;

    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(cereal::make_nvp("world", world));
    }
};
#endif //QUACKENGINE_TRIGGERSWITCHSCENECOMPONENT_HPP